#pragma once
#include "../Utility/AsoUtility.h"
#include "../Common/Vector2.h"
#include "../Manager/InputManager.h"
#include "../Scene/GameScene5.h"

class Player5
{

public:

	// �v���C���[�̍ő�A�j���[�V����
	static constexpr int PLAYER_MAX_NUM_ANIM = 3;

	// �v���C���[�̃T�C�Y
	static constexpr int PLAYER_SIZE_X = 100;
	static constexpr int PLAYER_SIZE_Y = 100;

	// �v���C���[�̏c���̕�����
	static constexpr int NUM_X = 3;
	static constexpr int NUM_Y = 4;

	// �I�񂾕���
	enum class DIR
	{
		UP = 1,
		RIGHT = 2,
		DOWN = 3,
		LEFT = 4
	};

	// �R���X�g���N�^
	Player5();

	// �f�X�g���N�^
	~Player5(void);

	void Init(GameScene5* scene, InputManager::JOYPAD_NO playerNo);
	void Update(void);
	void Draw(void);
	void Release(void);

	// ���W�̎擾
	Vector2 GetPos(void);

	// ���W�̃Z�b�^�[
	void SetPos(Vector2 pos);

	// ��������̎擾
	bool IsAlive(void);

	// ��������̐ݒ�
	void SetAlive(bool alive);

	// �P�O�̐�������̎擾
	bool OldAlive(void);

	// �����̎擾
	std::vector<int> GetDir(void);

	// ���͂��Ȃ��Ƃ����Ȃ���
	int GetPushMax(void);

	// HP�̎擾
	int GetHP(void);

	// HP�̐ݒ�
	void SetHP(int hp);

	// ���͂�������
	bool GetinputAlive(void);

	// �ő�l���`�悪�ł�����
	int GetArrowCnt(void);

	// �ő�l���̕`���0�ɂ���
	void SetArrowCnt(int cnt);

	// �_���[�W��H�������
	bool GetDamage(void);

	// �X�^�[�g���̓��͏��
	bool GetInputStart(void);

	// ���֐i�ނƂ��̓��͏��
	bool GetInputPlayer(void);

	// �����_���̐������擾
	int GetRandNumber(void);

	// �����_���̐�����ݒ肷��
	void SetRandNumber(int rand);

	// ������{�^�������������̔���
	bool GetInputRevival(void);

private:

	// �Q�[���V�[���̃|�C���^�ϐ�
	GameScene5* gameScene_;

	// �v���C���[�̉摜
	int playerImg_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM];

	// �v���C���[�̍��W
	Vector2 pos_;

	// ���S���W
	Vector2 centerPos_;

	// ����
	AsoUtility::DIR dir_;

	// �A�j���[�V�����̃f�[�^
	int animData_[4];

	// �A�j���[�V�����̃J�E���g
	int cntAnim_;

	// �A�j���[�V�����X�s�[�h
	float speedAnim_;

	// �Q�[���p�b�h�̔ԍ�
	InputManager::JOYPAD_NO padNo_;

	// �̗�
	int hp_;

	// �̗͍ő�l
	float hpMax_;

	// �����t���O
	bool isAlive_;

	// 1�O�̐����t���O
	bool oldAlive_;

	// �X�s�[�h
	float speed_;

	// �f�o�b�O�`��
	void DrawDebug(void);

	// HP��1���炷���߂̃t���O
	bool subtract_;

	// ���͂������̂��i�[����z��
	std::vector<int> direction_;

	// ���͂�����
	int pushCnt_;

	// ���͂��Ȃ��Ƃ����Ȃ���
	int pushMax_;

	// ���͂����ׂďI��������ǂ����̃t���O
	bool inputAlive_;

	// ���͂������̉摜
	int inputImage_;

	// �܂����͂���Ă��Ȃ����̉摜
	int notInputImage_;

	// �������킹�̎��̖��̉摜
	int arrowImage_;

	// ���������Ԃɕ\�������邽�߂̃J�E���^
	int answerCnt_;

	// ��󂪍ő�l���`�悳���邽�߂̃J�E���^
	int arrowCnt_;

	// �_���[�W��H�������
	bool damage_;

	// �Z�摜
	int maruImage_;

	// �~�摜
	int batuImage_;

	// ���͂����Ƃ��̉�
	int inputSE_;

	// ���艹
	int decideSE_;

	// �v���C���[��OK�{�^�����������Ƃ��̉�
	int playerDecideSE_;

	// �v���C���[���Ƃɓ��͂�����
	bool inputPlayer_;

	// �X�^�[�g���̓��͏��
	bool inputStart_;

	// ���񂾂Ƃ��̉�
	int deathSE_;

	// ���񂾂Ƃ��̉��̃t���O
	bool death_;

	// �P�O�̐����t���O��ێ����Ă�������
	int aliveCnt_;

	// ����������̓���
	bool inputRevival_;

	// �����_���ŏo����
	int randNumber_;

};

