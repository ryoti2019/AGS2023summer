#pragma once
#include "../Utility/AsoUtility.h"
#include "../Common/Vector2.h"
#include "../Manager/InputManager.h"
#include "../Scene/GameScene3.h"

class Shot2;

class Player3
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
	Player3();

	// �f�X�g���N�^
	~Player3(void);

	void Init(GameScene3* scene, InputManager::JOYPAD_NO playerNo);
	void Update(void);
	void Draw(void);
	void Release(void);

	// ���W�̎擾
	Vector2 GetPos(void);

	// ���W�̃Z�b�^�[
	void SetPos(Vector2 pos);

	// Shot�̎擾
	std::vector<Shot2*> GetShots(void);

	// �X�^�[�g���̓��͏��
	bool GetInputStart(void);

	// ���֐i�ނƂ��̓��͏��
	bool GetInputPlayer(void);

private:

	// �Q�[���V�[���̃|�C���^�ϐ�
	GameScene3* gameScene_;

	// �e
	std::vector<Shot2*> shots_;

	// �v���C���[�̉摜
	int playerImg_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM];

	// �v���C���[�̍��W
	Vector2 pos_;

	// ���S���W
	Vector2 centerPos_;

	// ����
	AsoUtility::DIR dir_;

	// �e�摜
	int shotImgs_[SHOT_MAX_NUM_ANIM];

	// �A�j���[�V�����̃f�[�^
	int animData_[4];

	// �A�j���[�V�����̃J�E���g
	int cntAnim_;

	// �A�j���[�V�����X�s�[�h
	float speedAnim_;

	// �Q�[���p�b�h�̔ԍ�
	InputManager::JOYPAD_NO padNo_;

	// �e�𔭎˂���
	void Attack(void);

	// �e�̐���
	Shot2* GetValidShot(void);

	// �U���̉�
	int shotSE_;

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

};

