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

struct BiomeData
{
    DirectX::XMFLOAT2 base;
    float _padding0[2]; // 16����Ʈ ���� �����

    DirectX::XMFLOAT2 biomePos[5];
    float _padding1[2]; // �� ũ�⸦ 16����Ʈ ����� ����
};

class BiomeBuffer : public ConstBuffer
{
public:
    BiomeBuffer() : ConstBuffer(&data, sizeof(BiomeData)) {}

    void SetBase(const Vector2& v) { data.base = { v.x, v.y }; }
    void SetBiomePos(int index, const Vector2& v)
    {
        if (index >= 0 && index < 5)
            data.biomePos[index] = { v.x, v.y };
    }

    BiomeData* Get() { return &data; }

private:
    BiomeData data = {};
};