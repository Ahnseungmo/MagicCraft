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
    
    float3 basePos : TEXCOORD0;
};

Output VS(Input input)
{
    Output output;
    
    float4 worldPos = mul(input.pos, mul(input.transform, world));
    output.basePos = worldPos.xyz;
    
    matrix transform = mul(input.transform, world);    
    output.pos = mul(input.pos, transform);    

//   output.basePos = output.pos.xyz;
//   output.basePos = output.pos.xyz / output.pos.w;

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
/*
cbuffer BiomeBuffer : register(b1)
{
    float2 biomePos[5];
};
*/


StructuredBuffer<float2> biomePos : register(t1); // StructuredBuffer를 t0에 바인딩
Texture2D baseMap : register(t0);
SamplerState samplerState : register(s0);

float4 PS(Output output) : SV_TARGET
{
    // 기본 색상 배열 (바이옴 색상)
    float4 baseColors[5];
    
    // 거리 계산을 위한 변수
    float distance[5];
    
    // 현재 위치를 basePos.xy로 설정 (월드좌표)
    float2 basePos = output.basePos.xy;

    const float MAX_DISTANCE = 1e30f;
    // 가장 가까운 바이옴을 찾기 위한 변수
    int closestBiomeIndex = 4;
    float closestDistance = MAX_DISTANCE; // 아주 큰 값으로 초기화

    // 바이옴 색상 및 거리 계산
    for (int i = 0; i < 5; i++)
    {
        // UV 좌표 계산 (현재 프레임을 기준으로)
        float2 uv;
        uv.x = (output.uv.x + ((output.curFrame.x + (i * 6)) / output.maxFrame.x)); // 오프셋을 적용한 UV 계산
        uv.y = (output.uv.y + ((output.curFrame.y) / output.maxFrame.y)); // 오프셋을 적용한 UV 계산
        
        // 샘플링을 통해 해당 바이옴의 색을 가져옴
        baseColors[i] = baseMap.Sample(samplerState, uv);

        // 현재 픽셀 위치와 바이옴 위치 간 거리 계산
        float2 dif = biomePos[i] - basePos;
        float dist = dif.x * dif.x + dif.y * dif.y;

        // 가장 가까운 바이옴을 찾기
        if (dist < closestDistance)
        {
            closestDistance = dist;
            closestBiomeIndex = i;
        }
    }

    // 가장 가까운 바이옴 색상 적용
    float4 finalColor = baseColors[closestBiomeIndex];

    // 결과 색상에 최종 색상을 곱해서 반환
    return finalColor * color;
}