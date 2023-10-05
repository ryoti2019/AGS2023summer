#pragma once
#include "SceneBase.h"
#include "../Utility/AsoUtility.h"

class SceneManager;

class ResultScene : public SceneBase

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
	ResultScene(void);

	// �f�X�g���N�^
	~ResultScene(void);

	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

private:

	// ����
	AsoUtility::DIR dir_;

	// �A�j���[�V�����̃f�[�^
	int animData_[4];

	// �A�j���[�V�����̃J�E���g
	int cntAnim_;

	// �v���C���[����������
	int win1_;
	int win2_;
	int win3_;
	int win4_;

	// �N���D�����Ă��邩
	bool isWin1_;
	bool isWin2_;
	bool isWin3_;
	bool isWin4_;

	// �v���C���[�̉摜
	int p1Image_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM];;
	int p2Image_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM];;
	int p3Image_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM];;
	int p4Image_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM];;

	int youWin_;

	// ���͂��ꂽ����
	int inputNum_;

	// �v���C���[�̐l��
	int playerNum_;

	// �v���C���[���Ƃɓ��͂�����
	bool inputPlayer1;
	bool inputPlayer2;
	bool inputPlayer3;
	bool inputPlayer4;

	// �v���C���[��OK�摜�̓ǂݍ���
	int OKImage1_;
	int OKImage2_;
	int OKImage3_;
	int OKImage4_;

	// �v���C���[��OK�{�^�����������Ƃ��̉�
	int playerDecideSE_;

	// BGM
	int bgm_;

	// ���艹
	int decideSE_;

};

