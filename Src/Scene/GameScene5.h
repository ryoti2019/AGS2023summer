#pragma once
#include "SceneBase.h"
#include "../Common/Vector2F.h"
#include "../Utility/AsoUtility.h"

class SceneManager;
class Player5;
class Stage;
class Shot;
class StartMes;
class ResultScene;

class GameScene5 : public SceneBase
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

	enum class DIR
	{
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

	// �R���X�g���N�^
	GameScene5(void);

	// �f�X�g���N�^
	~GameScene5(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	// �S���̓��͂��I�������true�ɂȂ�
	bool GetInputEnd(void);

	void SetInputEnd(bool inputEnd);

	// �����̎擾
	std::vector<int> GetDir(void);

	// ���ɗv�f���𑫂�
	void SetPushBack(bool pushback);

	// �摜�̕\������
	int GetImageTime(void);

	// �����Ă���v���C���[�Ƀt���O�����킹��
	bool GetPlayerInput(void);

	// ������\�������鎞��
	int GetAnswerTime(void);

	// ������\�����鎞�Ԃ��I�������
	bool GetIsAnswer(void);

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
	std::vector<Player5*> players_;

	// �X�^�[�g���b�Z�[�W
	StartMes* startMes_;

	// ���U���g
	ResultScene* resultScene_;

	// �X�e�[�W
	Stage* stage_;

	// �v���C���[�̉摜
	int playerImg_[PLAYER_MAX_NUM_ANIM];

	// ����
	Vector2 dir_;

	// ����
	std::vector<int> direction_;

	// ���͂��Ȃ��Ƃ����Ȃ���
	int pushMax_;

	// ���͂�����
	int pushCnt_;

	// ���������߂�O�̃t���O
	bool dirAlive_;

	// �f�o�b�O�`��
	void DrawDebug(void);

	// �S���̓��͂��I�������true�ɂȂ�
	bool inputEnd_;

	// ���ɗv�f���𑫂�
	bool pushBack_;

	// �w�i�摜
	int bgImage_;

	// ���摜
	int kokubanImage_;

	// ���̉摜
	int arrowImage_;

	// �摜���o�鎞��
	int imageTime_;

	int cnt_;

	// �����Ă�v���C���[�Ƀt���O�����킹��
	bool playerInput_;

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

	// ���͂���̉摜
	int nyuuryokusiro_;

	// �������킹�̃J�E���^
	int answerCnt_;

	// ������\�������鎞��
	int answerTime_;

	// ������\�������I�����
	bool isAnswer_;

	// �_���[�W��H�炢�I�����
	bool damage_;

	// ��肪�o���ꂽ�Ƃ��̉�
	int questionSE_;

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

	// �������Ƃ������𑫂�
	bool win_;

};

