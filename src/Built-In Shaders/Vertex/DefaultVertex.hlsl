#include "../Include/Lumina.hlsli"

MeshVertexOutput main( MeshVertexInput v )
{
	MeshVertexOutput o;

	matrix worldViewProj = mul(world, mul(view, projection));

	o.position = mul(float4(v.position, 1.0), worldViewProj);
	o.worldpos = mul(float4(v.position, 1.0), world).xyz;
	o.color = v.color;
	o.texcoord = v.texcoord;
	o.normal = mul(v.normal, (float3x3)worldInverseTranspose);
	o.tangent = v.tangent;

	return o;
}