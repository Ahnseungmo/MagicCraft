#include "Framework.h"

Orc3::Orc3()
{
	string path = "Resources/Textures/MagicCraft/Character/Enemys/Orc3/";

	LoadClip(Idle,	Up,		path, "Orc1_Idle_Up.xml", true, 1.0f);
	LoadClip(Idle,	Down,	path, "Orc1_Idle_Down.xml", true, 1.0f);
	LoadClip(Idle,	Left,	path, "Orc1_Idle_Left.xml", true, 1.0f);
	LoadClip(Idle,	Right,	path, "Orc1_Idle_Right.xml", true, 1.0f);

	LoadClip(Walk, Up, path, "Orc1_Walk_Up.xml", true, 1.0f);
	LoadClip(Walk, Down, path, "Orc1_Walk_Down.xml", true, 1.0f);
	LoadClip(Walk, Left, path, "Orc1_Walk_Left.xml", true, 1.0f);
	LoadClip(Walk, Right, path, "Orc1_Walk_Right.xml", true, 1.0f);

	LoadClip(Run, Up, path,	"Orc1_Run_Up.xml", true, 1.0f);
	LoadClip(Run, Down, path,	"Orc1_Run_Down.xml", true, 1.0f);
	LoadClip(Run, Left, path,	"Orc1_Run_Left.xml", true, 1.0f);
	LoadClip(Run, Right, path, "Orc1_Run_Right.xml", true, 1.0f);

	LoadClip(ATTACK, Up, path, "Orc1_Attack_Up.xml", false, 1.0f);
	LoadClip(ATTACK, Down, path, "Orc1_Attack_Down.xml", false, 1.0f);
	LoadClip(ATTACK, Left, path, "Orc1_Attack_Left.xml", false, 1.0f);
	LoadClip(ATTACK, Right, path, "Orc1_Attack_Right.xml", false, 1.0f);

	LoadClip(Hurt, Up, path, "Orc1_Hurt_Up.xml", false, 1.0f);
	LoadClip(Hurt, Down, path, "Orc1_Hurt_Down.xml", false, 1.0f);
	LoadClip(Hurt, Left, path, "Orc1_Hurt_Left.xml", false, 1.0f);
	LoadClip(Hurt, Right, path, "Orc1_Hurt_Right.xml", false, 1.0f);


	LoadClip(Death, Up, path, "Orc1_Death_Up.xml", false, 1.0f);
	LoadClip(Death, Down, path, "Orc1_Death_Down.xml", false, 1.0f);
	LoadClip(Death, Left, path, "Orc1_Death_Left.xml", false, 1.0f);
	LoadClip(Death, Right, path, "Orc1_Death_Right.xml", false, 1.0f);

	for (int i = 0;i < 4;i++) {
		motionClips[ATTACK][(Direction)i]->SetEvent(bind(&Enemy::EndAttack,this));
	}

	clipTransform->SetParent(this);
	float imageY = motionClips[Idle][Up]->GetCurFrame()->GetSize().y;
	clipTransform->SetLocalPosition(0, -Radius() + imageY / 2);

	clipTransform->UpdateWorld();


	hpMax = 45;
	hp = hpMax;
}

Orc3::~Orc3()
{
	for (auto& clips : motionClips) {
		for (auto& clip : clips.second) {
			delete clip.second;
		}
		clips.second.clear();
	}
	motionClips.clear();
}
