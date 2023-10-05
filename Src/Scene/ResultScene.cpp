#include <DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Manager/SceneManager.h"
#include "../Utility/Application.h"
#include "../Manager/InputManager.h"
#include "ResultScene.h"

ResultScene::ResultScene(void)
{
}

ResultScene::~ResultScene(void)
{
}

void ResultScene::Init(void)
{

	// プレイヤー画像の読み込み
	LoadDivGraph("Data/Image/Player/1P.png",
		PLAYER_MAX_NUM_ANIM,
		NUM_X, NUM_Y,
		PLAYER_SIZE_X, PLAYER_SIZE_Y,
		&p1Image_[0][0]);
	// プレイヤー画像の読み込み
	LoadDivGraph("Data/Image/Player/2P.png",
		PLAYER_MAX_NUM_ANIM,
		NUM_X, NUM_Y,
		PLAYER_SIZE_X, PLAYER_SIZE_Y,
		&p2Image_[0][0]);
	// プレイヤー画像の読み込み
	LoadDivGraph("Data/Image/Player/3P.png",
		PLAYER_MAX_NUM_ANIM,
		NUM_X, NUM_Y,
		PLAYER_SIZE_X, PLAYER_SIZE_Y,
		&p3Image_[0][0]);
	// プレイヤー画像の読み込み
	LoadDivGraph("Data/Image/Player/4P.png",
		PLAYER_MAX_NUM_ANIM,
		NUM_X, NUM_Y,
		PLAYER_SIZE_X, PLAYER_SIZE_Y,
		&p4Image_[0][0]);

	// プレイヤーのOK画像の読み込み
	OKImage1_ = LoadGraph("Data/Image/UI/1POK.png");
	OKImage2_ = LoadGraph("Data/Image/UI/2POK.png");
	OKImage3_ = LoadGraph("Data/Image/UI/3POK.png");
	OKImage4_ = LoadGraph("Data/Image/UI/4POK.png");	

	youWin_ = LoadGraph("Data/Image/UI/YouWin.png");

	isWin1_ = false;
	isWin2_ = false;
	isWin3_ = false;
	isWin4_ = false;

	// 方向
	dir_ = AsoUtility::DIR::DOWN;

	// タイトルのBGM読み込み
	bgm_ = LoadSoundMem("Data/Music/Result.mp3");

	// タイトルのBGM再生
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP, true);

	// 決定ボタンのSEの読み込み
	decideSE_ = LoadSoundMem("Data/Music/decide.mp3");

	// プレイヤーがOKボタンを押したときの音の読み込み
	playerDecideSE_ = LoadSoundMem("Data/Music/PlayerDecide.mp3");

}

void ResultScene::Update(void)
{

	int pNum = SceneManager::GetInstance().GetPlayerNum();
	for (int i = 0; i < pNum; i++)
	{
		if (pNum == 2)
		{
			if (SceneManager::GetInstance().GetWin1() > SceneManager::GetInstance().GetWin2())
			{
				isWin1_ = true;
			}
			if (SceneManager::GetInstance().GetWin2() > SceneManager::GetInstance().GetWin1())
			{
				isWin2_ = true;
			}
		}
		if (pNum == 3)
		{
			if (SceneManager::GetInstance().GetWin1() > SceneManager::GetInstance().GetWin2() &&
				SceneManager::GetInstance().GetWin1() > SceneManager::GetInstance().GetWin3())
			{
				isWin1_ = true;
			}
			if (SceneManager::GetInstance().GetWin2() > SceneManager::GetInstance().GetWin1() &&
				SceneManager::GetInstance().GetWin2() > SceneManager::GetInstance().GetWin3())
			{
				isWin2_ = true;
			}
			if (SceneManager::GetInstance().GetWin3() > SceneManager::GetInstance().GetWin1() &&
				SceneManager::GetInstance().GetWin3() > SceneManager::GetInstance().GetWin2())
			{
				isWin3_ = true;
			}
		}
		if (pNum == 4)
		{
			if (SceneManager::GetInstance().GetWin1() > SceneManager::GetInstance().GetWin2() &&
				SceneManager::GetInstance().GetWin1() > SceneManager::GetInstance().GetWin3() &&
				SceneManager::GetInstance().GetWin1() > SceneManager::GetInstance().GetWin4())
			{
				isWin1_ = true;
			}
			if (SceneManager::GetInstance().GetWin2() > SceneManager::GetInstance().GetWin1() &&
				SceneManager::GetInstance().GetWin2() > SceneManager::GetInstance().GetWin3() &&
				SceneManager::GetInstance().GetWin2() > SceneManager::GetInstance().GetWin4())
			{
				isWin2_ = true;
			}
			if (SceneManager::GetInstance().GetWin3() > SceneManager::GetInstance().GetWin1() &&
				SceneManager::GetInstance().GetWin3() > SceneManager::GetInstance().GetWin2() &&
				SceneManager::GetInstance().GetWin3() > SceneManager::GetInstance().GetWin4())
			{
				isWin3_ = true;
			}
			if (SceneManager::GetInstance().GetWin4() > SceneManager::GetInstance().GetWin1() &&
				SceneManager::GetInstance().GetWin4() > SceneManager::GetInstance().GetWin2() &&
				SceneManager::GetInstance().GetWin4() > SceneManager::GetInstance().GetWin3())
			{
				isWin4_ = true;
			}
		}
	}

	// シーン遷移
	auto& ins = InputManager::GetInstance();
	// プレイヤーごとにボタンを押したか判定する
	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT) && !inputPlayer1)
	{
		inputNum_ += 1;
		inputPlayer1 = true;
		PlaySoundMem(playerDecideSE_, DX_PLAYTYPE_BACK, true);
	}
	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD2, InputManager::JOYPAD_BTN::RIGHT) && !inputPlayer2)
	{
		inputNum_ += 1;
		inputPlayer2 = true;
		PlaySoundMem(playerDecideSE_, DX_PLAYTYPE_BACK, true);
	}
	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD3, InputManager::JOYPAD_BTN::RIGHT) && !inputPlayer3)
	{
		inputNum_ += 1;
		inputPlayer3 = true;
		PlaySoundMem(playerDecideSE_, DX_PLAYTYPE_BACK, true);
	}
	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD4, InputManager::JOYPAD_BTN::RIGHT) && !inputPlayer4)
	{
		inputNum_ += 1;
		inputPlayer4 = true;
		PlaySoundMem(playerDecideSE_, DX_PLAYTYPE_BACK, true);
	}
	// 全員がボタンを押したら次へ進む

	if (inputNum_ == playerNum_ || InputManager::GetInstance().IsTrgDown(KEY_INPUT_Z))
	{
		PlaySoundMem(decideSE_, DX_PLAYTYPE_BACK, false);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
		StopSoundMem(bgm_);
	}

}

void ResultScene::Draw(void)
{

	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 100, 1.0f, 0.0f, youWin_, true);

	int pNum = SceneManager::GetInstance().GetPlayerNum();
	if (pNum == 2)
	{

		if (isWin1_)
		{
			animData_[0] = 0;
			animData_[1] = 1;
			animData_[2] = 2;
			animData_[3] = 1;
			DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 3.0f, 0.0f, p1Image_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
		}
		if (isWin2_)
		{
			animData_[0] = 0;
			animData_[1] = 1;
			animData_[2] = 2;
			animData_[3] = 1;
			DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 3.0f, 0.0f, p2Image_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
		}
	}

	int pSize = Application::SCREEN_SIZE_X / pNum - 1;
	int pSpace = 100;	// 2人：150　3人：100　４人：75

	if (pNum == 3)
	{
		if (isWin1_)
		{
			animData_[0] = 0;
			animData_[1] = 1;
			animData_[2] = 2;
			animData_[3] = 1;
			DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 3.0f, 0.0f, p1Image_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
		}
		if (isWin2_)
		{
			animData_[0] = 0;
			animData_[1] = 1;
			animData_[2] = 2;
			animData_[3] = 1;
			DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 3.0f, 0.0f, p2Image_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
		}
		if (isWin3_)
		{
			animData_[0] = 0;
			animData_[1] = 1;
			animData_[2] = 2;
			animData_[3] = 1;
			DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 3.0f, 0.0f, p3Image_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
		}
		if (isWin1_ && isWin2_)
		{
			DrawRotaGraph(pSpace + (pSize * 0), Application::SCREEN_SIZE_Y / 2, 3.0f,0.0f, p1Image_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
			DrawRotaGraph(pSpace + (pSize * 1), Application::SCREEN_SIZE_Y / 2, 3.0f,0.0f, p2Image_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
		}
		if (isWin1_ && isWin3_)
		{
			DrawRotaGraph(pSpace + (pSize * 0), Application::SCREEN_SIZE_Y / 2, 3.0f, 0.0f, p1Image_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
			DrawRotaGraph(pSpace + (pSize * 1), Application::SCREEN_SIZE_Y / 2, 3.0f, 0.0f, p3Image_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
		}
		if (isWin2_ && isWin3_)
		{
			DrawRotaGraph(pSpace + (pSize * 0), Application::SCREEN_SIZE_Y / 2, 3.0f, 0.0f, p2Image_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
			DrawRotaGraph(pSpace + (pSize * 1), Application::SCREEN_SIZE_Y / 2, 3.0f, 0.0f, p3Image_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
		}
	}

	int i = 0;
	if (pNum == 4)
	{
		if (isWin1_)
		{
			animData_[0] = 0;
			animData_[1] = 1;
			animData_[2] = 2;
			animData_[3] = 1;
			DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 3.0f, 0.0f, p1Image_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
		}
		if (isWin2_)
		{
			animData_[0] = 0;
			animData_[1] = 1;
			animData_[2] = 2;
			animData_[3] = 1;
			DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 3.0f, 0.0f, p2Image_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
		}
		if (isWin3_)
		{
			animData_[0] = 0;
			animData_[1] = 1;
			animData_[2] = 2;
			animData_[3] = 1;
			DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 3.0f, 0.0f, p3Image_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
		}
		if (isWin4_)
		{
			animData_[0] = 0;
			animData_[1] = 1;
			animData_[2] = 2;
			animData_[3] = 1;
			DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 3.0f, 0.0f, p4Image_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
		}
	}
	cntAnim_++;
}

void ResultScene::Release(void)
{
}
