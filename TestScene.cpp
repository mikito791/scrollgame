#include "TestScene.h"
#include "Player.h"
#include "Bird.h"
#include "Field.h"
#include"Camera.h"
#include"Banner.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
	
}

//������
void TestScene::Initialize()
{
	Instantiate<Camera>(this);
	Field* pField=Instantiate<Field>(this);
	//Instantiate<Bird>(this);
	Instantiate<Player>(this);
	pField->Reset();
	Instantiate<Banner>(this);
	
}

//�X�V
void TestScene::Update()
{
	switch (state) {
	case S_Ready: UpdateReady(); break;
	case S_Play: UpdatePlay(); break;
	case S_Clear: UpdateClear(); break;
	case S_Dead: UpdateDead(); break;
	}
}

//�`��
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
}

bool TestScene::CanMove()
{
	return (state == S_Play);
}

void TestScene::StartReady()
{
	state = S_Ready;
	readyTimer = 2.0f;//Ready�̕\������
	Banner* bn = FindGameObject<Banner>();
	bn->View(Banner::ViewID::V_Start);
}

void TestScene::UpdateReady()
{
	readyTimer -= 1.0f / 60.0;
	if (readyTimer <= 0.0f) {
		StartPlay();
	}
}

void TestScene::StartPlay()
{
	state = S_Play;
	Banner* bn = FindGameObject<Banner>();
	bn->View(Banner::ViewID::V_Noting);
}

void TestScene::UpdatePlay()
{
}

void TestScene::UpdateClear()
{
}

void TestScene::StartDead()
{
	state = S_Dead;
	Banner* bn = FindGameObject<Banner>();
	bn->View(Banner::ViewID::V_GameOver);
}

void TestScene::UpdateDead()
{
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		StartReady();
	}
}
