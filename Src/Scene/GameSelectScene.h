#pragma once
#include "SceneBase.h"
#include "../Manager/InputManager.h"
class GameSelectScene : public SceneBase

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
		GAME = 1,
		GAME2 = 2,
		GAME3 = 3,
		GAME4 = 4,
		GAME5 = 5,
		MAX
	};

	// �R���X�g���N�^
	GameSelectScene(void);

	// �f�X�g���N�^
	~GameSelectScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

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

	void GameSelect(void);

	// BGM
	int bgm_;

	// ���艹
	int decideSE_;

	// �I����
	int selectSE_;

	// �w�i
	int bgImage_;

	// �w�i�̍��W
	Vector2 bgImagePos01_;
	Vector2 bgImagePos02_;

	// �Q�[���̉摜
	int game1Image_;
	int game2Image_;
	int game3Image_;
	int game4Image_;
	int game5Image_;

	// �Q�[���̃^�C�g���摜
	int game1TitleImage_;
	int game2TitleImage_;
	int game3TitleImage_;
	int game4TitleImage_;
	int game5TitleImage_;

	// �V�т����Q�[����I��ł˂̉摜
	int gameSelectImage_;

};

