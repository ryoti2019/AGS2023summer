#pragma once
#include "../Utility/AsoUtility.h"
#include "../Common/Vector2.h"
#include "../Manager/InputManager.h"
#include "../Scene/GameScene2.h"

class Shot;

class Player2
{

public:


	// �v���C���[�̍ő�A�j���[�V����
	static constexpr int PLAYER_MAX_NUM_ANIM = 3;

	// �v���C���[�̃T�C�Y
	static constexpr int PLAYER_SIZE_X = 32;
	static constexpr int PLAYER_SIZE_Y = 32;

	// �v���C���[�̏c���̕�����
	static constexpr int NUM_X = 3;
	static constexpr int NUM_Y = 4;


	// �e�̍ő�A�j���[�V����
	static constexpr int SHOT_MAX_NUM_ANIM = 16;

	// �e�̃T�C�Y
	static constexpr int SHOT_SIZE_X = 48;
	static constexpr int SHOT_SIZE_Y = 48;

	// �e�̏c���̕�����
	static constexpr int SHOT_NUM_X = 4;
	static constexpr int SHOT_NUM_Y = 4;

	// �e���ˌ�̍d������
	static constexpr float SHOT_DELAY = 1.0f;

	// �R���X�g���N�^
	Player2();

	// �f�X�g���N�^
	~Player2(void);

	void Init(GameScene2* scene, InputManager::JOYPAD_NO playerNo);
	void Update(void);
	void Draw(void);
	void Release(void);

	// HP�̃Q�b�^�[
	int GetHP(void);

	// HP�̃Q�b�^�[
	void SetHP(int hp);

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

	// ���{�^���̉�������
	bool GetButton(void);

	// Shot�̎擾
	std::vector<Shot*> GetShots(void);

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
	GameScene2* gameScene_;

	// �e
	std::vector<Shot*> shots_;

	// �v���C���[�̉摜
	int playerImg_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM];

	// �v���C���[�̎��S�摜
	int playerDeathImage;

	// �e�摜
	int shotImgs_[SHOT_MAX_NUM_ANIM];

	// �v���C���[�̍��W
	Vector2 pos_;

	// ���S���W
	Vector2 centerPos_;

	// �v���C���[�̈ړ����x
	int speed_;

	// ����
	AsoUtility::DIR dir_;

	// �A�j���[�V�����̃f�[�^
	int animData_[4];

	// �A�j���[�V�����̃J�E���g
	int cntAnim_;

	// �A�j���[�V�����X�s�[�h
	float speedAnim_;

	// ��������
	bool isAlive_;

	// 1�O�̐����t���O
	bool oldAlive_;

	// �_�Ŕ���
	bool isBlink_;

	// �{�^���̉�������
	bool button_;

	// �̗�
	float hp_;

	// �̗͍ő�l
	float hpMax_;

	// �e���ˌ�̍d�����Ԍv�Z�p
	float stepShotDelay_;

	// �Q�[���p�b�h�̔ԍ�
	InputManager::JOYPAD_NO padNo_;

	// �v���C���[�̃f�o�b�O�`��
	void DrawDebug(void);

	// �e�𔭎˂���
	void Attack(void);

	// �e�̐���
	Shot* GetValidShot(void);

	// �U���̉�
	int shotSE_;

	// ���艹
	int decideSE_;

	// �v���C���[���Ƃɓ��͂�����
	bool inputPlayer_;

	// �v���C���[��OK�{�^�����������Ƃ��̉�
	int playerDecideSE_;

	// ���񂾂Ƃ��̉�
	int deathSE_;

	// ���񂾂Ƃ��̉��̃t���O
	bool death_;

	// �X�^�[�g���̓��͏��
	bool inputStart_;

	// �P�O�̐����t���O��ێ����Ă�������
	int aliveCnt_;

	// ����������̓���
	bool inputRevival_;

	// �����_���ŏo����
	int randNumber_;

};
