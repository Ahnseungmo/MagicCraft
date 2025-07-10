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


StructuredBuffer<float2> biomePos : register(t1); // StructuredBuffer�� t0�� ���ε�
Texture2D baseMap : register(t0);
SamplerState samplerState : register(s0);

float4 PS(Output output) : SV_TARGET
{
    // �⺻ ���� �迭 (���̿� ����)
    float4 baseColors[5];
    
    // �Ÿ� ����� ���� ����
    float distance[5];
    
    // ���� ��ġ�� basePos.xy�� ���� (������ǥ)
    float2 basePos = output.basePos.xy;

    const float MAX_DISTANCE = 1e30f;
    // ���� ����� ���̿��� ã�� ���� ����
    int closestBiomeIndex = 4;
    float closestDistance = MAX_DISTANCE; // ���� ū ������ �ʱ�ȭ

    // ���̿� ���� �� �Ÿ� ���
    for (int i = 0; i < 5; i++)
    {
        // UV ��ǥ ��� (���� �������� ��������)
        float2 uv;
        uv.x = (output.uv.x + ((output.curFrame.x + (i * 6)) / output.maxFrame.x)); // �������� ������ UV ���
        uv.y = (output.uv.y + ((output.curFrame.y) / output.maxFrame.y)); // �������� ������ UV ���
        
        // ���ø��� ���� �ش� ���̿��� ���� ������
        baseColors[i] = baseMap.Sample(samplerState, uv);

        // ���� �ȼ� ��ġ�� ���̿� ��ġ �� �Ÿ� ���
        float2 dif = biomePos[i] - basePos;
        float dist = dif.x * dif.x + dif.y * dif.y;

        // ���� ����� ���̿��� ã��
        if (dist < closestDistance)
        {
            closestDistance = dist;
            closestBiomeIndex = i;
        }
    }

    // ���� ����� ���̿� ���� ����
    float4 finalColor = baseColors[closestBiomeIndex];

    // ��� ���� ���� ������ ���ؼ� ��ȯ
    return finalColor * color;
}