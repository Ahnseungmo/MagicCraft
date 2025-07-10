#pragma once

class StructuredBuffer
{
public:
    StructuredBuffer(void* data, UINT dataSize, UINT numElements);
    ~StructuredBuffer();

    void UpdateBuffer();

    void SetVS(UINT slot);  // Vertex Shader�� Structured Buffer ����
    void SetPS(UINT slot);  // Pixel Shader�� Structured Buffer ����
    void UpdateData(void* newData);  // CPU���� �����͸� ������Ʈ

    ID3D11Buffer* GetBuffer() const { return buffer; } // ���۸� ��ȯ

protected:
    ID3D11Buffer* buffer;  // GPU���� ���Ǵ� Structured Buffer
    ID3D11ShaderResourceView* srv;  // ���̴� ���ҽ� �� (StructuredBuffer �б��)

    void* data;  // �����͸� �����ϴ� CPU�� ������
    UINT dataSize;  // �� ����� ũ��
    UINT numElements;  // ����� ����
};
