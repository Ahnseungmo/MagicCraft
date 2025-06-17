#pragma once

class Environment : public Singleton<Environment>
{
	friend class Singleton;

private:
	Environment();
	~Environment();

public:
	void Update();

	void SetViewport(UINT width = SCREEN_WIDTH, UINT height = SCREEN_HEIGHT);
	void SetUIViewBuffer();

	Camera* GetMainCamera() { return mainCamera; }
private:
	void CreateProjection();
	void CreateSamplerState();
	void CreateBlendState();

private:
	Camera* mainCamera;
	MatrixBuffer* projectionBuffer;
	MatrixBuffer* uiViewBuffer;

	ID3D11SamplerState* samplerState;
	ID3D11BlendState* alphaBlendState;	
};