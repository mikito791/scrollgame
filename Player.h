#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// プレイヤーキャラ
/// </summary>
class Player : public GameObject
{
public:
	Player(GameObject* scene);
	~Player();
	void Update() override;
	void Draw() override;
	void SetPosition(int x, int y);
private:
	int hImage;
	GameObject* sceneTop;

	bool prevSpaceKey;
	float jumpSpeed;
	bool onGround;

	int animType;//状況
	int animFrame;//コマ
	int frameCounter;

	enum State
	{
		S_Walk=0,
		S_Cry,
	};
	State state;
};