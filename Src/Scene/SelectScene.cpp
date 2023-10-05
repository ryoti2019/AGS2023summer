#include "../Utility/Application.h"
#include "../Manager/SceneManager.h"
#include "SelectScene.h"

SelectScene::SelectScene(void)
{

	imgSelect_ = -1;

}

SelectScene::~SelectScene(void)
{
}

void SelectScene::Init(void)
{
	// �摜�̏�����
	imgSelect_ = LoadGraph("Data/Image/UI/gameSelect.png");

	// �w�i�摜�̓ǂݍ���
	bgImage_ = LoadGraph("Data/Image/UI/TitleBG.png");

	// �A�탂�[�h�̉摜�̓ǂݍ���
	rennsennImage_ = LoadGraph("Data/Image/UI/�A�탂�[�h.png");

	// �~�j�Q�[�����[�h�̉摜�̓ǂݍ���
	miniGameImage_ = LoadGraph("Data/Image/UI/miniGameMode.png");

	// �т������[�h��I��ł˂̉摜�̓ǂݍ���
	asobitaiImage_ = LoadGraph("Data/Image/UI/SelectUI.png");
	
	// �A�탂�[�h�̃t���O
	isRennsennMode_ = true;

	// �~�j�Q�[�����[�h�̃t���O
	isMiniGameMode_ = false;

	// �w�i�摜���W�̏�����
	bgImagePos01_.x = 0;
	bgImagePos02_.x = -BG_SIZE_X;

	// �Q�[���ԍ�
	gameNo_ = 1;

	// BGM�ǂݍ���
	bgm_ = LoadSoundMem("Data/Music/GameModeSelect.mp3");

	// BGM�Đ�
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP, true);

	// ����{�^����SE�̓ǂݍ���
	decideSE_ = LoadSoundMem("Data/Music/decide.mp3");

	// �I���{�^����SE�̓ǂݍ���
	selectSE_ = LoadSoundMem("Data/Music/select.mp3");
	
	// �߂�{�^���̓ǂݍ���
	bottonAImage_ = LoadGraph("Data/Image/UI/bottonA.png");
	backImage_ = LoadGraph("Data/Image/UI/back.png");

	// ����{�^��
	bottonBImage_ = LoadGraph("Data/Image/UI/bottonB.png");
	nextImage_ = LoadGraph("Data/Image/UI/next.png");


}

void SelectScene::Update(void)
{

	// �w�i�X�N���[������
	bgImagePos01_.x += SCROLL_POW;
	bgImagePos02_.x += SCROLL_POW;
	if (bgImagePos01_.x >= Application::SCREEN_SIZE_X)
	{
		bgImagePos01_.x = bgImagePos02_.x - BG_SIZE_X;
	}
	if (bgImagePos02_.x >= Application::SCREEN_SIZE_X)
	{
		bgImagePos02_.x = bgImagePos01_.x - BG_SIZE_X;
	}

	// �Q�[���̑I��
	// �v���C���[�̐l����I������
	auto& ins = InputManager::GetInstance();
	auto& sce = SceneManager::GetInstance();
	auto pad1 = ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1);
	auto pad2 = ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD2);
	auto pad3 = ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD3);
	auto pad4 = ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD4);
	auto isTrgLStick1 = ins.IsPadStickTrgDownX(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN);
	auto isTrgLStick2 = ins.IsPadStickTrgDownX(InputManager::JOYPAD_NO::PAD2, InputManager::JOYPAD_BTN::DOWN);
	auto isTrgLStick3 = ins.IsPadStickTrgDownX(InputManager::JOYPAD_NO::PAD3, InputManager::JOYPAD_BTN::DOWN);
	auto isTrgLStick4 = ins.IsPadStickTrgDownX(InputManager::JOYPAD_NO::PAD4, InputManager::JOYPAD_BTN::DOWN);
	// �v���C���[�̐l����ς���
	if (isTrgLStick1 && pad1.AKeyLX < 0 || isTrgLStick2 && pad2.AKeyLX < 0 || isTrgLStick3 && pad3.AKeyLX < 0 || isTrgLStick4 && pad4.AKeyLX < 0)
	{
		PlaySoundMem(selectSE_, DX_PLAYTYPE_BACK, true);
		gameNo_ -= 1;
		isRennsennMode_ = true;
		isMiniGameMode_ = false;
		if (0 >= gameNo_)
		{
			gameNo_ = 1;
			isRennsennMode_ = true;
			isMiniGameMode_ = false;

		}
	}

	if (isTrgLStick1 && pad1.AKeyLX > 0 || isTrgLStick2 && pad2.AKeyLX > 0 || isTrgLStick3 && pad3.AKeyLX > 0 || isTrgLStick4 && pad4.AKeyLX > 0)
	{
		PlaySoundMem(selectSE_, DX_PLAYTYPE_BACK, true);
		gameNo_ += 1;
		isRennsennMode_ = false;
		isMiniGameMode_ = true;
		if (3 <= gameNo_)
		{
			gameNo_ = 2;
			isRennsennMode_ = false;
			isMiniGameMode_ = true;

		}
	}

	// �Q�[����I������
	SelectScene::GAME_TYPE game = static_cast<SelectScene::GAME_TYPE>(gameNo_);

	// �V�[���J��
	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT) || 
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD2, InputManager::JOYPAD_BTN::RIGHT) ||
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD3, InputManager::JOYPAD_BTN::RIGHT) ||
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD4, InputManager::JOYPAD_BTN::RIGHT))
	{
		PlaySoundMem(decideSE_, DX_PLAYTYPE_BACK, false);
		StopSoundMem(bgm_);
		switch (game)
		{
		case SelectScene::GAME_TYPE::BATTLE:
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
			sce.SetBattleMode(true);
			break;
		case SelectScene::GAME_TYPE::GAME:
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMESELECT);
			break;
		}
	}

	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN) ||
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD2, InputManager::JOYPAD_BTN::DOWN) ||
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD3, InputManager::JOYPAD_BTN::DOWN) ||
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD4, InputManager::JOYPAD_BTN::DOWN))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::PLAYERSELECT);
		StopSoundMem(bgm_);
	}
}

void SelectScene::Draw(void)
{

	// �w�i�̕`��(1����)
	DrawGraph(bgImagePos01_.x, 0, bgImage_, true);
	// �w�i�̕`��(2����)
	DrawGraph(bgImagePos02_.x, 0, bgImage_, true);

	if (isRennsennMode_)
	{
		// �A�탂�[�h�̉摜�̕`��
		DrawRotaGraph(Application::SCREEN_SIZE_X / 4, Application::SCREEN_SIZE_Y / 2, 1.2f, 0.0f, rennsennImage_, true);

		// �~�j�Q�[�����[�h�̉摜�̕`��
		DrawRotaGraph(768, Application::SCREEN_SIZE_Y / 2, 0.8f, 0.0f, miniGameImage_, true);
	}
	if (isMiniGameMode_)
	{
		// �A�탂�[�h�̉摜�̕`��
		DrawRotaGraph(Application::SCREEN_SIZE_X / 4, Application::SCREEN_SIZE_Y / 2, 0.8f, 0.0f, rennsennImage_, true);

		// �~�j�Q�[�����[�h�̉摜�̕`��
		DrawRotaGraph(768, Application::SCREEN_SIZE_Y / 2, 1.2f, 0.0f, miniGameImage_, true);
	}

	// �V�т������[�h��I��ł˂̉摜�̕`��
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 550, 1.0f, 0.0f, asobitaiImage_, true);
	
	//// �Q�[���Z���N�g�̕`��
	//DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 1.0f, 0.0, imgSelect_, true);

	//DrawFormatString(0, 0, 0x000000, "%d", gameNo_, true);

	// �߂�{�^���̕`��
	DrawRotaGraph(25, 600, 1.0f, 0.0f, bottonAImage_, true);
	DrawRotaGraph(85, 600, 1.0f, 0.0f, backImage_, true);

	// ����{�^���̕`��
	DrawRotaGraph(Application::SCREEN_SIZE_X - 110, 600, 1.0f, 0.0f, bottonBImage_, true);
	DrawRotaGraph(Application::SCREEN_SIZE_X - 50, 600, 1.0f, 0.0f, nextImage_, true);

}

void SelectScene::Release(void)
{
	DeleteGraph(bgImage_);
	DeleteGraph(imgSelect_);
	DeleteGraph(isMiniGameMode_);
	DeleteGraph(asobitaiImage_);
	DeleteGraph(backImage_);
	DeleteGraph(bottonAImage_);
	DeleteGraph(nextImage_);
	DeleteGraph(bottonBImage_);
	DeleteGraph(rennsennImage_);
	DeleteGraph(miniGameImage_);
	DeleteSoundMem(bgm_);
	DeleteSoundMem(decideSE_);
	DeleteSoundMem(selectSE_);
}
