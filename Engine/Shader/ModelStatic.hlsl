const float4x4 World:		register(c0);
const float4x4 ViewProj:	register(c4);

struct VS_IN
{
	float3 pos		:POSITION;
	float3 normal   :NORMAL;
	float2 texcoord :TEXCOORD0;
};

struct VS_OUT
{
	float4 pos		: POSITION;
	float4 diffuse	: COLOR0;
	float2 tex		: TEXCOORD0;	
	float3 normal   : TEXCOORD1;
};


VS_OUT MainVS(VS_IN input)
{
	VS_OUT result;
	float4x4 wvp = mul(ViewProj,World);
	float4 pos = float4(input.pos.x,input.pos.z, -input.pos.y, 1);
	//float4 pos = float4(input.pos.xyz, 1);
	result.pos = mul(wvp,pos);
	result.normal = mul(input.normal,(float3x3)World);
	result.normal = normalize(result.normal);

    float lighting = saturate(dot(result.normal, float3(0,1,0)));

	result.diffuse = float4(1,1,1,lighting);
	result.tex = input.texcoord;
	return result;
}

struct PS_IN
{
	float4 diffuse	: COLOR0;
	float2 tex		: TEXCOORD0;
	float3 normal   : TEXCOORD1;
};

sampler2D tex_Creature : register(s0);

float4 MainPS(PS_IN input):COLOR0
{
    const float4 ambient = float4(0.2,0.6,0.8,1);
    const float4 diffuse = float4(1.9,0.4,0.0,1);
	float4 texcolor = tex2D(tex_Creature,input.tex);	
		
	float4 lighting = input.diffuse.w*diffuse + ambient;  
    return lighting*texcolor;
}