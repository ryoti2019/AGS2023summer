#pragma once
#include "SceneBase.h"
#include "../Manager/InputManager.h"
#include "../Utility/AsoUtility.h"
class SceneManager;
class Grid;

class TitleScene : public SceneBase
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

	// �X�N���[�����x
	static constexpr int SCROLL_POW = 2;

	// �w�i�̃T�C�Y
	static constexpr int BG_SIZE_X = 2048;
	static constexpr int BG_SIZE_Y = 640;

	// �v���C���[
	enum class PLAYER_NUM
	{
		PLAYER_2 = 2,
		PLAYER_3 = 3,
		PLAYER_4 = 4,
		MAX
	};



	// �R���X�g���N�^
	TitleScene(void);

	// �f�X�g���N�^
	~TitleScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	// �v���C���[�̉摜
	int img1_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM];
	int img2_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM];
	int img3_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM];
	int img4_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM];

	// �v���C���[���W
	Vector2 pos1_;
	Vector2 pos2_;
	Vector2 pos3_;
	Vector2 pos4_;

	// �v���C���[�̏��
	bool p1_;
	bool p2_;
	bool p3_;
	bool p4_;

	// �v���C���[�̕���
	AsoUtility::DIR dir_;

	// �v���C���[�̈ړ��X�s�[�h
	float p1speed_;
	float p2speed_;
	float p3speed_;
	float p4speed_;

	// �A�j���[�V�����̃f�[�^
	int animData_[4];

	// �A�j���[�V�����̃J�E���g
	int cntAnim_;

	// �Q�[���p�b�h�̔ԍ�
	InputManager::JOYPAD_NO padNo_;

	// BGM
	int bgm_;

	// ���艹
	int decideSE_;

	// �I����
	int selectSE_;

	// �w�i
	int bgImage_;

	// �^�C�g�����S
	int logoImage_;

	// �w�i�̍��W
	Vector2 bgImagePos01_;
	Vector2 bgImagePos02_;

	int step1_;
	int step2_;
	int step3_;
	int step4_;
	int nextStep1_;
	int nextStep2_;
	int nextStep3_;
	int nextStep4_;

	// �X�^�[�g�̉摜
	int startImage_;

	// ���ŗp�J�E���^�[
	int blinkCnt_;

};

