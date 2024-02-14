#include "TestScene.h"
#include "Player.h"
#include "Bird.h"
#include "Field.h"
#include"Camera.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
	Instantiate<Camera>(this);
	Instantiate<Field>(this);
	//Instantiate<Bird>(this);
	Instantiate<Player>(this);
	
}

//�X�V
void TestScene::Update()
{
}

//�`��
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
}
