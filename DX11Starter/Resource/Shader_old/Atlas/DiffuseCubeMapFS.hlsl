// External texture-related data
Texture2D texture_diffuse		: register(t0);
Texture2D texture_normal		: register(t1);
Texture2D texture_property		: register(t2);

SamplerState samplerWrap	: register(s0);

// Defines the input to this pixel shader
// - Should match the output of our corresponding vertex shader
struct VertexToPixel
{
	float4 position		: SV_POSITION;
	float3 normal		: NORMAL0;
	float3 tangent		: NORMAL1;
	float3 biTangent	: NORMAL2;
	float4 worldPos		: POSITION;
	float2 uv			: TEXCOORD;
};


struct PS_OUTPUT
{
	float4 world: SV_Target0;
	float4 normal: SV_Target1;
	float4 diffuse: SV_Target2;
	float4 property: SV_Target3;
	//float4 texture_specular: SV_Target4; At some point...
};

// Entry point for this pixel shader
PS_OUTPUT main(VertexToPixel input) : SV_TARGET
{
	input.normal = normalize(input.normal);
	input.tangent = normalize(input.tangent);
	input.biTangent = normalize(input.biTangent);


	PS_OUTPUT output;
	float3 normal = texture_normal.Sample(samplerWrap, input.uv).xyz * 2 - 1;
	normal = normal.x * input.tangent +normal.y * input.biTangent + normal.z * input.normal;

	//output.normal = float4(input.uv,0,1);
	output.world = float4(input.worldPos.xyz,1);
	output.normal = float4(normal, 1);
	output.diffuse = texture_diffuse.Sample(samplerWrap, input.uv);
	output.property = texture_property.Sample(samplerWrap, input.uv);
	//output.normal = float4((normal + 1) *.5, 1);
	//output.specular = texture_specular.Sample(samplerWrap, input.uv);

	 //output.diffuse = float4(0, 0, 0, 0);
	 //output.normal = float4(0, 0, 0, 0);
	 //output.specular = float4(0, 0, 0, 0);
	 //output.normal = float4(input.worldPos.xyz, 1);
	 //output.worldPos = float4(input.worldPos.xyz, 1);
	//output.depth = float4(input.worldPos.w, input.worldPos.w, input.worldPos.w, 1);
	return output;
}

