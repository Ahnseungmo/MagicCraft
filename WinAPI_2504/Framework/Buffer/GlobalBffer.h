#pragma once

class MatrixBuffer : public ConstBuffer
{
public:
    MatrixBuffer() : ConstBuffer(&matrix, sizeof(Matrix))
    {
        matrix = XMMatrixIdentity();
    }

    void Set(Matrix value)
    {
        matrix = XMMatrixTranspose(value);
    }

private:
    Matrix matrix;
};

class ColorBuffer : public ConstBuffer
{
public:
    ColorBuffer() : ConstBuffer(&color, sizeof(Float4))
    {
        color = { 1, 1, 1, 1 };
    }

    void Set(Float4 color) { this->color = color; }
    void Set(float r, float g, float b, float a = 1.0f)
    {
        color = { r, g, b, a };
    }

	Float4* GetColor() { return &color; }

private:
    Float4 color;
};

class FloatValueBuffer : public ConstBuffer
{
public:
    FloatValueBuffer() : ConstBuffer(values, sizeof(float) * 4)
    {
    }

	float* GetValues() { return values; }

private:
    float values[4] = {};
};

class IntValueBuffer : public ConstBuffer
{
public:
    IntValueBuffer() : ConstBuffer(values, sizeof(int) * 4)
    {
    }

    int* GetValues() { return values; }

private:
    int values[4] = {};
};

struct BiomePosData
{
    DirectX::XMFLOAT2 biomePos;  // 2D ��ǥ
};

class BiomeBuffer : public StructuredBuffer
{
public:
    // ������: StructuredBuffer �ʱ�ȭ
    BiomeBuffer(BiomePosData* data, UINT numElements)
        : StructuredBuffer(data, sizeof(BiomePosData), numElements)
    {
    }

    // SetBiomePos: Ư�� �ε����� biomePos �� ����
    void SetBiomePos(int index, const DirectX::XMFLOAT2& pos)
    {
        if (index >= 0 && index < 5) {
            ((BiomePosData*)data)[index].biomePos = pos;  // biomePos ���� �迭�� ����
        }
        
    }

    // GetBiomePos: Ư�� �ε����� biomePos �� ��ȯ
    DirectX::XMFLOAT2 GetBiomePos(int index)
    {
        if (index >= 0 && index < 5) {
            return ((BiomePosData*)data)[index].biomePos;
        }
        return DirectX::XMFLOAT2(0.0f, 0.0f);  // �߸��� �ε����� �⺻�� ��ȯ
    }

    void SetPS(UINT slot) {
        StructuredBuffer::UpdateBuffer();  // ������ ������Ʈ
        StructuredBuffer::SetPS(slot);
    }
};