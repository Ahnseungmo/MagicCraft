#pragma once

class Cookie : public RectCollider
{
private:
	enum ActionState
	{
		Run, Roll, Idle, Dead, Attack
	};

public:
	Cookie();
	~Cookie();

	void Update();
	void Render();
	void Edit();

private:
	void CreateClips();
	void LoadClip(string path, string file, bool isLoop, float speed = 1.0f);

	void SetIdle();

	void StartAttack();
	void EndAttack();	

private:
	ActionState curState = Run;

	Transform* clipTransform;
	MatrixBuffer* worldBuffer;

	vector<Clip*> clips;	

	RectCollider* attackCollider;

	Texture* secondMap;
	FloatValueBuffer* valueBuffer;
};