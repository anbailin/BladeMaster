#define MAX_BONE 60

struct BoneContainer
{
	float4x4 Bones[ MAX_BONE ];
};
const float4x4 World:register(c0);
const float4x4 ViewProj:register(c4);
const BoneContainer  BoneData : register(c9);

struct VS_IN
{
	float3 pos		:POSITION;
	float4 weight   :BLENDWEIGHT;
	int4   indice   :BLENDINDICES;
	float3 normal   :NORMAL;
	float2 texcoord :TEXCOORD0;
	float4 color0   :COLOR0;
	float4 color1   :COLOR1;
};

struct VS_OUT
{
	float4 pos		: POSITION;	
	float4 diffuse	: COLOR0;
	float2 tex		: TEXCOORD0;	
	float3 normal	: TEXCOORD1;
};

float3 ccanan(float4x4 m, float3 v)
{
	float3 result ;
	result.x = m[0][0]*v.x + m[0][1]*v.y + m[0][2]*v.z + m[0][3];
	result.y = m[1][0]*v.x + m[1][1]*v.y + m[1][2]*v.z + m[1][3];
	result.z = m[2][0]*v.x + m[2][1]*v.y + m[2][2]*v.z + m[2][3];
	return result;
}

float3 ccanan(float3 v, float4x4 m)
{
	float3 result;
	result.x = v.x*m[0][0] + v.y*m[1][0] + v.z*m[2][0] + m[3][0];
	result.y = v.x*m[0][1] + v.y*m[1][1] + v.z*m[2][1] + m[3][1];
	result.z = v.x*m[0][2] + v.y*m[1][2] + v.z*m[2][2] + m[3][2];
	return result;
}


float3 nor(float4x4 m, float3 v)
{
	float3 result ;
	result.x = m[0][0]*v.x + m[0][1]*v.y + m[0][2]*v.z;
	result.y = m[1][0]*v.x + m[1][1]*v.y + m[1][2]*v.z;
	result.z = m[2][0]*v.x + m[2][1]*v.y + m[2][2]*v.z;
	return result;
}
const float ratio = 1.0;

VS_OUT MainVS(VS_IN input)
{
	VS_OUT result;

	float4x4 wvp =  mul(ViewProj,World);
//---------------------------------------------------------
	//float3 pos = float3(input.pos.x, input.pos.z, -input.pos.y);
	float3 pos = input.pos;
	
	float4 weights = input.weight.bgra;
	
	float3 pos1 = ccanan(BoneData.Bones[input.indice.x],pos);
	float3 pos2 = ccanan(BoneData.Bones[input.indice.y],pos);
	float3 pos3 = ccanan(BoneData.Bones[input.indice.z],pos);
	float3 pos4 = ccanan(BoneData.Bones[input.indice.w],pos);
	float3 animpos = pos1*weights.x + pos2*weights.y + pos3*weights.z + pos4*weights.w;
	float4 newpos = float4(animpos.x,animpos.z,-animpos.y,1);

	result.pos = mul(wvp,newpos);
//---------------------------------------------------------
	float3 normal = input.normal;
	float3 nor1 = mul((float3x3)BoneData.Bones[input.indice.x],normal);
	float3 nor2 = mul((float3x3)BoneData.Bones[input.indice.y],normal);
	float3 nor3 = mul((float3x3)BoneData.Bones[input.indice.z],normal);
	float3 nor4 = mul((float3x3)BoneData.Bones[input.indice.w],normal);
	float3 animNorm = nor1*weights.x + nor2*weights.y + nor3*weights.z + nor4*weights.w;
	
	animNorm = mul(animNorm,World);
	animNorm = normalize(animNorm);
    float lighting = saturate(dot(animNorm, float3(0,1,0)));
//---------------------------------------------------------
	result.tex = input.texcoord;

	result.diffuse = float4(weights.xyz,lighting);

	result.normal = animNorm;

	return result;
}

struct PS_IN
{
	float4 diffuse	: COLOR0;
	float2 tex		: TEXCOORD0;
	float3 normal	: TEXCOORD1;
};

struct PS_OUT
{
	float4 color	: COLOR0;
};


sampler2D		tex_simple				: register(s0);

const float3 light = float3(1,0,0);

float4 MainPS(PS_IN input):COLOR0
{    
    const float4 ambient = float4(0.2,0.6,0.8,1);
    const float4 diffuse = float4(1.9,0.4,0.0,1);
	float4 texcolor = tex2D(tex_simple,input.tex);	
		
	float4 lighting = input.diffuse.w*diffuse + ambient;    
    return lighting * texcolor;
}