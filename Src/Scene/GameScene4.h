#pragma once
#include "SceneBase.h"
#include "../Common/Vector2F.h"
#include "../Utility/AsoUtility.h"

class Player4;
class Stage2;
class StartMes;
class ResultScene;

class GameScene4 : public SceneBase
{

public:

	// �v���C���[�̍ő�A�j���[�V����
	static constexpr int PLAYER_MAX_NUM_ANIM = 12;

	// �v���C���[�̃T�C�Y
	static constexpr int PLAYER_SIZE_X = 100;
	static constexpr int PLAYER_SIZE_Y = 100;

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

	// L�X�e�B�b�N�̍ő�A�j���[�V����
	static constexpr int STICK_MAX_NUM_ANIM = 8;

	// L�X�e�B�b�N�̃T�C�Y
	static constexpr int STICK_SIZE_X = 32;
	static constexpr int STICK_SIZE_Y = 32;

	// L�X�e�B�b�N�̏c���̕�����
	static constexpr int STICK_NUM_X = 8;
	static constexpr int STICK_NUM_Y = 1;

	// �R���X�g���N�^
	GameScene4(void);

	// �f�X�g���N�^
	~GameScene4(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	// ���[���h(�X�N���[��)���W���}�b�v���W�ɕϊ�����
	Vector2 World2MapPos(Vector2 worldPos);

	// �}�b�v�`�b�v���g�p�����Փ˔���
	bool IsCollisionStage(Vector2 worldPos);

	// �X�e�[�W�̎擾
	Stage2* GetStage(void);

	// ���̎擾
	bool GetL(void);

	// ���̐ݒ�
	void SetL(bool left);

	// �E�̎擾
	bool GetR(void);

	// ���̐ݒ�
	void SetR(bool right);

	// �J�E���^�̎擾
	int GetCnt(void);

	// ���U���g�̎擾
	bool GetResult(void);

	// �X�L�b�v�̎擾
	bool GetSkip(void);

	// �X�^�[�g�̏��
	bool IsStart(void);

	void SetInputNum(int input);

	void SetStartNum(int start);

	bool GetRevival(void);

private:

	// �v���C���[
	std::vector<Player4*> players_;

	// �X�^�[�g���b�Z�[�W
	StartMes* startMes_;

	// ���U���g
	ResultScene* resultScene_;

	// �X�e�[�W
	Stage2* stage_;

	// �v���C���[�̉摜
	int playerImg_[PLAYER_MAX_NUM_ANIM];

	// ����
	Vector2 dir_;

	// ���̃t���O
	bool left_;

	// �E�̃t���O
	bool right_;

	int lr_[2];

	// ���E�̔�����n�߂�p
	bool start_;

	// ���E�̔�����n�߂�p�̃J�E���^
	int startCnt_;

	// �J�E���g�_�E���̃J�E���^��������Ă������̃t���O
	bool startCntStart_;

	// �J�E���g�_�E���̉摜
	int count1_;
	int count2_;
	int count3_;
	int count4_;
	int count5_;

	// �J�E���g�_�E���̃J�E���^
	int downCnt_;

	// �J�E���g�_�E���̃J�E���^��������Ă������̃t���O
	bool downCntStart_;

	// �Q�[�������p�̉摜
	int expImage_;

	// �Q�[���������X�L�b�v���邽�߂̃t���O
	bool skip_;

	// ���艹
	int decideSE_;

	// B�{�^���̉摜
	int BbottonImage_[BOTTON_MAX_NUM_ANIM];

	// L�X�e�B�b�N�̉摜
	int LstickIMage_[STICK_MAX_NUM_ANIM];

	// �A�j���[�V�����̃J�E���^
	int cntAnim_;

	// BGM
	int bgm_;

	// �_���[�W��H��������̉�
	int damageSE_;

	// �g�Q�̉�
	int spinaSE_;

	// �J�E���g�_�E���̉�
	int countDownSE_;

	// �I�ׂ̉摜
	int erabe_;

	// �U�����󂯂�Ƃ��Ƀv���C���[�̓������~�߂鎞��
	int notOperationTime_;

	// �����_���Ɍ��߂�����
	int random_;

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

	// ���������Ƃ��̃t���O
	bool revival_;

	// ���������Ƃ���HP�𑝂₷�t���O
	bool revivalHP_;

	// �����_���ɐ�����1��I��
	bool isRand1_;
	bool isRand2_;
	bool isRand3_;
	bool isRand4_;

	// �����_���Ɍ��܂������̑���
	int inputRandNum_;

	// �����_��
	void Rand(void);

	// �S���̃T�C�R���̉摜
	int allDice_[6];

	// 1���̃T�C�R���̉摜
	int dice1_;
	int dice2_;
	int dice3_;
	int dice4_;
	int dice5_;
	int dice6_;

	// �T�C�R����U��
	int saikoro_;

	bool win_;

};

