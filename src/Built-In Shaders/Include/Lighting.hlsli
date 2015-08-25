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

// Blinn-Phong rendering



// Physically based rendering

float NormalDistribution(float roughness, float3 normal, float3 halfvector)
{
	float alpha = roughness * roughness;
	float alpha2 = alpha*alpha;
	float ndotd = dot(normal, halfvector);
	float denom = ((ndotd*ndotd) * (alpha2 - 1) + 1);

	return alpha2 / 3.141592 * denom*denom;
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

float4 LambertianBDRF(float4 cdiff)
{
	return cdiff / 3.141592;
}

// Ideally, support multiple lighting models here
float4 PBRCalculateFinalColor(float4 albedo, float3 normal, float roughness, float metalness, float3 viewvector, DirectionalLight dLight)
{
	float3 halfvector = normalize(l + v);

	float4 diffuse = LambertianBDRF(albedo);
	float4 specular = CookTorrenceMicrofacetSpecular(roughness, metalness, normal, viewvector, halfvector, dLight.direction);
	
	return float4(3.141592 * (diffuse + specular).rgb * (dLight.color.rgb * dLight.intensity * dot(normal, dLight.direction)).rgb , 1.0);
}

#endif