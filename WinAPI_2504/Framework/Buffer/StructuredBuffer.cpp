#include "Framework.h"

StructuredBuffer::StructuredBuffer(void* data, UINT dataSize, UINT numElements)
    : data(data), dataSize(dataSize), numElements(numElements), buffer(nullptr), srv(nullptr)
{
    // 버퍼 생성
    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth = dataSize * numElements;  // 정확한 크기 설정
    bufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    bufferDesc.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = data;

    HRESULT hr = DEVICE->CreateBuffer(&bufferDesc, &initData, &buffer);
    if (FAILED(hr))
    {
        MessageBox(nullptr, L"Buffer Creation Failed!", L"Error", MB_OK);
        return;  // 초기화 실패 시 리턴
    }

    // SRV 생성 (데이터 타입을 DXGI_FORMAT_R32G32_FLOAT으로 설정)
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format = DXGI_FORMAT_R32G32_FLOAT;  // float2를 사용하므로 R32G32_FLOAT 사용
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
    srvDesc.Buffer.ElementWidth = numElements;

    hr = DEVICE->CreateShaderResourceView(buffer, &srvDesc, &srv);
    if (FAILED(hr))
    {
        MessageBox(nullptr, L"SRV Creation Failed!", L"Error", MB_OK);
        if (buffer) buffer->Release();
        return;  // 초기화 실패 시 리턴
    }
}

StructuredBuffer::~StructuredBuffer()
{
    if (srv) srv->Release();
    if (buffer) buffer->Release();
}

void StructuredBuffer::UpdateBuffer()
{
    DC->UpdateSubresource(buffer, 0, nullptr, data, 0, 0);
}

void StructuredBuffer::SetVS(UINT slot)
{
    DC->VSSetShaderResources(slot, 1, &srv);
}

void StructuredBuffer::SetPS(UINT slot)
{
    DC->PSSetShaderResources(slot, 1, &srv);
}

void StructuredBuffer::UpdateData(void* newData)
{
    data = newData;
    DC->UpdateSubresource(buffer, 0, nullptr, newData, 0, 0);
}
