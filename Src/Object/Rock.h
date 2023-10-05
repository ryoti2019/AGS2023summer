#pragma once
#include <vector>
#include "../Manager/InputManager.h"
#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"
#include "RockChild.h"

class GameScene3;

class Rock
{

public:

	// ����󂷐�
	static constexpr int ROCK_NUM = 100;

	// ��̃T�C�Y
	static constexpr int SIZE_X = 64;
	static constexpr int SIZE_Y = 64;

	// �R���X�g���N�^
	Rock(int img);

	// �f�X�g���N�^
	~Rock(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	// ���W�̎擾
	Vector2 GetPos(void);

	// ���W�̐ݒ�
	void SetPos(Vector2 pos);

	// �����t���O�̎擾
	bool IsAlive(void);

	// �����t���O�̐ݒ�
	void SetAlive(bool isAlive);

	// Shot�̎擾
	std::vector<RockChild*> GetRockChild(void);

	// ����󂵂��瑫��
	void AddCnt(int i);

	// ����󂵂����̎擾
	int GetRockCount(void);

private:

	// 覐΂̎q
	std::vector<RockChild*> children_;

	// ���W
	Vector2 pos_;

	// ��̉摜
	int image_;

	// �����t���O
	bool isAlive_;

	int cnt_;

	// ����󂵂���
	int rockConter_;

};

