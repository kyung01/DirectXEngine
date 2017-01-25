cbuffer externalData : register(b0)
{
	float SCREEN_WIDTH, SCREEN_HEIGHT;
	float3 lightColor;
};
struct VertexToPixel
{
	float4 position		: SV_POSITION;
};



Texture2D textureEyeDepth		: register(t0);

SamplerState samplerBoarderZero : register(s0);
// Entry point for this pixel shader
float4 main(VertexToPixel input) : SV_TARGET
{
	float2 uv = input.position.xy / float2(SCREEN_WIDTH,SCREEN_HEIGHT);

	float4 d = textureEyeDepth.Sample(samplerBoarderZero, uv );//
	if (input.position.z < d.x + 0.00000001)
		return float4(1, 0, 0, 1);
	return float4(0, 0, 1, 1);
	//return float4(input.position.x / SCREEN_WIDTH, input.position.y / SCREEN_HEIGHT, 0,1);
}
