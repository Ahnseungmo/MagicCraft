#pragma once

class StructuredBuffer
{
public:
    StructuredBuffer(void* data, UINT dataSize, UINT numElements);
    ~StructuredBuffer();

    void UpdateBuffer();

    void SetVS(UINT slot);  // Vertex Shader에 Structured Buffer 전달
    void SetPS(UINT slot);  // Pixel Shader에 Structured Buffer 전달
    void UpdateData(void* newData);  // CPU에서 데이터를 업데이트

    ID3D11Buffer* GetBuffer() const { return buffer; } // 버퍼를 반환

protected:
    ID3D11Buffer* buffer;  // GPU에서 사용되는 Structured Buffer
    ID3D11ShaderResourceView* srv;  // 셰이더 리소스 뷰 (StructuredBuffer 읽기용)

    void* data;  // 데이터를 저장하는 CPU측 데이터
    UINT dataSize;  // 각 요소의 크기
    UINT numElements;  // 요소의 개수
};
