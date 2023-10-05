#pragma once
#include "SceneBase.h"
#include "../Manager/InputManager.h"
class SceneManager;

class SelectScene : public SceneBase
{

public:

	// �X�N���[�����x
	static constexpr int SCROLL_POW = 2;

	// �w�i�̃T�C�Y
	static constexpr int BG_SIZE_X = 2048;
	static constexpr int BG_SIZE_Y = 640;

	// �Q�[���̎��
	enum class GAME_TYPE
	{
		BATTLE = 1,
		GAME = 2,
		MAX = 3
	};

	// �R���X�g���N�^
	SelectScene(void);

	// �f�X�g���N�^
	~SelectScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	SceneManager* sceneManager_;

	// �摜
	int imgSelect_;

	// ���W
	Vector2 pos2_;
	Vector2 pos3_;
	Vector2 pos4_;

	// �Q�[���̃i���o�[
	int gameNo_;

	// L�X�e�B�b�N���|���ꂽ��
	bool stickL_;

	// �Q�[���p�b�h�̔ԍ�
	InputManager::JOYPAD_NO padNo_;

	// �w�i
	int bgImage_;

	// �w�i�̍��W
	Vector2 bgImagePos01_;
	Vector2 bgImagePos02_;

	// �A�탂�[�h�̉摜
	int rennsennImage_;

	// �~�j�Q�[�����[�h�̉摜
	int miniGameImage_;

	// �A�탂�[�h�̃t���O
	bool isRennsennMode_;

	// �~�j�Q�[�����[�h�̉摜
	bool isMiniGameMode_;

	// �V�т������[�h��I��ł˂̉摜
	int asobitaiImage_;

	// BGM
	int bgm_;

	// ���艹
	int decideSE_;

	// �I����
	int selectSE_;

	// �߂�{�^��
	int backImage_;
	int bottonAImage_;

	// ����{�^��
	int nextImage_;
	int bottonBImage_;

	// ���͂��ꂽ����
	int inputNum_;

};

