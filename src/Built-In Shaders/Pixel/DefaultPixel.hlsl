#include "../Include/Lumina.hlsli"

cbuffer Properties : register(b1)
{
	float4 tint;
	float roughness;
	float metalness;
}

Texture2D _Albedo : register(t0);
Texture2D _Normal : register(t1);
Texture2D _Metalness : register(t2);

sampler _Sampler : register(s0);

float4 main(MeshVertexOutput input) : SV_TARGET
{
	// Grab the texture color
	float4 texcolor = _Albedo.Sample(_Sampler, input.texcoord);
	return texcolor;
	// Normal mapping
	float3 normalT = UnpackNormals(_Normal.Sample(_Sampler, input.texcoord));
	float3 N = input.normal;
	float3 T = normalize(input.tangent - dot(input.tangent, N) * N);
	float3 B = cross(N, T);
	float3x3 TBN = float3x3(T, B, N);
	float3 bumpedNormal = normalize(mul(normalT, TBN));

	// Grab the metalness map
	//float metalness = _Metalness.Sample(_Sampler, input.texcoord).r;

	float3 viewvector = normalize(eyePos - input.worldpos);

	texcolor *= tint;

	//return texcolor * (CalculateAllLights(dLight, numDL, pLight, numPL, sLight, numSL, input.position, bumpedNormal, viewvector, specularPower) + ambientLight);
	return PBRCalculateFinalColor(texcolor, bumpedNormal, roughness, metalness, viewvector, dLight[0]);
}