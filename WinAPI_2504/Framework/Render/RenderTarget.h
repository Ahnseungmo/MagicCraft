#pragma once

class RenderTarget
{
public:
	RenderTarget(UINT width = SCREEN_WIDTH, UINT height = SCREEN_HEIGHT);
	~RenderTarget();

	virtual void Set(Float4 clearColor = Float4(1, 1, 1, 1));

	
    ID3D11ShaderResourceView* GetSRV() { return srv; }

private:
    void CreateRTVTexture();
    void CreateRTV();
    void CreateSRV();
    void CreateProjection();

    void CreateDSV();

private:
    UINT width, height;

    ID3D11Texture2D* rtvTexture;
    ID3D11RenderTargetView* rtv;
    ID3D11ShaderResourceView* srv;

    ID3D11Texture2D* dsvTexture = nullptr;
    ID3D11DepthStencilView* dsv = nullptr;

    MatrixBuffer* projectionBuffer;
};