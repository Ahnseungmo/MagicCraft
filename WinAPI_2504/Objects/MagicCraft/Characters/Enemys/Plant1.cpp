#include "Framework.h"

Plant1::Plant1()
{
	string path = "Resources/Textures/MagicCraft/Character/Enemys/Plant1/";

	LoadClip(Idle,	Up,		path, "Plant1_Idle_Up.xml", true, 1.0f);
	LoadClip(Idle,	Down,	path, "Plant1_Idle_Down.xml", true, 1.0f);
	LoadClip(Idle,	Left,	path, "Plant1_Idle_Left.xml", true, 1.0f);
	LoadClip(Idle,	Right,	path, "Plant1_Idle_Right.xml", true, 1.0f);

	LoadClip(Walk, Up, path, "Plant1_Walk_Up.xml", true, 1.0f);
	LoadClip(Walk, Down, path, "Plant1_Walk_Down.xml", true, 1.0f);
	LoadClip(Walk, Left, path, "Plant1_Walk_Left.xml", true, 1.0f);
	LoadClip(Walk, Right, path, "Plant1_Walk_Right.xml", true, 1.0f);

	LoadClip(Run, Up, path,	"Plant1_Run_Up.xml", true, 1.0f);
	LoadClip(Run, Down, path,	"Plant1_Run_Down.xml", true, 1.0f);
	LoadClip(Run, Left, path,	"Plant1_Run_Left.xml", true, 1.0f);
	LoadClip(Run, Right, path, "Plant1_Run_Right.xml", true, 1.0f);

	LoadClip(ATTACK, Up, path, "Plant1_Attack_Up.xml", false, 1.0f);
	LoadClip(ATTACK, Down, path, "Plant1_Attack_Down.xml", false, 1.0f);
	LoadClip(ATTACK, Left, path, "Plant1_Attack_Left.xml", false, 1.0f);
	LoadClip(ATTACK, Right, path, "Plant1_Attack_Right.xml", false, 1.0f);

	LoadClip(Hurt, Up, path, "Plant1_Hurt_Up.xml", false, 1.0f);
	LoadClip(Hurt, Down, path, "Plant1_Hurt_Down.xml", false, 1.0f);
	LoadClip(Hurt, Left, path, "Plant1_Hurt_Left.xml", false, 1.0f);
	LoadClip(Hurt, Right, path, "Plant1_Hurt_Right.xml", false, 1.0f);


	LoadClip(Death, Up, path, "Plant1_Death_Up.xml", false, 1.0f);
	LoadClip(Death, Down, path, "Plant1_Death_Down.xml", false, 1.0f);
	LoadClip(Death, Left, path, "Plant1_Death_Left.xml", false, 1.0f);
	LoadClip(Death, Right, path, "Plant1_Death_Right.xml", false, 1.0f);

	for (int i = 0;i < 4;i++) {
		motionClips[ATTACK][(Direction)i]->SetEvent(bind(&Enemy::EndAttack,this));
	}

	clipTransform->SetParent(this);
	float imageY = motionClips[Idle][Up]->GetCurFrame()->GetSize().y;
	clipTransform->SetLocalPosition(0, -Radius() + imageY / 2);

	clipTransform->UpdateWorld();
}

Plant1::~Plant1()
{
	for (auto& clips : motionClips) {
		for (auto& clip : clips.second) {
			delete clip.second;
		}
		clips.second.clear();
	}
	motionClips.clear();
}
