#pragma once
#include "Engine/GameObject.h"

//�e�X�g�V�[�����Ǘ�����N���X
class TestScene : public GameObject
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TestScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	bool CanMove();
private:
	enum State {
		S_Ready,//Ready�\�����i2�b�ԃX�^�[�g��\���j
		S_Play,//�Q�[����
		S_Clear,//�Q�[���N���A�i�N���A��\�����ă{�^�����������܂őҋ@�j
		S_Dead,//���S�i�Q�[���I�[�o�[��\�����ă{�^�����������܂őҋ@�j
	};
	State state; //�X�e�[�g�̒l��\��
	void StartReady();
	void UpdateReady();
	void StartPlay();
	void UpdatePlay();
	void UpdateClear();
public:
	void StartDead();
private:
	void UpdateDead();

	float readyTimer;
};