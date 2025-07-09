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
    
    
    matrix transform = mul(input.transform, world);    
    output.pos = mul(input.pos, transform);    

    output.basePos = output.pos.xyz;
//    output.basePos = output.pos.xyz / output.pos.w;

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

cbuffer BiomeBuffer : register(b1)
{
    float2 base;
    float2 biomePos[5];
};

Texture2D baseMap : register(t0);
SamplerState samplerState : register(s0);

float4 PS(Output output) : SV_TARGET
{
    // 기본 색상 배열 (바이옴 색상)
    float4 baseColors[5];
    
    // 거리 계산을 위한 변수
    float distance[5];
    float merge = 0;

    // 현재 위치를 basePos.xy로 설정 (월드좌표)
    float2 basePos = output.basePos.xy;

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
        distance[i] = sqrt(dif.x * dif.x + dif.y * dif.y);

        // 전체 거리 합산 (거리가 클수록 색이 덜 적용되게 하기 위함)
        merge += distance[i];
    }

    // 가장 가까운 두 바이옴을 찾기 위해 거리를 기준으로 정렬
    float dis = distance[0];
    int index = 0;
    for (int i = 1; i < 5; i++)
    {
        if (distance[i] <= dis)
        {
            index = i;
            dis = distance[i];
        }

    }

    int closest1 = 0, closest2 = 1;
    if (distance[1] < distance[0]) {
        closest1 = 1;
        closest2 = 0;
    }
    /*

    for (int i = 2; i < 5; i++)
    {
        if (distance[i] < distance[closest1]) {
            closest2 = closest1;
            closest1 = i;
        } else if (distance[i] < distance[closest2]) {
            closest2 = i;
        }
    }
    */

    // 두 가장 가까운 바이옴 색상 간 보간
            float dist1 = distance[closest1] / merge;
    float dist2 = distance[closest2] / merge;
    
    // 색상 보간
 //   float4 finalColor = lerp(baseColors[closest1], baseColors[closest2], dist1 / (dist1 + dist2));
    float4 finalColor = baseColors[index];

    // 결과 색상에 최종 색상을 곱해서 반환
    return finalColor * color;
}