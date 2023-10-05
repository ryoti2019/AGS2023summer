#pragma once
#include "SceneBase.h"
#include "../Common/Vector2F.h"
#include "../Utility/AsoUtility.h"

class Player3;
class Stage;
class Shot;
class Rock;
class RockChild;
class StartMes;

class GameScene3 : public SceneBase
{

public:

	// �v���C���[�̍ő�A�j���[�V����
	static constexpr int PLAYER_MAX_NUM_ANIM = 12;

	// �v���C���[�̃T�C�Y
	static constexpr int PLAYER_SIZE_X = 32;
	static constexpr int PLAYER_SIZE_Y = 32;

	// �v���C���[�̏c���̕�����
	static constexpr int PLAYER_NUM_X = 3;
	static constexpr int PLAYER_NUM_Y = 4;

	// B�{�^���̍ő�A�j���[�V����
	static constexpr int BOTTON_MAX_NUM_ANIM = 4;

	// B�{�^���̃T�C�Y
	static constexpr int BOTTON_SIZE_X = 32;
	static constexpr int BOTTON_SIZE_Y = 32;

	// �{�^���̏c���̕�����
	static constexpr int BOTTON_NUM_X = 4;
	static constexpr int BOTTON_NUM_Y = 1;

	// �R���X�g���N�^
	GameScene3(void);

	// �f�X�g���N�^
	~GameScene3(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	// ���U���g�̎擾
	bool GetResult(void);

	// �X�L�b�v�̎擾
	bool GetSkip(void);

	// �X�^�[�g�̏��
	bool IsStart(void);

	void SetInputNum(int input);

	void SetStartNum(int start);

private:

	// �v���C���[
	std::vector<Player3*> players_;

	// ��
	std::vector<Rock*> rocks_;

	// �X�^�[�g���b�Z�[�W
	StartMes* startMes_;

	// �X�e�[�W
	Stage* stage_;

	// �v���C���[�̉摜
	int playerImg_[PLAYER_MAX_NUM_ANIM];

	// ��̉摜
	int rockImg_;

	// ����
	Vector2 dir_;

	// �Փ˔���
	void Collision(void);

	// �Փ˔���
	bool IsCollisionRect(Vector2 stPos1, Vector2 edPos1, Vector2 stPos2, Vector2 edPos2);

	// �Փ˔���
	bool IsCollisionRectCenter(Vector2 centerPos1, Vector2 size1, Vector2 centerPos2, Vector2 size2);

	// �w�i�摜
	int bgImage_;

	// �Q�[�������p�̉摜
	int expImage_;

	// �Q�[���������X�L�b�v���邽�߂̃t���O
	bool skip_;

	// ���艹
	int decideSE_;

	// B�{�^���̉摜
	int BbottonImage_[BOTTON_MAX_NUM_ANIM];

	// �A�j���[�V�����̃J�E���^
	int cntAnim_;

	// BGM
	int bgm_;

	// ������
	int explosionSE_;

	// �A�ł���
	int renndasiroImage_;

	// ���U���g
	void Result(void);

	// ���U���g�̃t���O
	bool result_;

	// �����摜
	int winImage1_;
	int winImage2_;
	int winImage3_;
	int winImage4_;

	// ���͂��ꂽ����
	int inputNum_;

	// �v���C���[���Ƃɓ��͂�����
	bool inputPlayer1_;
	bool inputPlayer2_;
	bool inputPlayer3_;
	bool inputPlayer4_;

	// �X�^�[�g�̉摜
	int startImage_;

	// �X�^�[�g���邽�߂̓���
	int startNum_;

	bool isStart_;

	// �v���C���[��OK�摜�̓ǂݍ���
	int OKImage1_;
	int OKImage2_;
	int OKImage3_;
	int OKImage4_;

	// �������Ƃ������𑫂�
	bool win_;
};


