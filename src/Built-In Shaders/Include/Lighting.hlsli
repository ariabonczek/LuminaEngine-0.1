#ifndef LIGHTING_HLSLI
#define LIGHTING_HLSLI

//
// Handles all lighting calculation and information for Lumina
//
float PI = 3.14159265359;

struct DirectionalLight
{
	float4 color;
	float3 direction;
	float  intensity;
	bool   hasShadows;
};

struct PointLight
{
	float4 color;
	float3 position;
	float  range;
	float  intensity;
	bool   hasShadows;
};

struct SpotLight
{
	float4 color;
	float3 direction;
	float  intensity;
	float3 position;
	float  range;
	float  spot;
	bool   hasShadows;
};

///
// Forward Rendering
///

// Blinn-Phong rendering
float4 CalculateLighting(DirectionalLight dLight, float3 normal, float3 view, float specularPower)
{
	float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float3 lightVector = -dLight.direction;

	float diffusefactor = dot(lightVector, normal);
	diffusefactor = max(0.0f, diffusefactor);
		return float4(diffusefactor, diffusefactor, diffusefactor, 1.0);
		diffuse = float4((dLight.color * dLight.intensity * diffusefactor).rgb, 1.0f);
		float3 v = normalize(reflect(lightVector, normal));
		float specularfactor = dot(view, v);

		if (specularfactor > 0)
		{
			specularfactor = pow(specularfactor, specularPower);
			specular = float4((dLight.color * dLight.intensity * specularfactor).rgb, 1.0f);
		}
	
	return diffuse + specular;
}

float4 CalculateLighting(PointLight pLight, float3 pos, float3 normal, float3 view, float specularPower)
{
	float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float3 lightVector = pLight.position - pos;
	float d = length(lightVector);
	if (d > pLight.range)
		return diffuse;
	lightVector /= d;

	float diffusefactor = dot(lightVector, normal);
	if (diffusefactor > 0)
	{
		diffuse = float4((pLight.color * pLight.intensity * diffusefactor).rgb, 1.0f);
		float3 v = normalize(reflect(lightVector, normal));
		float specularfactor = dot(view, v);

		if (specularfactor > 0)
		{
			specularfactor = pow(specularfactor, specularPower);
			specular = float4((pLight.color * pLight.intensity * specularfactor).rgb, 1.0f);
		}
	}
	// 0.01 represents the minimum percentage of light before attenuation turns to black
	float attenuation = 1.0f / (d*d * 0.01) ;
	diffuse *= attenuation;
	specular *= attenuation;
	return diffuse + specular;
}

float4 CalculateLighting(SpotLight sLight, float3 pos, float3 normal, float3 view, float specularPower)
{
	float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float3 lightVector = sLight.position - pos;
	float d = length(lightVector);
	if (d > sLight.range)
		return diffuse;
	lightVector /= d;

	float diffusefactor = dot(lightVector, normal);
	if (diffusefactor > 0)
	{
	 diffuse = float4((sLight.color * sLight.intensity * diffusefactor).rgb, 1.0f);
		float3 v = normalize(reflect(lightVector, normal));
		float specularfactor = dot(view, v);

		if (specularfactor > 0)
		{
			specularfactor = pow(specularfactor, specularPower);
			specular = float4((sLight.color * sLight.intensity * specularfactor).rgb, 1.0f);
		}
	}
	float spot = pow(max(dot(-lightVector, sLight.direction), 0.0f), sLight.spot);
	float attenuation = spot / (d*d * 0.01);
	diffuse *= attenuation;
	specular *= attenuation;
	return diffuse + specular;
}

float4 CalculateAllLights(DirectionalLight dLight[1], uint numDL, PointLight pLight[1], uint numPL, SpotLight sLight[1], uint numSL, float3 pos, float3 normal, float3 view, float specularPower)
{
	float4 ret = float4(0.0f, 0.0f, 0.0f, 0.0f);
	for (uint i = 0; i < numDL; i++)
	{
		ret += CalculateLighting(dLight[i], normal, view, specularPower);
	}
	for (uint i = 0; i < numPL; i++)
	{
		ret += CalculateLighting(pLight[i], pos, normal, view, specularPower);
	}
	for (uint i = 0; i < numSL; i++)
	{
		ret += CalculateLighting(sLight[i], pos, normal, view, specularPower);
	}
	return ret;
}

///
// Physically based rendering
///

float NormalDistribution(float roughness, float3 normal, float3 halfvector)
{
	float alpha = roughness * roughness;
	float alpha2 = alpha*alpha;
	float ndotd = dot(normal, halfvector);
	float denom = ((ndotd*ndotd) * (alpha2 - 1) + 1);

	return alpha2 / denom*denom;
}

float GaussianFresnelReflectance(float metalness, float3 viewvector, float3 halfvector)
{
	float vdoth = saturate(dot(viewvector, halfvector));

	return metalness + (1 - metalness) * exp2((5.55473 * vdoth - 6.98316) * vdoth);
}

float GeometricAttenuationInternal(float k, float3 normal, float3 _vector)
{
	float ndotv = saturate(dot(normal, _vector));
	
	return ndotv / (ndotv * (1 - k) + k);
}

float GeometricAttenuation(float roughness, float3 normal, float3 viewvector, float3 lightvector)
{
	float k = ((roughness + 1) * (roughness + 1)) / 8;

	return GeometricAttenuationInternal(k, normal, viewvector) * GeometricAttenuationInternal(k, normal, lightvector);
}

float CookTorrenceMicrofacetSpecular(float roughness, float metalness, float3 normal, float3 viewvector, float3 halfvector, float3 lightvector)
{
	return
		(NormalDistribution(roughness, normal, halfvector) * GaussianFresnelReflectance(metalness, viewvector, halfvector) * GeometricAttenuation(roughness, normal, viewvector, lightvector)) /
		(4 * saturate(dot(normal, lightvector)) * saturate(dot(normal, viewvector)));
}


// Ideally, support multiple lighting models here
float4 PBRCalculateFinalColor(float4 diffuse, float3 normal, float roughness, float metalness, float3 viewvector, DirectionalLight dLight)
{
	float3 halfvector = normalize(-dLight.direction + viewvector);

	float4 specular = CookTorrenceMicrofacetSpecular(roughness, metalness, normal, viewvector, halfvector, -dLight.direction);
	
	return float4((diffuse + specular).rgb * (dLight.color.rgb * dLight.intensity * dot(normal, -dLight.direction)).rgb , 1.0);
}

#endif