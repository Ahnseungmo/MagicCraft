#include "Framework.h"

RenderTarget::RenderTarget(UINT width, UINT height)
    : width(width), height(height)
{
    CreateRTVTexture();
    CreateRTV();
    CreateSRV();
    CreateDSV();
    CreateProjection();
}

RenderTarget::~RenderTarget()
{
    rtvTexture->Release();
    rtv->Release();
    if (dsvTexture) dsvTexture->Release();
    if (dsv) dsv->Release();
    delete projectionBuffer;
}

void RenderTarget::Set(Float4 clearColor)
{
    DC->OMSetRenderTargets(1, &rtv, dsv);

    DC->ClearRenderTargetView(rtv, (float*)&clearColor);
    DC->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH, 1.0f, 0);//
    Environment::Get()->SetViewport(width, height);
    projectionBuffer->SetVS(2);
}

void RenderTarget::CreateRTVTexture()
{
    D3D11_TEXTURE2D_DESC desc = {};
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;

    DEVICE->CreateTexture2D(&desc, nullptr, &rtvTexture);
}

void RenderTarget::CreateRTV()
{
    D3D11_RENDER_TARGET_VIEW_DESC desc = {};
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

    DEVICE->CreateRenderTargetView(rtvTexture, &desc, &rtv);
}

void RenderTarget::CreateSRV()
{
    D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    desc.Texture2D.MipLevels = 1;

    DEVICE->CreateShaderResourceView(rtvTexture, &desc, &srv);
}

void RenderTarget::CreateProjection()
{
    Matrix orthographic = XMMatrixOrthographicOffCenterLH(
        0.0f, width, 0.0f, height, -1.0f, 1.0f);

    projectionBuffer = new MatrixBuffer();
    projectionBuffer->Set(orthographic);
}
void RenderTarget::CreateDSV()
{
    D3D11_TEXTURE2D_DESC depthDesc = {};
    depthDesc.Width = width;
    depthDesc.Height = height;
    depthDesc.MipLevels = 1;
    depthDesc.ArraySize = 1;
    depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthDesc.SampleDesc.Count = 1;
    depthDesc.Usage = D3D11_USAGE_DEFAULT;
    depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

    DEVICE->CreateTexture2D(&depthDesc, nullptr, &dsvTexture);

    D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
    dsvDesc.Format = depthDesc.Format;
    dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

    DEVICE->CreateDepthStencilView(dsvTexture, &dsvDesc, &dsv);
}