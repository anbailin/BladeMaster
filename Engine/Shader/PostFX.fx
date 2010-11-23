/**
*	common
*/

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
#if BLOOM_FILTER
VertexOutput MainVS(QuadVertex input)
{
	VertexOutput result;
	result.pos = input.pos;
	result.tex = input.tex;
    return result;
}
#endif //BLOOM_FILTER


/**
*	bright pass filter
*/
#if BLOOM_FILTER

sampler2D bloomFilterSrc : register(s0);
static const float Luminance = 0.08f;
static const float fMiddleGray = 0.18f;
static const float fWhiteCutoff = 0.8f;

float4 MainPS(VertexOutput input):COLOR0
{
	float3 ColorOut = tex2D(bloomFilterSrc, input.tex).xyz;
    
	ColorOut *=  fMiddleGray / ( Luminance + 0.001f );
    ColorOut *= ( 1.0f + ( ColorOut / ( fWhiteCutoff * fWhiteCutoff ) ) );
    ColorOut -= 5.0f;

    ColorOut = max( ColorOut, 0.0f );    

    ColorOut /= 10.0f;
    
    return float4( ColorOut, 1.0f );
}
#endif

#if (BLOOM_BLURV)||(BLOOM_BLURH)
/**
*	bloom blur
*/
static const int g_cKernelSize = 13;

static const float2 PixelKernel[g_cKernelSize] =
{
    { 0, -6 },
    { 0, -5 },
    { 0, -4 },
    { 0, -3 },
    { 0, -2 },
    { 0, -1 },
    { 0,  0 },
    { 0,  1 },
    { 0,  2 },
    { 0,  3 },
    { 0,  4 },
    { 0,  5 },
    { 0,  6 },
};

static const float BlurWeights[g_cKernelSize] = 
{
    0.002216,
    0.008764,
    0.026995,
    0.064759,
    0.120985,
    0.176033,
    0.199471,
    0.176033,
    0.120985,
    0.064759,
    0.026995,
    0.008764,
    0.002216,
};

float BloomScale = 1.5f;

sampler2D bloomSrcTex:register(s0);

float4 MainPS( float2 Tex : TEXCOORD0 ) : COLOR0
{
    float4 Color = 0;

    for (int i = 0; i < g_cKernelSize; i++)
    {    
#if BLOOM_BLURV
        Color += tex2D( bloomSrcTex, Tex + PixelKernel[i].xy/float2(640,360) ) * BlurWeights[i];
#elif (BLOOM_BLURH)
        Color += tex2D( bloomSrcTex, Tex + PixelKernel[i].yx/float2(640,360) ) * BlurWeights[i];
#endif
    }

    return float4(Color.xyz * 1.5,1);
}

#endif //#if defined(BLOOM_BLURV)||defined(BLOOM_BLURV)

#if BLOOM_MERGE
sampler2D bloomSrcTex:register(s0);
sampler2D lightingRT : register(s1);

float4 MainPS(float2 Tex : TEXCOORD0 ) : COLOR0
{
    float4 bloomColor = tex2D(bloomSrcTex, Tex);
    float4 lightingColor = tex2D(lightingRT, Tex);
    float4 result = bloomColor + lightingColor;
    return float4(result.xyz,1.0f);
}
#endif//BLOOM_MERGE

#if COPY
sampler2D srcTex:register(s0);

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
#endif