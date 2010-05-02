#define MAX_BONE 66

const float4x4	wvp:register(c0);

struct VS_IN
{
	float4 pos		:POSITION;	
	float4 color	:COLOR;
};

struct VS_OUT
{
	float4 pos		: POSITION;
	float4 diffuse	:COLOR;
};

VS_OUT MainVS(VS_IN input)
{
	VS_OUT result;
	float4 pos = float4(input.pos.x, input.pos.z, -input.pos.y,1.0f);
	result.pos = mul(wvp,pos);
	result.diffuse = input.color;
	return result;
}

struct PS_IN
{
	float4 diffuse:COLOR;
};

struct PS_OUT
{
	float4 color: COLOR;
};

PS_OUT MainPS(PS_IN input)
{
	PS_OUT result;
	result.color = input.diffuse;
	return result;
}