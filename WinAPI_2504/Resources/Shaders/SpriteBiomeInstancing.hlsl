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
    
    matrix transform : INSTANCE_TRANSFORM;
    float2 curFrame : INSTANCE_CURFRAME;
    float2 maxFrame : INSTANCE_MAXFRAME;
};

struct Output
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
    
    float2 curFrame : INSTANCE_CURFRAME;
    float2 maxFrame : INSTANCE_MAXFRAME;
};

Output VS(Input input)
{
    Output output;
    
    matrix transform = mul(input.transform, world);
    output.pos = mul(input.pos, transform);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    
    output.uv = input.uv;
        
    output.curFrame = input.curFrame;
    output.maxFrame = input.maxFrame;
    
    return output;
}

cbuffer ColorBuffer : register(b0)
{
    float4 color;
}

cbuffer BiomeBuffer : register(b0)
{
    float2 base;
    float2 biomePos[5];
};

Texture2D baseMap : register(t0);
SamplerState samplerState : register(s0);

float4 PS(Output output) : SV_TARGET
{
//    float2 uv = output.uv + (output.curFrame / output.maxFrame); // Adjust UV based on current frame
    

    float4 baseColors[5] = { 0, };
    float distance[5] = { 0, };
    float merge = 0;

    for (int i = 0; i < 5; i++)
    {
        float2 uv = output.uv + ((output.curFrame + i * 6) / output.maxFrame); // Adjust UV based on current frame
        baseColors[i] = baseMap.Sample(samplerState, uv);
        float2 dif = biomePos[i] - base;
        distance[i] = sqrt(dif.x * dif.x + dif.y + dif.y);
        merge += distance[i];
    }
    for (int i = 0; i < 5; i++)
    {
        baseColors[i].a = distance[i]/merge;
        
    }
    
    float4 baseColor = baseColors[0];
    for (int i = 1; i < 5; i++)
    {
//        baseColor *=     float4 baseColor = baseColors[0];

    }
    
    
      
   // float4 baseColor = baseMap.Sample(samplerState, uv);
    return baseColor * color;
}