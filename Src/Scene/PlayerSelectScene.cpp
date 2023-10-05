#include <string>
#include <DxLib.h>
#include "../Utility/Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "PlayerSelectScene.h"
PlayerSelectScene::PlayerSelectScene(void)
{
}

PlayerSelectScene::~PlayerSelectScene(void)
{
}

void PlayerSelectScene::Init(void)
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

	// 「人数を選択してください」の読み込み
	selectImage_ = LoadGraph("Data/Image/UI/Select.png");

	// プレイヤーのUI画像の読み込み
	p1Image_ = LoadGraph("Data/Image/UI/1P.png");
	p2Image_ = LoadGraph("Data/Image/UI/2P.png");
	p3Image_ = LoadGraph("Data/Image/UI/3P.png");
	p4Image_ = LoadGraph("Data/Image/UI/4P.png");

	// プレイヤーのOK画像の読み込み
	OKImage1_ = LoadGraph("Data/Image/UI/1POK.png");
	OKImage2_ = LoadGraph("Data/Image/UI/2POK.png");
	OKImage3_ = LoadGraph("Data/Image/UI/3POK.png");
	OKImage4_ = LoadGraph("Data/Image/UI/4POK.png");

	// 背景画像座標の初期化
	bgImagePos01_.x = 0;
	bgImagePos02_.x = -BG_SIZE_X;

	// プレイヤーの人数
	playerNum_ = 2;

	// 座標の初期化
	pos1_ = { Application::SCREEN_SIZE_X + 100, Application::SCREEN_SIZE_Y + 100 };
	pos2_ = { Application::SCREEN_SIZE_X + 100, Application::SCREEN_SIZE_Y + 100 };
	pos3_ = { Application::SCREEN_SIZE_X + 100, Application::SCREEN_SIZE_Y + 100 };
	pos4_ = { Application::SCREEN_SIZE_X + 100, Application::SCREEN_SIZE_Y + 100 };
	p1Pos_ = { Application::SCREEN_SIZE_X + 100, Application::SCREEN_SIZE_Y + 100 };
	p2Pos_ = { Application::SCREEN_SIZE_X + 100, Application::SCREEN_SIZE_Y + 100 };
	p3Pos_ = { Application::SCREEN_SIZE_X + 100, Application::SCREEN_SIZE_Y + 100 };
	p4Pos_ = { Application::SCREEN_SIZE_X + 100, Application::SCREEN_SIZE_Y + 100 };


	// タイトルのBGM読み込み
	bgm_ = LoadSoundMem("Data/Music/PlayerSelect.mp3");

	// タイトルのBGM再生
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP, true);

	// 決定ボタンのSEの読み込み
	decideSE_ = LoadSoundMem("Data/Music/decide.mp3");

	// プレイヤーがOKボタンを押したときの音の読み込み
	playerDecideSE_ = LoadSoundMem("Data/Music/PlayerDecide.mp3");

	// 選択ボタンのSEの読み込み
	selectSE_ = LoadSoundMem("Data/Music/select.mp3");

	dir_ = AsoUtility::DIR::LEFT;

	cntAnim_ = 0;

	inputPlayer1 = false;
	inputPlayer2 = false;
	inputPlayer3 = false;
	inputPlayer4 = false;

	// 戻るボタン
	bootonAImage_ = LoadGraph("Data/Image/UI/bottonA.png");
	backImage_ = LoadGraph("Data/Image/UI/back.png");

}

void PlayerSelectScene::Update(void)
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

	// プレイヤーの人数の選択
	PlayerSelect();

	// プレイヤー座標
	if (playerNum_ == 2)
	{
		pos1_ = { Application::SCREEN_SIZE_X / 2 - 100, 408 };
		pos2_ = { Application::SCREEN_SIZE_X / 2 + 100, 408 };
		p1Pos_ = { pos1_.x, pos1_.y - 100 };
		p2Pos_ = { pos2_.x, pos2_.y - 100 };
	}

	if (playerNum_ == 3)
	{
		pos1_ = { Application::SCREEN_SIZE_X / 2 - 200, 408 };
		pos2_ = { Application::SCREEN_SIZE_X / 2 , 408 };
		pos3_ = { Application::SCREEN_SIZE_X / 2 + 200, 408 };
		p1Pos_ = { pos1_.x, pos1_.y - 100 };
		p2Pos_ = { pos2_.x, pos2_.y - 100 };
		p3Pos_ = { pos3_.x, pos3_.y - 100 };
	}

	if (playerNum_ == 4)
	{
		pos1_ = { Application::SCREEN_SIZE_X / 2 - 300, 408 };
		pos2_ = { Application::SCREEN_SIZE_X / 2 - 100, 408 };
		pos3_ = { Application::SCREEN_SIZE_X / 2 + 100, 408 };
		pos4_ = { Application::SCREEN_SIZE_X / 2 + 300, 408 };
		p1Pos_ = { pos1_.x, pos1_.y - 100 };
		p2Pos_ = { pos2_.x, pos2_.y - 100 };
		p3Pos_ = { pos3_.x, pos3_.y - 100 };
		p4Pos_ = { pos4_.x, pos4_.y - 100 };
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


	if (oldPlayerNum_ != playerNum_)
	{
		inputNum_ = 0;
		inputPlayer1 = false;
		inputPlayer2 = false;
		inputPlayer3 = false;
		inputPlayer4 = false;
	}
	oldPlayerNum_ = playerNum_;

	// 全員がボタンを押したら次へ進む

	if (inputNum_ == playerNum_ || InputManager::GetInstance().IsTrgDown(KEY_INPUT_Z))
	{
		PlaySoundMem(decideSE_, DX_PLAYTYPE_BACK, false);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SELECT);
		StopSoundMem(bgm_);
	}

	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN) ||
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD2, InputManager::JOYPAD_BTN::DOWN) ||
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD3, InputManager::JOYPAD_BTN::DOWN) ||
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD4, InputManager::JOYPAD_BTN::DOWN))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
		StopSoundMem(bgm_);
	}

}

void PlayerSelectScene::Draw(void)
{

	// タイトルの描画
	//DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 1.0f, 0.0, imgTitle_, true);
	// 背景の描画(1枚目)
	DrawGraph(bgImagePos01_.x, 0, bgImage_, true);
	// 背景の描画(2枚目)
	DrawGraph(bgImagePos02_.x, 0, bgImage_, true);

	// タイトルロゴの描画
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 100, 2.0f, 0.0f, logoImage_, true);

	// 「人数を選択してください」の描画
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 550, 1.0f, 0.0f, selectImage_, true);

	// 人数画像の描画
	if (playerNum_ == 2)
	{
		// プレイヤー画像の描画
		// アニメーションのチップ番号(0～3)を作る
		animData_[0] = 0;
		animData_[1] = 1;
		animData_[2] = 2;
		animData_[3] = 1;
		DrawRotaGraph(pos1_.x, pos1_.y, 1.0f, 0.0f, img1_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
		DrawRotaGraph(pos2_.x, pos2_.y, 1.0f, 0.0f, img2_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
		if (!inputPlayer1)
		{
			DrawRotaGraph(p1Pos_.x, p1Pos_.y, 1.0f, 0.0f, p1Image_, true);
		}
		if (!inputPlayer2)
		{
			DrawRotaGraph(p2Pos_.x, p2Pos_.y, 1.0f, 0.0f, p2Image_, true);
		}
		cntAnim_++;
	}

	if (playerNum_ == 3)
	{
		animData_[0] = 0;
		animData_[1] = 1;
		animData_[2] = 2;
		animData_[3] = 1;
		DrawRotaGraph(pos1_.x, pos1_.y, 1.0f, 0.0f, img1_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
		DrawRotaGraph(pos2_.x, pos2_.y, 1.0f, 0.0f, img2_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
		DrawRotaGraph(pos3_.x, pos3_.y, 1.0f, 0.0f, img3_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
		if (!inputPlayer1)
		{
			DrawRotaGraph(p1Pos_.x, p1Pos_.y, 1.0f, 0.0f, p1Image_, true);
		}
		if (!inputPlayer2)
		{
			DrawRotaGraph(p2Pos_.x, p2Pos_.y, 1.0f, 0.0f, p2Image_, true);
		}
		if (!inputPlayer3)
		{
			DrawRotaGraph(p3Pos_.x, p3Pos_.y, 1.0f, 0.0f, p3Image_, true);
		}
		cntAnim_++;
	}

	if (playerNum_ == 4)
	{
		animData_[0] = 0;
		animData_[1] = 1;
		animData_[2] = 2;
		animData_[3] = 1;
		DrawRotaGraph(pos1_.x, pos1_.y, 1.0f, 0.0f, img1_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
		DrawRotaGraph(pos2_.x, pos2_.y, 1.0f, 0.0f, img2_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
		DrawRotaGraph(pos3_.x, pos3_.y, 1.0f, 0.0f, img3_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
		DrawRotaGraph(pos4_.x, pos4_.y, 1.0f, 0.0f, img4_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
		if (!inputPlayer1)
		{
			DrawRotaGraph(p1Pos_.x, p1Pos_.y, 1.0f, 0.0f, p1Image_, true);
		}
		if (!inputPlayer2)
		{
			DrawRotaGraph(p2Pos_.x, p2Pos_.y, 1.0f, 0.0f, p2Image_, true);
		}
		if (!inputPlayer3)
		{
			DrawRotaGraph(p3Pos_.x, p3Pos_.y, 1.0f, 0.0f, p3Image_, true);
		}
		if (!inputPlayer4)
		{
			DrawRotaGraph(p4Pos_.x, p4Pos_.y, 1.0f, 0.0f, p4Image_, true);
		}
		cntAnim_++;
	}

	if (inputPlayer1)
	{
		DrawRotaGraph(p1Pos_.x, p1Pos_.y, 1.0f, 0.0f, OKImage1_, true);
	}
	if (inputPlayer2)
	{
		DrawRotaGraph(p2Pos_.x, p2Pos_.y, 1.0f, 0.0f, OKImage2_, true);
	}
	if (inputPlayer3)
	{
		DrawRotaGraph(p3Pos_.x, p3Pos_.y, 1.0f, 0.0f, OKImage3_, true);
	}
	if (inputPlayer4)
	{
		DrawRotaGraph(p4Pos_.x, p4Pos_.y, 1.0f, 0.0f, OKImage4_, true);
	}

	// 戻るボタンの描画
	DrawRotaGraph(25, 600, 1.0f, 0.0f, bootonAImage_, true);
	DrawRotaGraph(85, 600, 1.0f, 0.0f, backImage_, true);

}

void PlayerSelectScene::Release(void)
{
	DeleteGraph(img1_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM]);
	DeleteGraph(img2_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM]);
	DeleteGraph(img3_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM]);
	DeleteGraph(img4_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM]);
	DeleteGraph(p1Image_);
	DeleteGraph(p2Image_);
	DeleteGraph(p3Image_);
	DeleteGraph(p4Image_);
	DeleteGraph(p4Image_);
	DeleteGraph(logoImage_);
	DeleteGraph(bgImage_);
	DeleteGraph(selectImage_);
	DeleteGraph(OKImage1_);
	DeleteGraph(OKImage2_);
	DeleteGraph(OKImage3_);
	DeleteGraph(OKImage4_);
	DeleteGraph(backImage_);
	DeleteGraph(bootonAImage_);
	DeleteSoundMem(bgm_);
	DeleteSoundMem(decideSE_);
	DeleteSoundMem(playerDecideSE_);
	DeleteSoundMem(selectSE_);
}

void PlayerSelectScene::PlayerSelect(void)
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
	if (isTrgLStick1 && pad1.AKeyLX < 0 || isTrgLStick2 && pad2.AKeyLX < 0|| isTrgLStick3 && pad3.AKeyLX < 0 || isTrgLStick4 && pad4.AKeyLX < 0)
	{
		PlaySoundMem(selectSE_, DX_PLAYTYPE_BACK, true);
		playerNum_ -= 1;
		if (1 >= playerNum_)
		{
			playerNum_ = 4;
		}
	}

	if (isTrgLStick1 && pad1.AKeyLX > 0 || isTrgLStick2 && pad2.AKeyLX > 0|| isTrgLStick3 && pad3.AKeyLX > 0|| isTrgLStick4 && pad4.AKeyLX > 0)
	{
		PlaySoundMem(selectSE_, DX_PLAYTYPE_BACK, true);
		playerNum_ += 1;
		if (5 <= playerNum_)
		{
			playerNum_ = 2;
		}
	}

	// プレイヤーの人数を選択する
	PlayerSelectScene::PLAYER_NUM num = static_cast<PlayerSelectScene::PLAYER_NUM>(playerNum_);
	switch (num)
	{
	case PlayerSelectScene::PLAYER_NUM::PLAYER_2:
		SceneManager::GetInstance().SetPlayerNum(2);
		break;
	case PlayerSelectScene::PLAYER_NUM::PLAYER_3:
		SceneManager::GetInstance().SetPlayerNum(3);
		break;
	case PlayerSelectScene::PLAYER_NUM::PLAYER_4:
		SceneManager::GetInstance().SetPlayerNum(4);
		break;
	}

}
