struct PS_IN
{
	float4 diffuse:COLOR;
};

struct PS_OUT
{
	float4 color: COLOR;
};

PS_OUT main(PS_IN input)
{
	PS_OUT result;
	result.color = input.diffuse;
	return result;
}