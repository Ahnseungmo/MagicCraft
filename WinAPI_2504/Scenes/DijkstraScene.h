#pragma once

class DijkstraScene : public Scene
{
public:
	DijkstraScene();
	~DijkstraScene();	

	void Update() override;
	void Render() override;

private:
	Dijkstra* dijkstra = nullptr;
	Tank* tank;
};