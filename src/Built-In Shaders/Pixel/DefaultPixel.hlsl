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
	float4 texcolor = _Albedo.Sample(_Sampler, input.texcoord);
	float3 normal = UnpackNormals(_Normal.Sample(_Sampler, input.texcoord));
	float metalness = _Metalness.Sample(_Sampler, input.texcoord).r;
	
	float3 viewvector = normalize(eyePos - input.worldpos);
	
	texcolor *= tint;

	return PBRCalculateFinalColor(texcolor, normal, roughness, metalness, viewvector, dLight[0]);
}