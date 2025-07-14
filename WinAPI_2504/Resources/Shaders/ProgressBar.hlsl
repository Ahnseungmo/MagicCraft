cbuffer WorldBuffer : register(b0)
{
    matrix world;
}
cbuffer ViewBuffer : register(b1)
{
    matrix view;
}
cbuffer ProjectionBuffer : register(b2)
{
    matrix projection;
}

struct Input
{
    float4 pos : POSITION;
    float2 uv : UV;
};

struct Output
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

Output VS(Input input)
{
    Output output;
    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    
    output.uv = input.uv;
    
    return output;
}

cbuffer ColorBuffer : register(b0)
{
    float4 color;
}

cbuffer ProgressBarBuffer : register(b1)
{
    float amount; // Amount of progress (0.0 to 1.0)
};

cbuffer ColorBuffer : register(b2)
{
    float4 addColor;
}

Texture2D baseMap : register(t0);
Texture2D secondMap : register(t1);

SamplerState samplerState : register(s0);


float4 PS(Output output) : SV_TARGET
{
    float2 uv = output.uv;

    // 체력 영역 바깥이면 투명
    if (uv.x > amount)
        return float4(0, 0, 0, 0);

    // 체력 영역 출력
    float4 baseColor = baseMap.Sample(samplerState, uv);

    return baseColor;
}