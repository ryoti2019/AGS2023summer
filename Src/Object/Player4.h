#pragma once
#include "../Utility/AsoUtility.h"
#include "../Common/Vector2.h"
#include "../Manager/InputManager.h"
#include "../Scene/GameScene4.h"

class SceneManager;

class Player4
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

	// �R���X�g���N�^
	Player4();

	// �f�X�g���N�^
	~Player4(void);

	void Init(GameScene4* scene, InputManager::JOYPAD_NO playerNo);
	void Update(void);
	void Draw(void);
	void Release(void);

	// ���W�̎擾
	Vector2 GetPos(void);

	// ���W�̃Z�b�^�[
	void SetPos(Vector2 pos);

	// �����̐ݒ�
	void SetDir(AsoUtility::DIR dir);

	// �E�̎擾
	bool GetR(void);

	// �E�̐ݒ�
	void SetR(bool r);

	// �E�̎擾
	bool GetL(void);

	// �E�̐ݒ�
	void SetL(bool l);

	// HP��1���炷���߂̃t���O�̐ݒ�
	void SetSubTract(bool subtract);

	// ��������̎擾
	bool IsAlive(void);

	// ��������̐ݒ�
	void SetAlive(bool alive);

	// �P�O�̐�������̎擾
	bool OldAlive(void);

	// �X�^�[�g���̓��͏��
	bool GetInputStart(void);

	// ���֐i�ނƂ��̓��͏��
	bool GetInputPlayer(void);

	// HP�̐ݒ�
	void SetHP(int hp);

	// HP�̎擾
	int GetHP(void);

	// �����_���̐������擾
	int GetRandNumber(void);

	// �����_���̐�����ݒ肷��
	void SetRandNumber(int rand);

	// ������{�^�������������̔���
	bool GetInputRevival(void);

private:

	// �Q�[���V�[���̃|�C���^�ϐ�
	GameScene4* gameScene_;

	// �V�[���̊Ǘ�
	SceneManager* sceneManager_;

	// �v���C���[�̉摜
	int playerImg_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM];

	// �v���C���[��UI
	int playerUIImage_;

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

	// �����t���O
	bool isAlive_;

	// 1�O�̐����t���O
	bool oldAlive_;

	// �X�s�[�h
	float speed_;

	// �f�o�b�O�`��
	void DrawDebug(void);

	// ���̃t���O
	bool left_;

	// �E�̃t���O
	bool right_;

	// HP��1���炷���߂̃t���O
	bool subtract_;

	// �n�[�g�摜
	int heartImage_;

	// �v���C���[�Ԃ̋���
	int pSpace_;

	// �v���C���[���Ƃɓ��͂�����
	bool inputPlayer_;

	// �v���C���[��OK�{�^�����������Ƃ��̉�
	int playerDecideSE_;

	// ���񂾂Ƃ��̉�
	int deathSE_;

	// ���艹
	int decideSE_;

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

