#include "Lighting.hlsli"

cbuffer perFrame : register(b0)
{
	matrix view;
	matrix projection;
	float3 eyePos;
	float elapsedTime;
}

cbuffer perObject : register(b2)
{
	matrix world;
	matrix worldInverseTranspose;
}

cbuffer lighting : register(b3)
{
	DirectionalLight dLight[1];
	PointLight		 pLight[1];
	SpotLight        sLight[1];
	uint numDL;
	uint numPL;
	uint numSL;
}

struct MeshVertexInput
{
	float3 position : POSITION;
	float4 color    : COLOR;
	float2 texcoord : TEXCOORD0;
	float3 normal   : NORMAL;
	float3 tangent  : TANGENT;
};

struct MeshVertexOutput
{
	float4 position : SV_POSITION;
	float3 worldpos : POSITION0;
	float4 color    : COLOR;
	float2 texcoord	: TEXCOORD0;
	float3 normal   : NORMAL;
	float3 tangent  : TANGENT;
};

float3 UnpackNormals(float3 samplevalue)
{
	return samplevalue * 2.0f - 1.0f;
}