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
    DirectX::XMFLOAT2 biomePos;  // 2D 좌표
};

class BiomeBuffer : public StructuredBuffer
{
public:
    // 생성자: StructuredBuffer 초기화
    BiomeBuffer(BiomePosData* data, UINT numElements)
        : StructuredBuffer(data, sizeof(BiomePosData), numElements)
    {
    }

    // SetBiomePos: 특정 인덱스에 biomePos 값 설정
    void SetBiomePos(int index, const DirectX::XMFLOAT2& pos)
    {
        if (index >= 0 && index < 5) {
            ((BiomePosData*)data)[index].biomePos = pos;  // biomePos 값을 배열에 설정
        }
        
    }

    // GetBiomePos: 특정 인덱스의 biomePos 값 반환
    DirectX::XMFLOAT2 GetBiomePos(int index)
    {
        if (index >= 0 && index < 5) {
            return ((BiomePosData*)data)[index].biomePos;
        }
        return DirectX::XMFLOAT2(0.0f, 0.0f);  // 잘못된 인덱스는 기본값 반환
    }

    void SetPS(UINT slot) {
        StructuredBuffer::UpdateBuffer();  // 데이터 업데이트
        StructuredBuffer::SetPS(slot);
    }
};