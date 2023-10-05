#include "../Utility/Application.h"
#include "../Manager/SceneManager.h"
#include "GameSelectScene.h"

GameSelectScene::GameSelectScene(void)
{
}

GameSelectScene::~GameSelectScene(void)
{
}

void GameSelectScene::Init(void)
{
	// 画像の初期化
	imgSelect_ = LoadGraph("Data/Image/UI/gameSelect.png");

	// ゲーム番号
	gameNo_ = 1;

	// 背景画像の読み込み
	bgImage_ = LoadGraph("Data/Image/UI/TitleBG.png");

	// ゲームの画像の読み込み
	game1Image_ = LoadGraph("Data/Image/UI/Game1.png");
	game2Image_ = LoadGraph("Data/Image/UI/Game2.png");
	game3Image_ = LoadGraph("Data/Image/UI/Game3.png");
	game4Image_ = LoadGraph("Data/Image/UI/Game4.png");
	game5Image_ = LoadGraph("Data/Image/UI/Game5.png");

	// ゲームのタイトルの読み込み
	game1TitleImage_ = LoadGraph("Data/Image/UI/ikinokore.png");
	game2TitleImage_ = LoadGraph("Data/Image/UI/tekiwotaose.png");
	game3TitleImage_ = LoadGraph("Data/Image/UI/renndasiro.png");
	game4TitleImage_ = LoadGraph("Data/Image/UI/erabe.png");
	game5TitleImage_ = LoadGraph("Data/Image/UI/nyuuryokusiro.png");

	// 遊びたいゲームを選んでね画像の読み込み
	gameSelectImage_ = LoadGraph("Data/Image/UI/gameSelect.png");

	// BGM
	bgm_ = LoadSoundMem("Data/Music/GameSelect.mp3");

	// タイトルのBGM再生
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP, true);

	// 決定音
	decideSE_ = LoadSoundMem("Data/Music/decide.mp3");

	// 選択音
	selectSE_ = LoadSoundMem("Data/Music/select.mp3");

	// 背景画像座標の初期化
	bgImagePos01_.x = 0;
	bgImagePos02_.x = -BG_SIZE_X;

}

void GameSelectScene::Update(void)
{

	// 背景スクロール処理
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

	// ゲームセレクト
	GameSelect();

	auto& ins = InputManager::GetInstance();
	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN) ||
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD2, InputManager::JOYPAD_BTN::DOWN) ||
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD3, InputManager::JOYPAD_BTN::DOWN) ||
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD4, InputManager::JOYPAD_BTN::DOWN))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SELECT);
		StopSoundMem(bgm_);
	}
}

void GameSelectScene::Draw(void)
{

	// 背景の描画(1枚目)
	DrawGraph(bgImagePos01_.x, 0, bgImage_, true);
	// 背景の描画(2枚目)
	DrawGraph(bgImagePos02_.x, 0, bgImage_, true);

	//// ゲームセレクトの描画
	//DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 1.0f, 0.0, imgSelect_, true);

	//DrawFormatString(0, 0, 0x000000, "%d", gameNo_, true);

	// 遊びたいゲームを選んでね画像の描画
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 600, 1.0f, 0.0f, gameSelectImage_, true);

	// ゲームを選択する
	if (gameNo_ == 1)
	{
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 1.0f, 0.0f, game1Image_, true);
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 50, 1.0f, 0.0f, game1TitleImage_, true);
	}
	if (gameNo_ == 2)
	{
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 1.0f, 0.0f, game2Image_, true);
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 50, 1.0f, 0.0f, game2TitleImage_, true);
	}
	if (gameNo_ == 3)
	{
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 1.0f, 0.0f, game3Image_, true);
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 50, 1.0f, 0.0f, game3TitleImage_, true);
	}
	if (gameNo_ == 4)
	{
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 1.0f, 0.0f, game4Image_, true);
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 50, 1.0f, 0.0f, game4TitleImage_, true);
	}
	if (gameNo_ == 5)
	{
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 1.0f, 0.0f, game5Image_, true);
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 50, 1.0f, 0.0f, game5TitleImage_, true);
	}

}

void GameSelectScene::Release(void)
{
	DeleteGraph(imgSelect_);
	DeleteGraph(imgSelect_);
	DeleteGraph(imgSelect_);
	DeleteGraph(imgSelect_);

}

void GameSelectScene::GameSelect(void)
{
	// プレイヤーの人数を選択する
	auto& ins = InputManager::GetInstance();
	auto pad1 = ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1);
	auto pad2 = ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD2);
	auto pad3 = ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD3);
	auto pad4 = ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD4);
	auto isTrgLStick1 = ins.IsPadStickTrgDownX(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN);
	auto isTrgLStick2 = ins.IsPadStickTrgDownX(InputManager::JOYPAD_NO::PAD2, InputManager::JOYPAD_BTN::DOWN);
	auto isTrgLStick3 = ins.IsPadStickTrgDownX(InputManager::JOYPAD_NO::PAD3, InputManager::JOYPAD_BTN::DOWN);
	auto isTrgLStick4 = ins.IsPadStickTrgDownX(InputManager::JOYPAD_NO::PAD4, InputManager::JOYPAD_BTN::DOWN);
	// プレイヤーの人数を変える
	if (isTrgLStick1 && pad1.AKeyLX < 0 || isTrgLStick2 && pad2.AKeyLX < 0 || isTrgLStick3 && pad3.AKeyLX < 0 || isTrgLStick4 && pad4.AKeyLX < 0)
	{
		PlaySoundMem(selectSE_, DX_PLAYTYPE_BACK, true);
		gameNo_ -= 1;
		if (0 >= gameNo_)
		{
			gameNo_ = 5;
		}
	}

	if (isTrgLStick1 && pad1.AKeyLX > 0 || isTrgLStick2 && pad2.AKeyLX > 0 || isTrgLStick3 && pad3.AKeyLX > 0 || isTrgLStick4 && pad4.AKeyLX > 0)
	{
		PlaySoundMem(selectSE_, DX_PLAYTYPE_BACK, true);
		gameNo_ += 1;
		if (6 <= gameNo_)
		{
			gameNo_ = 1;
		}
	}

	// ゲームを選択する
	GameSelectScene::GAME_TYPE game = static_cast<GameSelectScene::GAME_TYPE>(gameNo_);

	// シーン遷移
	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT) ||
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD2, InputManager::JOYPAD_BTN::RIGHT) ||
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD3, InputManager::JOYPAD_BTN::RIGHT) ||
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD4, InputManager::JOYPAD_BTN::RIGHT))
	{
		PlaySoundMem(decideSE_, DX_PLAYTYPE_BACK, false);
		StopSoundMem(bgm_);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
		switch (game)
		{
		case GameSelectScene::GAME_TYPE::GAME:
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
			break;
		case GameSelectScene::GAME_TYPE::GAME2:
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME2);
			break;
		case GameSelectScene::GAME_TYPE::GAME3:
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME3);
			break;
		case GameSelectScene::GAME_TYPE::GAME4:
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME4);
			break;
		case GameSelectScene::GAME_TYPE::GAME5:
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME5);
			break;
		}
	}
}
