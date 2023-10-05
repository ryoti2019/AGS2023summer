#pragma once
#include <vector>
#include "../Utility/AsoUtility.h"
#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"
#include "MeteorChild.h"

class Player;
class GameScene;

class Meteor
{

public:

	// �e�̐�������
	static constexpr float SHOT_ALIVE = 3.0f;

	// ���e�I�̃T�C�Y
	static constexpr int SIZE_X = 64;
	static constexpr int SIZE_Y = 64;

	// �����̃A�j���[�V������
	static constexpr int BLAST_ANIM_NUM = 4;

	// �R���X�g���N�^
	Meteor(int* imgs, int imgNum);

	// �f�X�g���N�^
	~Meteor(void);

	void Init(GameScene* scene);

	void Update(void);

	void Draw(void);

	void Release(void);

	// ���W�̎擾
	Vector2 GetPos(void);

	// ���W�̐ݒ�
	void SetPos(Vector2 pos);

	// 覐΂̎擾
	std::vector<Meteor*> GetMeteors(void);

	// 覐΂̎q�擾
	std::vector<MeteorChild*> GetMeteorChildlen(void);

private:

	// �Q�[���V�[���̃|�C���^�ϐ�
	GameScene* gameScene_;

	// 覐�
	std::vector<Meteor*> meteors_;

	// 覐΂̎q
	std::vector<MeteorChild*> children_;

	// 覐΂̐���
	MeteorChild* GetValidMeteor(void);

	// ���W
	Vector2 pos_;

	int step_;

	int nextStep_;

	// �摜
	int* imgs_;
	int imgNum_;

	// �A�j���[�V�����̃f�[�^
	int animData_[4];

	// �A�j���[�V�����̃J�E���g
	int cntAnim_;


};

