#pragma once

class InstancingScene : public Scene
{
private:
	const UINT SIZE = 100;

public:
	InstancingScene();
	~InstancingScene();	

	void Update() override;
	void Render() override;

public:
	//vector<Quad*> quads;

	Quad* quad;

	vector<InstanceData> instances;
	VertexBuffer* instanceBuffer;
};