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

VS_OUT main(VS_IN input)
{
	VS_OUT result;
	float4 pos = float4(input.pos.x, input.pos.z, -input.pos.y,1.0f);
	result.pos = mul(wvp,pos);
	result.diffuse = input.color;
	return result;
}