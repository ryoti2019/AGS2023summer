#pragma once
#include "../Scene/GameScene.h"
#include "../Utility/AsoUtility.h"
#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"

class RockChild
{

public:

	// ����󂷐�
	static constexpr int ROCK_NUM = 100;

	// ��̃T�C�Y
	static constexpr int SIZE_X = 32;
	static constexpr int SIZE_Y = 32;

	// �R���X�g���N�^
	RockChild(int img);

	// �f�X�g���N�^
	~RockChild(void);

	// ��̐���
	void CreateRock(Vector2 pos);

	void Update(void);

	void Draw(void);

	void Release(void);

	// ��������
	bool IsAlive(void);

	// ���W�̎擾
	Vector2 GetPos(void);

	// ��������̐ݒ�
	void SetAlive(bool alive);

private:

	// ����
	Vector2F dir_;

	// ���W
	Vector2 pos_;

	// ��̉摜
	int image_;

	// ��������
	bool isAlive_;



};

