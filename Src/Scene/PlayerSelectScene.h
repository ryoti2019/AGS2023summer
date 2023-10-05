#pragma once
#include "SceneBase.h"
#include "../Manager/InputManager.h"
#include "../Utility/AsoUtility.h"
class SceneManager;
class Grid;

class PlayerSelectScene : public SceneBase
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
	PlayerSelectScene(void);

	// �f�X�g���N�^
	~PlayerSelectScene(void);

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

	// �v���C���[��UI�摜
	int p1Image_;
	int p2Image_;
	int p3Image_;
	int p4Image_;

	// �v���C���[��UI���W
	Vector2 p1Pos_;
	Vector2 p2Pos_;
	Vector2 p3Pos_;
	Vector2 p4Pos_;

	// �A�j���[�V�����̃f�[�^
	int animData_[4];

	// �A�j���[�V�����̃J�E���g
	int cntAnim_;

	// ����
	AsoUtility::DIR dir_;

	// �v���C���[�̐l��
	int playerNum_;
	int oldPlayerNum_;

	// �v���C���[�̐l���I��
	void PlayerSelect(void);

	// L�X�e�B�b�N���|���ꂽ��
	bool stickL_;

	// �Q�[���p�b�h�̔ԍ�
	InputManager::JOYPAD_NO padNo_;

	// BGM
	int bgm_;

	// ���艹
	int decideSE_;

	// �v���C���[��OK�{�^�����������Ƃ��̉�
	int playerDecideSE_;

	// �I����
	int selectSE_;

	// �^�C�g�����S
	int logoImage_;

	// �w�i
	int bgImage_;

	// �w�i�̍��W
	Vector2 bgImagePos01_;
	Vector2 bgImagePos02_;

	// �u�l����I�����Ă��������v�̉摜
	int selectImage_;

	// ���͂��ꂽ����
	int inputNum_;

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

	// �߂�{�^��
	int backImage_;
	int bootonAImage_;

};


