#include "Player.h"
#include <DxLib.h>
#include <assert.h>
#include"Stone.h"
#include"Camera.h"
namespace
{
	const float MOVE_SPEED = 4.0f;
	const float GROUND = 400.0f;
	const float JUMP_HEIGHT = 64.0f * 4.0f;//�W�����v�̍���
	const float GRAVITY = 9.8f / 60.0f;//�d�͉����x
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
	//�ړ�
	if (CheckHitKey(KEY_INPUT_D))
	{
		transform_.position_.x += MOVE_SPEED;
		if (++frameCounter >= 8) {
			animFrame = (animFrame + 1) % 4;
			frameCounter = 0;
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


	//�W�����v
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
	jumpSpeed += GRAVITY;//���x�@+= �����x
	transform_.position_.y += jumpSpeed;//���W�@+=�@���x

	if (transform_.position_.y >= GROUND)
	{
		transform_.position_.y = GROUND;
		jumpSpeed = 0.0f;
		onGround = true;
	}
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

	if (CheckHitKey(KEY_INPUT_M))
	{
		Stone* st = Instantiate<Stone>(GetParent());
		st->SetPosition(transform_.position_);
	}
	Camera* cam = GetParent()->FindGameObject<Camera>();
	cam->SetValue(cam->GetValue() + 1);
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
