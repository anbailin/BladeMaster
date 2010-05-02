struct VS_In
{
    float4 pos : POSITION;
    float3 normal : NORMAL;
    float4 color : COLOR0;
};

struct VS_Out
{
    float4 pos : POSITION;
    float3 normal : NORMAL;
    float4 color : COLOR0;
};

/**
*   vs and constans
*/
const float4x4 World    :register(c0);
const float4x4 View     :register(c4);
const float4x4 Proj     :register(c8);

VS_Out MainVS(VS_In vsin)
{
    float4x4 wv = mul(View, World);
    float4x4 wvp = mul(Proj, wv);
    VS_Out final;
    final.pos = mul(wvp,vsin.pos);
    final.normal = mul(wv,vsin.normal);
    final.color = vsin.color;

    return final;
}

/*
*   ps and contants
*/
const float4   TimeStamp:register(c0);

float4 MainPS(VS_Out psin):COLOR0
{
    float4 result = fmod(psin.color*5+TimeStamp*0.01,2.0f);
    result.x = abs(result.x-1.0f);
    result.x = result.x*result.x*0.5;
    return float4(result.x,result.x,result.x+0.3,1);    
}