#include "Player.h"
#include <DxLib.h>
#include <assert.h>
#include"Stone.h"
#include"Camera.h"
#include"Field.h"
#include"Bird.h"
#include"TestScene.h"
namespace
{
	const float MOVE_SPEED = 4.0f;
	const float GROUND = 400.0f;
	const float JUMP_HEIGHT = 64.0f * 4.0f;//ジャンプの高さ
	const float GRAVITY = 9.8f / 60.0f;//重力加速度
	/*Memo const float JUMP = -12.0f;
	const float GRAVITY = 0.5f;
	XMFLOAT3 JumpSpeed{ 0,0,0 };*/
}
Player::Player(GameObject* parent) : GameObject(sceneTop)
{
	hImage = LoadGraph("Assets/aoi.png");
	assert(hImage > 0);
	transform_.position_.x = 100.0f;
	transform_.position_.y = GROUND;
	jumpSpeed = 0.0f;
	onGround = true;
	frameCounter = 0;
	animType = 0;
	animFrame = 0;
	state = S_Walk;
}

Player::~Player()
{
	if (hImage > 0)
	{
		DeleteGraph(hImage);
	}
}

void Player::Update()
{
	Field* pField = GetParent()->FindGameObject<Field>();
	if (state == S_Cry)
	{
		frameCounter++;
		if (frameCounter >= 4)
		{
			frameCounter = 0;
			animFrame = (animFrame + 1) % 2;
		}
		return;
	}
	TestScene* scene = dynamic_cast<TestScene*>(GetParent());
	if (!scene->CanMove())
		return;
	//移動
	if (CheckHitKey(KEY_INPUT_D))
	{
		transform_.position_.x += MOVE_SPEED;
		if (++frameCounter >= 8) {
			animFrame = (animFrame + 1) % 4;
			frameCounter = 0;
		}
		int hitX = transform_.position_.x + 50;
		int hitY = transform_.position_.y + 63;
		
		if (pField != nullptr)
		{
			int push = pField->CollisionRight(hitX, hitY);
			transform_.position_.x -= push;
		}
	}
	else if (CheckHitKey(KEY_INPUT_A))
	{
		transform_.position_.x -= MOVE_SPEED;
		if (++frameCounter >= 8) {
			animFrame = (animFrame + 1) % 4;
			frameCounter = 0;
		}
	}
	else
	{
		animFrame = 0;
		frameCounter = 0;
	}


	//ジャンプ
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		//Memo transform_.position_.y += JUNP;
		if (prevSpaceKey == false) {
			if (onGround) {
				jumpSpeed = -sqrt(2 * GRAVITY * JUMP_HEIGHT);
				onGround = false;
			}
		}
		prevSpaceKey = true;
	}
	else
	{
		prevSpaceKey = false;
	}
	jumpSpeed += GRAVITY;//速度　+= 加速度
	transform_.position_.y += jumpSpeed;//座標　+=　速度
	if (pField != nullptr)
	{
		int pushR = pField->CollisionDown(transform_.position_.x + 50, transform_.position_.y + 63);
		int pushL = pField->CollisionDown(transform_.position_.x + 14, transform_.position_.y + 63);
		int push = max(pushR, pushL);//２つの足元のめりこみの大きいほう
		if (push >=1 ) {
			transform_.position_.y -= push - 1;
			jumpSpeed = 0.0f;
			onGround = true;
		}else{
			onGround = false;
		}

	}
	/*if (transform_.position_.y >= GROUND)
	{
		transform_.position_.y = GROUND;
		jumpSpeed = 0.0f;
		onGround = true;
	}*/
	/*Memo else
	{
		if (transform_.position_.y  GROUND)
		{
			JumpSpeed.y += GRAVITY;
			transform_.position_.y += JumpSpeed.y;
			if (JumpSpeed.y < 0)
			{
				JumpSpeed.y *= 0.9;
			}
		}
	}*/
	//石
	if (CheckHitKey(KEY_INPUT_M))
	{
		Stone* st = Instantiate<Stone>(GetParent());
		st->SetPosition(transform_.position_);
	}
	//鳥
	std::list<Bird*> pBirds = GetParent()->FindGameObjects<Bird>();
	for (Bird* pBird :pBirds)
	{
		if (pBird->ColliderCircle(transform_.position_.x + 32.0f, transform_.position_.y + 32.0f, 20.0f))
		{
			//transform_.position_.y = 0;
			animType = 4;
			animFrame = 0;
			state = S_Cry;
			scene->StartDead();
		}
	}
	//カメラ
	Camera* cam = GetParent()->FindGameObject<Camera>();
	int x = (int)transform_.position_.x - cam->GetValue();
	if (x > 400)
	{
		x = 400;
		cam->SetValue((int)transform_.position_.x-x);
	}
}

void Player::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
	{
		x -= cam->GetValue();
	}
	DrawRectGraph(x, y, animFrame*64, 0, 64, 64, hImage, TRUE);
}

void Player::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}
