#pragma once
#include "../Utility/AsoUtility.h"
#include "../Common/Vector2.h"
#include "../Manager/InputManager.h"

class GameScene;
class Meteor;

class Player
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

	// �o���A�̃T�C�Y
	static constexpr int SIZE_X = 100;
	static constexpr int SIZE_Y = 100;

	// �R���X�g���N�^
	Player();

	// �f�X�g���N�^
	~Player(void);

	void Init(GameScene* scene, InputManager::JOYPAD_NO playerNo);
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
	GameScene* gameScene_;

	// �v���C���[
	std::vector<Player*> players_;

	// �v���C���[�̉摜
	int playerImage_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM];

	// �v���C���[�̎��S�摜
	int playerDeathImage;

	// �v���C���[��UI
	int playerUIImage_;

	// �o���A�̉摜
	int barrierImage_;

	// �v���C���[�̍��W
	Vector2 pos_;

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

	// �Q�[���p�b�h�̔ԍ�
	InputManager::JOYPAD_NO padNo_;

	// �f�o�b�O�`��
	void DrawDebug(void);

	// �o���A�̓W�J��
	int barrierSE_;

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


