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
    // �⺻ ���� �迭 (���̿� ����)
    float4 baseColors[5];
    
    // �Ÿ� ����� ���� ����
    float distance[5];
    float merge = 0;

    // ���� ��ġ�� basePos.xy�� ���� (������ǥ)
    float2 basePos = output.basePos.xy;

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
        distance[i] = sqrt(dif.x * dif.x + dif.y * dif.y);

        // ��ü �Ÿ� �ջ� (�Ÿ��� Ŭ���� ���� �� ����ǰ� �ϱ� ����)
        merge += distance[i];
    }

    // ���� ����� �� ���̿��� ã�� ���� �Ÿ��� �������� ����
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

    // �� ���� ����� ���̿� ���� �� ����
            float dist1 = distance[closest1] / merge;
    float dist2 = distance[closest2] / merge;
    
    // ���� ����
 //   float4 finalColor = lerp(baseColors[closest1], baseColors[closest2], dist1 / (dist1 + dist2));
    float4 finalColor = baseColors[index];

    // ��� ���� ���� ������ ���ؼ� ��ȯ
    return finalColor * color;
}