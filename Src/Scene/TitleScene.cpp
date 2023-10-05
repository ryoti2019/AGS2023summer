#include <string>
#include <DxLib.h>
#include "../Utility/Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "TitleScene.h"

TitleScene::TitleScene(void)
{
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{

	// 画像の初期化
	//imgTitle_ = LoadGraph("Data/Image/UI/Title.png");
	// プレイヤー画像の読み込み
	int dirNum = static_cast<int>(AsoUtility::DIR::MAX);
	int allNum = PLAYER_MAX_NUM_ANIM * dirNum;

	LoadDivGraph("Data/Image/Player/1P.png",
		allNum,
		NUM_X, dirNum,
		PLAYER_SIZE_X, PLAYER_SIZE_Y,
		&img1_[0][0]);
	// プレイヤー画像の読み込み
	LoadDivGraph("Data/Image/Player/2P.png",
		allNum,
		NUM_X, dirNum,
		PLAYER_SIZE_X, PLAYER_SIZE_Y,
		&img2_[0][0]);
	// プレイヤー画像の読み込み
	LoadDivGraph("Data/Image/Player/3P.png",
		allNum,
		NUM_X, dirNum,
		PLAYER_SIZE_X, PLAYER_SIZE_Y,
		&img3_[0][0]);
	// プレイヤー画像の読み込み
	LoadDivGraph("Data/Image/Player/4P.png",
		allNum,
		NUM_X, dirNum,
		PLAYER_SIZE_X, PLAYER_SIZE_Y,
		&img4_[0][0]);

	// 背景画像の読み込み
	bgImage_ = LoadGraph("Data/Image/UI/TitleBG.png");

	// タイトルロゴの読み込み
	logoImage_ = LoadGraph("Data/Image/UI/Title.png");

	// 背景画像座標の初期化
	bgImagePos01_.x = 0;
	bgImagePos02_.x = -BG_SIZE_X;

	// 座標の初期化
	pos1_ = { Application::SCREEN_SIZE_X + 100, 408 };
	pos2_ = { Application::SCREEN_SIZE_X + 100, 408 };
	pos3_ = { Application::SCREEN_SIZE_X + 100, 408 };
	pos4_ = { Application::SCREEN_SIZE_X + 100, 408 };

	// タイトルのBGM読み込み
	bgm_ = LoadSoundMem("Data/Music/Future_1.mp3");

	// タイトルのBGM再生
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP, true);

	// 決定ボタンのSEの読み込み
	decideSE_ = LoadSoundMem("Data/Music/decide.mp3");

	// 選択ボタンのSEの読み込み
	selectSE_ = LoadSoundMem("Data/Music/select.mp3");

	dir_ = AsoUtility::DIR::LEFT;

	cntAnim_ = 0;

	step1_ = 0;
	step2_ = 0;
	step3_ = 0;
	step4_ = 0;
	nextStep1_ = 80;
	nextStep2_ = 80;
	nextStep3_ = 80;
	nextStep4_ = 80;

	// スタート画像の読み込み
	startImage_ = LoadGraph("Data/Image/UI/start.png");

	// 明滅用のカウンタ
	blinkCnt_ = 0;

}

void TitleScene::Update(void)
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

	// プレイヤーの移動処理
	if (p1_)
	{
		pos1_.x -= p1speed_;
	}
	if (p2_)
	{
		pos2_.x -= p2speed_;
	}
	if (p3_)
	{
		pos3_.x -= p3speed_;
	}
	if (p4_)
	{
		pos4_.x -= p4speed_;
	}

	// プレイヤーの死亡処理
	if (pos1_.x < -100)
	{
		p1_ = false;
		pos1_.x = Application::SCREEN_SIZE_X + 100;
	}
	if (pos2_.x < -100)
	{
		p2_ = false;
		pos2_.x = Application::SCREEN_SIZE_X + 100;
	}
	if (pos3_.x < -100)
	{
		p3_ = false;
		pos3_.x = Application::SCREEN_SIZE_X + 100;
	}
	if (pos4_.x < -100)
	{
		p4_ = false;
		pos4_.x = Application::SCREEN_SIZE_X + 100;
	}

	// プレイヤーの再出現処理
	if (!p1_)
	{
		step1_++;
		if (step1_ > nextStep1_)
		{
			p1_ = true;
			p1speed_ = 1.0f + GetRand(3);
			step1_ = 0;
			nextStep1_ = 120 + GetRand(180);
		}

	}
	if (!p2_)
	{
		step2_++;
		if (step2_ > nextStep2_)
		{
			p2_ = true;
			p2speed_ = 1.0f + GetRand(3);
			step2_ = 0;
			nextStep2_ = 120 + GetRand(180);
		}

	}
	if (!p3_)
	{
		step3_++;
		if (step3_ > nextStep3_)
		{
			p3_ = true;
			p3speed_ = 1.0f + GetRand(3);
			step3_ = 0;
			nextStep3_ = 120 + GetRand(180);
		}

	}
	if (!p4_)
	{
		step4_++;
		if (step4_ > nextStep4_)
		{
			p4_ = true;
			p4speed_ = 1.0f + GetRand(3);
			step4_ = 0;
			nextStep4_ = 120 + GetRand(180);
		}

	}

	// シーン遷移
	auto& ins = InputManager::GetInstance();
	auto isPadTrgDown1 = ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT);
	auto isPadTrgDown2 = ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD2, InputManager::JOYPAD_BTN::RIGHT);
	auto isPadTrgDown3 = ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD3, InputManager::JOYPAD_BTN::RIGHT);
	auto isPadTrgDown4 = ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD4, InputManager::JOYPAD_BTN::RIGHT);
	if (isPadTrgDown1 || isPadTrgDown2 || isPadTrgDown3 || isPadTrgDown4)
	{
		PlaySoundMem(decideSE_, DX_PLAYTYPE_BACK, false);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::PLAYERSELECT);
		StopSoundMem(bgm_);
	}

}

void TitleScene::Draw(void)
{

	// タイトルの描画
	//DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 1.0f, 0.0, imgTitle_, true);
	// 背景の描画(1枚目)
	DrawGraph(bgImagePos01_.x, 0, bgImage_, true);
	// 背景の描画(2枚目)
	DrawGraph(bgImagePos02_.x, 0, bgImage_, true);

	// タイトルロゴの描画
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 100, 2.0f, 0.0f, logoImage_, true);

	// プレイヤー画像の描画
	// アニメーションのチップ番号(0～3)を作る
	animData_[0] = 0;
	animData_[1] = 1;
	animData_[2] = 2;
	animData_[3] = 1;

	if (p1_)
	{
		DrawRotaGraph(pos1_.x, pos1_.y, 1.0f, 0.0f, img1_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
	}
	if (p2_)
	{
		DrawRotaGraph(pos2_.x, pos2_.y, 1.0f, 0.0f, img2_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
	}
	if (p3_)
	{
		DrawRotaGraph(pos3_.x, pos3_.y, 1.0f, 0.0f, img3_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
	}
	if (p4_)
	{
		DrawRotaGraph(pos4_.x, pos4_.y, 1.0f, 0.0f, img4_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
	}
	cntAnim_++;

	// スタート画像の描画
	blinkCnt_++;
	if ((blinkCnt_ / 60) % 2)
	{
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 550, 1.0f, 0.0f, startImage_, true);
	}

}

void TitleScene::Release(void)
{
	DeleteGraph(bgImage_);
	DeleteGraph(logoImage_);
	DeleteGraph(img1_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM]);
	DeleteGraph(img2_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM]);
	DeleteGraph(img3_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM]);
	DeleteGraph(img4_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM]);
	DeleteGraph(startImage_);
	DeleteSoundMem(bgm_);
	DeleteSoundMem(decideSE_);
	DeleteSoundMem(selectSE_);
}
