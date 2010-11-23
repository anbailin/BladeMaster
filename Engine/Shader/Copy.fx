sampler2D srcTex:register(s0);

struct QuadVertex
{
	float4 pos : POSITION;
	float2 tex : TEXCOORD0;
};

struct VertexOutput
{
	float4 pos : POSITION;
	float2 tex : TEXCOORD0;
};

/**
*	bloom impl
*/
VertexOutput MainVS(QuadVertex input)
{
	VertexOutput result;
	result.pos = input.pos;
	result.tex = input.tex;
    return result;
}

float4 MainPS(QuadVertex input):COLOR0
{
	return tex2D(srcTex, input.tex);
}