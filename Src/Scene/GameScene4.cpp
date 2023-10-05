#include <string>
#include <DxLib.h>
#include "../Utility/Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Object/Player4.h"
#include "../Object/Stage2.h"
#include "../Object/StrartMes.h"
#include "../Scene/ResultScene.h"
#include "GameScene4.h"

GameScene4::GameScene4(void)
{
}

GameScene4::~GameScene4(void)
{
}

void GameScene4::Init(void)
{

	// カウントダウンの画像
	count1_ = LoadGraph("Data/Image/UI/game4_1.png");
	count2_ = LoadGraph("Data/Image/UI/game4_2.png");
	count3_ = LoadGraph("Data/Image/UI/game4_3.png");
	count4_ = LoadGraph("Data/Image/UI/game4_4.png");
	count5_ = LoadGraph("Data/Image/UI/game4_5.png");

	// ゲーム説明用の画像
	expImage_ = LoadGraph("Data/Image/UI/game4UI.png");

	// ボタンの画像の読み込み
	LoadDivGraph("Data/Image/UI/BbottonAnim.png",
		BOTTON_MAX_NUM_ANIM,
		BOTTON_NUM_X, BOTTON_NUM_Y,
		BOTTON_SIZE_X, BOTTON_SIZE_Y,
		&BbottonImage_[0]);

	// スティックの画像の読み込み
	LoadDivGraph("Data/Image/UI/Lstick.png",
		STICK_MAX_NUM_ANIM,
		STICK_NUM_X, STICK_NUM_Y,
		STICK_SIZE_X, STICK_SIZE_Y,
		&LstickIMage_[0]);

	// 勝利画像の読み込み
	winImage1_ = LoadGraph("Data/Image/UI/1Pwin.png");
	winImage2_ = LoadGraph("Data/Image/UI/2Pwin.png");
	winImage3_ = LoadGraph("Data/Image/UI/3Pwin.png");
	winImage4_ = LoadGraph("Data/Image/UI/4Pwin.png");

	// プレイヤーのOK画像の読み込み
	OKImage1_ = LoadGraph("Data/Image/UI/1POK.png");
	OKImage2_ = LoadGraph("Data/Image/UI/2POK.png");
	OKImage3_ = LoadGraph("Data/Image/UI/3POK.png");
	OKImage4_ = LoadGraph("Data/Image/UI/4POK.png");

	// スタート画像の読み込み
	startImage_ = LoadGraph("Data/Image/UI/start.png");

	// 全部のサイコロの画像の読み込み
	LoadDivGraph("Data/Image/UI/AllDice.png",
		6, 6, 1,
		100, 100,
		& allDice_[0]);

	// 1つずつのサイコロの画像の読み込み
	dice1_ = LoadGraph("Data/Image/UI/Dice1.png");
	dice2_ = LoadGraph("Data/Image/UI/Dice2.png");
	dice3_ = LoadGraph("Data/Image/UI/Dice3.png");
	dice4_ = LoadGraph("Data/Image/UI/Dice4.png");
	dice5_ = LoadGraph("Data/Image/UI/Dice5.png");
	dice6_ = LoadGraph("Data/Image/UI/Dice6.png");

	// サイコロを振れ
	saikoro_ = LoadGraph("Data/Image/UI/saikoro.png");

	// ステージの初期化
	stage_ = new Stage2();
	stage_->Init(this);

	// プレイヤーの人数選択
	int pNum = SceneManager::GetInstance().GetPlayerNum();
	int pSize = Application::SCREEN_SIZE_X / pNum;
	int pSpace = 0;	// 2人：150　3人：100　４人：75
	if (pNum == 2)
	{
		pSpace = 256;
	}
	if (pNum == 3)
	{
		pSpace = 172;
	}
	if (pNum == 4)
	{
		pSpace = 128;
	}

	for (int i = 0; i < pNum; i++)
	{
		Player4* p = new Player4();
		InputManager::JOYPAD_NO jno = static_cast<InputManager::JOYPAD_NO>(i + 1);
		p->Init(this, jno);
		p->SetPos({ pSpace + (pSize * i), 500 });
		players_.push_back(p);
	}

	// スタートメッセージの初期化
	startMes_ = new StartMes();
	startMes_->Init();

	// 選べの読み込み
	erabe_ = LoadGraph("Data/Image/UI/erabe.png");

	// ゲーム説明をスキップするフラグ
	skip_ = false;

	// アニメーションのカウンタ
	cntAnim_ = 0;

	// BGMの読み込み
	bgm_ = LoadSoundMem("Data/Music/game4BGM.mp3");
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP, true);

	// ダメージを食らった時の音の読み込み
	damageSE_ = LoadSoundMem("Data/Music/explosion1.mp3");

	// 決定ボタンのSEの読み込み
	decideSE_ = LoadSoundMem("Data/Music/decideGame.mp3");

	// トゲの音
	spinaSE_ = LoadSoundMem("Data/Music/spinaSE.mp3");

	// カウントダウンのSE読み込み
	countDownSE_ = LoadSoundMem("Data/Music/countDownSE.mp3");

	notOperationTime_ = 180;

	left_ = false;
	right_ = false;
	start_ = false;
	startCntStart_ = false;
	startCnt_ = 0;
	downCntStart_ = false;
	downCnt_ = 0;

	// 決定ボタンのSEの読み込み
	decideSE_ = LoadSoundMem("Data/Music/decideGame.mp3");

	// アニメーションのカウンタ
	cntAnim_ = 0;

	inputNum_ = 0;

	startNum_ = 0;

	isStart_ = false;

	result_ = false;

	revival_ = false;

	isRand1_ = true;
	isRand2_ = true;
	isRand3_ = true;
	isRand4_ = true;

	inputRandNum_ = 0;

	revivalHP_ = true;

	win_ = true;
}

void GameScene4::Update(void)
{

	int pNum = SceneManager::GetInstance().GetPlayerNum();
	auto& ins = InputManager::GetInstance();
	if (startNum_ == pNum || InputManager::GetInstance().IsTrgDown(KEY_INPUT_Z))
	{
		skip_ = true;
	}

	if (skip_)
	{
		// スタートメッセージの更新
		startMes_->Update();
	}

	if (startMes_->GetCnt() >= 240)
	{
		isStart_ = true;
	}

	// 操作権限の制御
	if (notOperationTime_ >= 60)
	{
		for (auto player : players_)
		{
			// プレイヤーの更新
			player->Update();
		}
	}

	if (!revival_)
	{
		if (isStart_)
		{
			if (!result_)
			{
				// ステージの更新
				stage_->Update();

				// 右か左かランダムで決める
				if (start_)
				{
					random_ = (GetRand(1));
					if (random_ == 0)
					{
						left_ = true;
					}
					if (random_ == 1)
					{
						right_ = true;
					}
					start_ = false;
				}

				// カウントダウンが終わったら初期化する
				if (downCnt_ >= 300)
				{
					downCnt_ = 0;
					notOperationTime_ = 0;
					downCntStart_ = false;
				}

				// 条件が揃ったらカウンタをスタートする
				if (downCnt_ == 0 && startCnt_ == 0)
				{
					notOperationTime_++;
				}

				// 条件が揃ったらカウントをスタートする
				if (downCnt_ == 0 && startCnt_ == 0 && notOperationTime_ >= 60)
				{
					downCntStart_ = true;
					startCntStart_ = true;
				}

				// カウントダウンのカウンタを進める
				if (downCntStart_)
				{
					downCnt_++;
				}

				if (downCnt_ == 300)
				{
					left_ = false;
					right_ = false;
					start_ = true;
					PlaySoundMem(spinaSE_, DX_PLAYTYPE_BACK, true);
				}

				// スタートカウンタのカウンタを進める
				if (startCntStart_)
				{
					startCnt_++;
				}

				// 描画し終えたら初期化する
				if (startCnt_ >= 360)
				{
					startCnt_ = 0;
					startCntStart_ = false;
				}

				// プレイヤーにダメージを与える
				if (notOperationTime_ == 0)
				{
					for (auto player : players_)
					{
						player->SetDir(AsoUtility::DIR::DOWN);
						player->SetSubTract(true);
					}
				}

				// カウントダウンの音の処理
				if (downCnt_ == 1)
				{
					PlaySoundMem(countDownSE_, DX_PLAYTYPE_BACK, true);
				}
				if (downCnt_ == 61)
				{
					PlaySoundMem(countDownSE_, DX_PLAYTYPE_BACK, true);
				}
				if (downCnt_ == 121)
				{
					PlaySoundMem(countDownSE_, DX_PLAYTYPE_BACK, true);
				}
				if (downCnt_ == 181)
				{
					PlaySoundMem(countDownSE_, DX_PLAYTYPE_BACK, true);
				}
				if (downCnt_ == 241)
				{
					PlaySoundMem(countDownSE_, DX_PLAYTYPE_BACK, true);
				}
			}
		}
	}

	// プレイヤーの死亡した人数に合わせてシーン遷移する
	int deathNum = 0;
	for (int i = 0; i < pNum; i++)
	{
		if (!players_[i]->IsAlive())
		{
			deathNum++;
		}
	}

	if (pNum == deathNum + 1)
	{
		Result();
		result_ = true;
	}

	// 同時に死んでしまったとき
	if (pNum < deathNum + 1)
	{
		if (revivalHP_)
		{
			revival_ = true;
			revivalHP_ = false;
			for (int i = 0; i < pNum; i++)
			{
				if (i == 0 && players_[0]->OldAlive())
				{
					players_[0]->SetHP(1);
					players_[0]->SetAlive(true);
				}
				if (i == 1 && players_[1]->OldAlive())
				{
					players_[1]->SetHP(1);
					players_[1]->SetAlive(true);
				}
				if (i == 2 && players_[2]->OldAlive())
				{
					players_[2]->SetHP(1);
					players_[2]->SetAlive(true);
				}
				if (i == 3 && players_[3]->OldAlive())
				{
					players_[3]->SetHP(1);
					players_[3]->SetAlive(true);
				}
			}
		}
	}

	if (revival_)
	{
		Rand();
	}

}

void GameScene4::Draw(void)
{

	// ステージの描画
	stage_->Draw();

	// スタートメッセージの描画
	startMes_->Draw();


	for (auto player : players_)
	{
		// プレイヤーの描画
		player->Draw();
	}

	//// 左右の表示
	//if (left_)
	//{
	//	DrawFormatString(Application::SCREEN_SIZE_X / 2, 0, 0xffffff, "左");
	//}

	//if (right_)
	//{
	//	DrawFormatString(Application::SCREEN_SIZE_X / 2, 0, 0xffffff, "右");
	//}

	cntAnim_++;
	if (!skip_)
	{
		// ゲーム説明画像の描画
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 230, 1.0f, 0.0f, expImage_, true);
		DrawGraph(820, 367, BbottonImage_[(cntAnim_ / 10) % 4], true);
		DrawGraph(470, 360, LstickIMage_[cntAnim_ / 5 % 8], true);
	}
	if (skip_ && startMes_->GetCnt() >= 240)
	{
		if (!result_ && !revival_)
		{
			// 選べの描画
			DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 140, 1.0f, 0.0f, erabe_, true);

			// カウントの表示
			if (downCnt_ >= 0 && downCnt_ <= 60)
			{
				DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 300, 1.0f, 0.0f, count5_, true);
			}

			if (downCnt_ >= 60 && downCnt_ <= 120)
			{
				DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 300, 1.0f, 0.0f, count4_, true);
			}

			if (downCnt_ >= 120 && downCnt_ <= 180)
			{
				DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 300, 1.0f, 0.0f, count3_, true);
			}

			if (downCnt_ >= 180 && downCnt_ <= 240)
			{
				DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 300, 1.0f, 0.0f, count2_, true);
			}

			if (downCnt_ >= 240 && downCnt_ <= 300)
			{
				DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 300, 1.0f, 0.0f, count1_, true);
			}
		}
	}

	// 勝利した人の画像の描画
	int pNum = SceneManager::GetInstance().GetPlayerNum();
	if (result_)
	{
		for (int i = 0; i < pNum; i++)
		{
			if (pNum == 2)
			{
				if (players_[0]->IsAlive())
				{
					// 1Pの勝利画像
					DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 200, 1.0f, 0.0f, winImage1_, true);
				}
				if (players_[1]->IsAlive())
				{
					// 2Pの勝利画像
					DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 200, 1.0f, 0.0f, winImage2_, true);
				}
			}
			if (pNum == 3)
			{
				if (players_[0]->IsAlive())
				{
					// 1Pの勝利画像
					DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 200, 1.0f, 0.0f, winImage1_, true);
				}
				if (players_[1]->IsAlive())
				{
					// 2Pの勝利画像
					DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 200, 1.0f, 0.0f, winImage2_, true);
				}
				if (players_[2]->IsAlive())
				{
					// 3Pの勝利画像
					DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 200, 1.0f, 0.0f, winImage3_, true);
				}
			}
			if (pNum == 4)
			{
				if (players_[0]->IsAlive())
				{
					// 1Pの勝利画像
					DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 200, 1.0f, 0.0f, winImage1_, true);
				}
				if (players_[1]->IsAlive())
				{
					// 2Pの勝利画像
					DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 200, 1.0f, 0.0f, winImage2_, true);
				}
				if (players_[2]->IsAlive())
				{
					// 3Pの勝利画像
					DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 200, 1.0f, 0.0f, winImage3_, true);
				}
				if (players_[3]->IsAlive())
				{
					// 4Pの勝利画像
					DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 200, 1.0f, 0.0f, winImage4_, true);
				}
			}
		}
	}

	int pSize = Application::SCREEN_SIZE_X / pNum;
	int pSpace = 0;	// 2人：150　3人：100　４人：75
	// 人数画像の描画
	if (pNum == 2)
	{
		pSpace = 200;
	}
	if (pNum == 3)
	{
		pSpace = 100;
	}
	if (pNum == 4)
	{
		pSpace = 75;
	}

	for (int i = 0; i < pNum; i++)
	{

		if (pNum == 2)
		{
			if (players_[0]->GetInputStart() && !skip_)
			{
				DrawRotaGraph(pSpace + (pSize * 0) + 50, 600, 1.0f, 0.0f, OKImage1_, true);
			}
			if (players_[1]->GetInputStart() && !skip_)
			{
				DrawRotaGraph(pSpace + (pSize * 1) + 50, 600, 1.0f, 0.0f, OKImage2_, true);
			}
		}
		if (pNum == 3)
		{
			if (players_[0]->GetInputStart() && !skip_)
			{
				DrawRotaGraph(pSpace + (pSize * 0) + 50, 600, 1.0f, 0.0f, OKImage1_, true);
			}
			if (players_[1]->GetInputStart() && !skip_)
			{
				DrawRotaGraph(pSpace + (pSize * 1) + 50, 600, 1.0f, 0.0f, OKImage2_, true);
			}
			if (players_[2]->GetInputStart() && !skip_)
			{
				DrawRotaGraph(pSpace + (pSize * 2) + 50, 600, 1.0f, 0.0f, OKImage3_, true);
			}
		}
		if (pNum == 4)
		{
			if (players_[0]->GetInputStart() && !skip_)
			{
				DrawRotaGraph(pSpace + (pSize * 0) + 50, 600, 1.0f, 0.0f, OKImage1_, true);
			}
			if (players_[1]->GetInputStart() && !skip_)
			{
				DrawRotaGraph(pSpace + (pSize * 1) + 50, 600, 1.0f, 0.0f, OKImage2_, true);
			}
			if (players_[2]->GetInputStart() && !skip_)
			{
				DrawRotaGraph(pSpace + (pSize * 2) + 50, 600, 1.0f, 0.0f, OKImage3_, true);
			}
			if (players_[3]->GetInputStart() && !skip_)
			{
				DrawRotaGraph(pSpace + (pSize * 3) + 50, 600, 1.0f, 0.0f, OKImage4_, true);
			}
		}
	}

	for (int i = 0; i < pNum; i++)
	{
		if (result_)
		{
			if (pNum == 2)
			{
				if (players_[0]->GetInputPlayer())
				{
					DrawRotaGraph(pSpace + (pSize * 0) + 50, 600, 1.0f, 0.0f, OKImage1_, true);
				}
				if (players_[1]->GetInputPlayer())
				{
					DrawRotaGraph(pSpace + (pSize * 1) + 50, 600, 1.0f, 0.0f, OKImage2_, true);
				}
			}
			if (pNum == 3)
			{
				if (players_[0]->GetInputPlayer())
				{
					DrawRotaGraph(pSpace + (pSize * 0) + 50, 600, 1.0f, 0.0f, OKImage1_, true);
				}
				if (players_[1]->GetInputPlayer())
				{
					DrawRotaGraph(pSpace + (pSize * 1) + 50, 600, 1.0f, 0.0f, OKImage2_, true);
				}
				if (players_[2]->GetInputPlayer())
				{
					DrawRotaGraph(pSpace + (pSize * 2) + 50, 600, 1.0f, 0.0f, OKImage3_, true);
				}
			}
			if (pNum == 4)
			{
				if (players_[0]->GetInputPlayer())
				{
					DrawRotaGraph(pSpace + (pSize * 0) + 50, 600, 1.0f, 0.0f, OKImage1_, true);
				}
				if (players_[1]->GetInputPlayer())
				{
					DrawRotaGraph(pSpace + (pSize * 1) + 50, 600, 1.0f, 0.0f, OKImage2_, true);
				}
				if (players_[2]->GetInputPlayer())
				{
					DrawRotaGraph(pSpace + (pSize * 2) + 50, 600, 1.0f, 0.0f, OKImage3_, true);
				}
				if (players_[3]->GetInputPlayer())
				{
					DrawRotaGraph(pSpace + (pSize * 3) + 50, 600, 1.0f, 0.0f, OKImage4_, true);
				}
			}
		}
	}

	// スタート画像の描画
	if (result_)
	{
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 550, 1.0f, 0.0f, startImage_, true);
	}

	// サイコロの画像の描画
	for (int i = 0; i < pNum; i++)
	{
		if (revival_)
		{
			// サイコロを振れの描画
			DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 140, 1.0f, 0.0f, saikoro_, true);
			// 全部のサイコロの描画
			if (pNum == 2)
			{
				if (i == 0 && !players_[0]->GetInputRevival() && players_[0]->IsAlive() && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 0) + 50, 450, 1.0f, 0.0f, allDice_[(cntAnim_ / 10) % 6], true);
				}
				if (i == 1 && !players_[1]->GetInputRevival() && players_[1]->IsAlive() && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 1) + 50, 450, 1.0f, 0.0f, allDice_[(cntAnim_ / 10) % 6], true);
				}
			}
			if (pNum == 3)
			{
				if (i == 0 && !players_[0]->GetInputRevival() && players_[0]->IsAlive() && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 0) + 50, 450, 1.0f, 0.0f, allDice_[(cntAnim_ / 10) % 6], true);
				}
				if (i == 1 && !players_[1]->GetInputRevival() && players_[1]->IsAlive() && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 1) + 50, 450, 1.0f, 0.0f, allDice_[(cntAnim_ / 10) % 6], true);
				}
				if (i == 2 && !players_[2]->GetInputRevival() && players_[2]->IsAlive() && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 2) + 50, 450, 1.0f, 0.0f, allDice_[(cntAnim_ / 10) % 6], true);
				}
			}
			if (pNum == 4)
			{
				if (i == 0 && !players_[0]->GetInputRevival() && players_[0]->IsAlive() && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 0) + 50, 450, 1.0f, 0.0f, allDice_[(cntAnim_ / 10) % 6], true);
				}
				if (i == 1 && !players_[1]->GetInputRevival() && players_[1]->IsAlive() && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 1) + 50, 450, 1.0f, 0.0f, allDice_[(cntAnim_ / 10) % 6], true);
				}
				if (i == 2 && !players_[2]->GetInputRevival() && players_[2]->IsAlive() && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 2) + 50, 450, 1.0f, 0.0f, allDice_[(cntAnim_ / 10) % 6], true);
				}
				if (i == 3 && !players_[3]->GetInputRevival() && players_[3]->IsAlive() && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 3) + 50, 450, 1.0f, 0.0f, allDice_[(cntAnim_ / 10) % 6], true);
				}
			}

			if (pNum == 2)
			{
				if (i == 0 && players_[0]->GetInputRevival() && players_[0]->GetRandNumber() == 1 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 0) + 50, 450, 1.0f, 0.0f, dice1_, true);
				}
				if (i == 0 && players_[0]->GetInputRevival() && players_[0]->GetRandNumber() == 2 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 0) + 50, 450, 1.0f, 0.0f, dice2_, true);
				}
				if (i == 0 && players_[0]->GetInputRevival() && players_[0]->GetRandNumber() == 3 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 0) + 50, 450, 1.0f, 0.0f, dice3_, true);
				}
				if (i == 0 && players_[0]->GetInputRevival() && players_[0]->GetRandNumber() == 4 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 0) + 50, 450, 1.0f, 0.0f, dice4_, true);
				}
				if (i == 0 && players_[0]->GetInputRevival() && players_[0]->GetRandNumber() == 5 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 0) + 50, 450, 1.0f, 0.0f, dice5_, true);
				}
				if (i == 0 && players_[0]->GetInputRevival() && players_[0]->GetRandNumber() == 6 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 0) + 50, 450, 1.0f, 0.0f, dice6_, true);
				}

				// プレイヤー２のサイコロ
				if (i == 1 && players_[1]->GetInputRevival() && players_[1]->GetRandNumber() == 1 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 1) + 50, 450, 1.0f, 0.0f, dice1_, true);
				}
				if (i == 1 && players_[1]->GetInputRevival() && players_[1]->GetRandNumber() == 2 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 1) + 50, 450, 1.0f, 0.0f, dice2_, true);
				}
				if (i == 1 && players_[1]->GetInputRevival() && players_[1]->GetRandNumber() == 3 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 1) + 50, 450, 1.0f, 0.0f, dice3_, true);
				}
				if (i == 1 && players_[1]->GetInputRevival() && players_[1]->GetRandNumber() == 4 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 1) + 50, 450, 1.0f, 0.0f, dice4_, true);
				}
				if (i == 1 && players_[1]->GetInputRevival() && players_[1]->GetRandNumber() == 5 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 1) + 50, 450, 1.0f, 0.0f, dice5_, true);
				}
				if (i == 1 && players_[1]->GetInputRevival() && players_[1]->GetRandNumber() == 6 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 1) + 50, 450, 1.0f, 0.0f, dice6_, true);
				}
			}
			if (pNum == 3)
			{
				// プレイヤー１のサイコロ
				if (i == 0 && players_[0]->GetInputRevival() && players_[0]->GetRandNumber() == 1 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 0) + 50, 450, 1.0f, 0.0f, dice1_, true);
				}
				if (i == 0 && players_[0]->GetInputRevival() && players_[0]->GetRandNumber() == 2 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 0) + 50, 450, 1.0f, 0.0f, dice2_, true);
				}
				if (i == 0 && players_[0]->GetInputRevival() && players_[0]->GetRandNumber() == 3 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 0) + 50, 450, 1.0f, 0.0f, dice3_, true);
				}
				if (i == 0 && players_[0]->GetInputRevival() && players_[0]->GetRandNumber() == 4 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 0) + 50, 450, 1.0f, 0.0f, dice4_, true);
				}
				if (i == 0 && players_[0]->GetInputRevival() && players_[0]->GetRandNumber() == 5 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 0) + 50, 450, 1.0f, 0.0f, dice5_, true);
				}
				if (i == 0 && players_[0]->GetInputRevival() && players_[0]->GetRandNumber() == 6 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 0) + 50, 450, 1.0f, 0.0f, dice6_, true);
				}

				// プレイヤー２のサイコロ
				if (i == 1 && players_[1]->GetInputRevival() && players_[1]->GetRandNumber() == 1 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 1) + 50, 450, 1.0f, 0.0f, dice1_, true);
				}
				if (i == 1 && players_[1]->GetInputRevival() && players_[1]->GetRandNumber() == 2 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 1) + 50, 450, 1.0f, 0.0f, dice2_, true);
				}
				if (i == 1 && players_[1]->GetInputRevival() && players_[1]->GetRandNumber() == 3 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 1) + 50, 450, 1.0f, 0.0f, dice3_, true);
				}
				if (i == 1 && players_[1]->GetInputRevival() && players_[1]->GetRandNumber() == 4 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 1) + 50, 450, 1.0f, 0.0f, dice4_, true);
				}
				if (i == 1 && players_[1]->GetInputRevival() && players_[1]->GetRandNumber() == 5 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 1) + 50, 450, 1.0f, 0.0f, dice5_, true);
				}
				if (i == 1 && players_[1]->GetInputRevival() && players_[1]->GetRandNumber() == 6 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 1) + 50, 450, 1.0f, 0.0f, dice6_, true);
				}

				// プレイヤー３のサイコロ
				if (i == 2 && players_[2]->GetInputRevival() && players_[2]->GetRandNumber() == 1 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 2) + 50, 450, 1.0f, 0.0f, dice1_, true);
				}
				if (i == 2 && players_[2]->GetInputRevival() && players_[2]->GetRandNumber() == 2 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 2) + 50, 450, 1.0f, 0.0f, dice2_, true);
				}
				if (i == 2 && players_[2]->GetInputRevival() && players_[2]->GetRandNumber() == 3 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 2) + 50, 450, 1.0f, 0.0f, dice3_, true);
				}
				if (i == 2 && players_[2]->GetInputRevival() && players_[2]->GetRandNumber() == 4 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 2) + 50, 450, 1.0f, 0.0f, dice4_, true);
				}
				if (i == 2 && players_[2]->GetInputRevival() && players_[2]->GetRandNumber() == 5 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 2) + 50, 450, 1.0f, 0.0f, dice5_, true);
				}
				if (i == 2 && players_[2]->GetInputRevival() && players_[2]->GetRandNumber() == 6 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 2) + 50, 450, 1.0f, 0.0f, dice6_, true);
				}
			}
			if (pNum == 4)
			{
				// プレイヤー１のサイコロ
				if (i == 0 && players_[0]->GetInputRevival() && players_[0]->GetRandNumber() == 1 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 0) + 50, 450, 1.0f, 0.0f, dice1_, true);
				}
				if (i == 0 && players_[0]->GetInputRevival() && players_[0]->GetRandNumber() == 2 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 0) + 50, 450, 1.0f, 0.0f, dice2_, true);
				}
				if (i == 0 && players_[0]->GetInputRevival() && players_[0]->GetRandNumber() == 3 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 0) + 50, 450, 1.0f, 0.0f, dice3_, true);
				}
				if (i == 0 && players_[0]->GetInputRevival() && players_[0]->GetRandNumber() == 4 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 0) + 50, 450, 1.0f, 0.0f, dice4_, true);
				}
				if (i == 0 && players_[0]->GetInputRevival() && players_[0]->GetRandNumber() == 5 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 0) + 50, 450, 1.0f, 0.0f, dice5_, true);
				}
				if (i == 0 && players_[0]->GetInputRevival() && players_[0]->GetRandNumber() == 6 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 0) + 50, 450, 1.0f, 0.0f, dice6_, true);
				}

				// プレイヤー２のサイコロ
				if (i == 1 && players_[1]->GetInputRevival() && players_[1]->GetRandNumber() == 1 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 1) + 50, 450, 1.0f, 0.0f, dice1_, true);
				}
				if (i == 1 && players_[1]->GetInputRevival() && players_[1]->GetRandNumber() == 2 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 1) + 50, 450, 1.0f, 0.0f, dice2_, true);
				}
				if (i == 1 && players_[1]->GetInputRevival() && players_[1]->GetRandNumber() == 3 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 1) + 50, 450, 1.0f, 0.0f, dice3_, true);
				}
				if (i == 1 && players_[1]->GetInputRevival() && players_[1]->GetRandNumber() == 4 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 1) + 50, 450, 1.0f, 0.0f, dice4_, true);
				}
				if (i == 1 && players_[1]->GetInputRevival() && players_[1]->GetRandNumber() == 5 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 1) + 50, 450, 1.0f, 0.0f, dice5_, true);
				}
				if (i == 1 && players_[1]->GetInputRevival() && players_[1]->GetRandNumber() == 6 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 1) + 50, 450, 1.0f, 0.0f, dice6_, true);
				}

				// プレイヤー３のサイコロ
				if (i == 2 && players_[2]->GetInputRevival() && players_[2]->GetRandNumber() == 1 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 2) + 50, 450, 1.0f, 0.0f, dice1_, true);
				}
				if (i == 2 && players_[2]->GetInputRevival() && players_[2]->GetRandNumber() == 2 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 2) + 50, 450, 1.0f, 0.0f, dice2_, true);
				}
				if (i == 2 && players_[2]->GetInputRevival() && players_[2]->GetRandNumber() == 3 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 2) + 50, 450, 1.0f, 0.0f, dice3_, true);
				}
				if (i == 2 && players_[2]->GetInputRevival() && players_[2]->GetRandNumber() == 4 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 2) + 50, 450, 1.0f, 0.0f, dice4_, true);
				}
				if (i == 2 && players_[2]->GetInputRevival() && players_[2]->GetRandNumber() == 5 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 2) + 50, 450, 1.0f, 0.0f, dice5_, true);
				}
				if (i == 2 && players_[2]->GetInputRevival() && players_[2]->GetRandNumber() == 6 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 2) + 50, 450, 1.0f, 0.0f, dice6_, true);
				}

				// プレイヤー４のサイコロ
				if (i == 3 && players_[3]->GetInputRevival() && players_[3]->GetRandNumber() == 1 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 3) + 50, 450, 1.0f, 0.0f, dice1_, true);
				}
				if (i == 3 && players_[3]->GetInputRevival() && players_[3]->GetRandNumber() == 2 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 3) + 50, 450, 1.0f, 0.0f, dice2_, true);
				}
				if (i == 3 && players_[3]->GetInputRevival() && players_[3]->GetRandNumber() == 3 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 3) + 50, 450, 1.0f, 0.0f, dice3_, true);
				}
				if (i == 3 && players_[3]->GetInputRevival() && players_[3]->GetRandNumber() == 4 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 3) + 50, 450, 1.0f, 0.0f, dice4_, true);
				}
				if (i == 3 && players_[3]->GetInputRevival() && players_[3]->GetRandNumber() == 5 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 3) + 50, 450, 1.0f, 0.0f, dice5_, true);
				}
				if (i == 3 && players_[3]->GetInputRevival() && players_[3]->GetRandNumber() == 6 && !result_)
				{
					DrawRotaGraph(pSpace + (pSize * 3) + 50, 450, 1.0f, 0.0f, dice6_, true);
				}
			}
		}
	}

	if (revival_ && !result_)
	{
		// サイコロを振れの描画
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 140, 1.0f, 0.0f, saikoro_, true);
	}
}

void GameScene4::Release(void)
{

	// スタートメッセージの更新
	startMes_->Release();
	delete startMes_;

	// ステージの開放
	stage_->Release();

	for (auto player : players_)
	{
		// プレイヤーの開放
		player->Release();
		delete player;
	}

}

Vector2 GameScene4::World2MapPos(Vector2 worldPos)
{

	Vector2 ret;

	int  mapX = worldPos.x / Stage2::CHIP_SIZE_X;
	int  mapY = worldPos.y / Stage2::CHIP_SIZE_Y;

	ret.x = mapX;
	ret.y = mapY;

	return ret;

}

bool GameScene4::IsCollisionStage(Vector2 worldPos)
{

	// ワールド座標からマップ座標に変換する
	Vector2 mapPos = World2MapPos(worldPos);

	// マップ座標からマップチップ番号を取得する
	int chipNo = stage_->GetCollisionStageNo(mapPos);

	if (chipNo != -1)
	{
		return true;
	}

	return false;

}

Stage2* GameScene4::GetStage(void)
{
	return stage_;
}

bool GameScene4::GetL(void)
{
	return left_;
}

void GameScene4::SetL(bool left)
{
	left_ = left;
}

bool GameScene4::GetR(void)
{
	return right_;
}

void GameScene4::SetR(bool right)
{
	right_ = right;
}

int GameScene4::GetCnt(void)
{
	return startCnt_;
}

bool GameScene4::GetResult(void)
{
	return result_;
}

bool GameScene4::GetSkip(void)
{
	return skip_;
}

bool GameScene4::IsStart(void)
{
	return isStart_;
}

void GameScene4::SetInputNum(int input)
{
	inputNum_ += input;
}

void GameScene4::SetStartNum(int start)
{
	startNum_ += start;
}

bool GameScene4::GetRevival(void)
{
	return revival_;
}

void GameScene4::Result(void)
{

	int pNum = SceneManager::GetInstance().GetPlayerNum();

	for (int i = 0; i < pNum; i++)
	{
		if (pNum == 2)
		{
			if (players_[0]->IsAlive())
			{
				if (win_)
				{
					SceneManager::GetInstance().SetWin1(1);
					win_ = false;
				}
			}
			if (players_[1]->IsAlive())
			{
				if (win_)
				{
					SceneManager::GetInstance().SetWin2(1);
					win_ = false;
				}
			}
		}
		if (pNum == 3)
		{
			if (players_[0]->IsAlive())
			{
				if (win_)
				{
					SceneManager::GetInstance().SetWin1(1);
					win_ = false;
				}
			}
			if (players_[1]->IsAlive())
			{
				if (win_)
				{
					SceneManager::GetInstance().SetWin2(1);
					win_ = false;
				}
			}
			if (players_[2]->IsAlive())
			{
				if (win_)
				{
					SceneManager::GetInstance().SetWin3(1);
					win_ = false;
				}
			}
		}
		if (pNum == 4)
		{
			if (players_[0]->IsAlive())
			{
				if (win_)
				{
					SceneManager::GetInstance().SetWin1(1);
					win_ = false;
				}
			}
			if (players_[1]->IsAlive())
			{
				if (win_)
				{
					SceneManager::GetInstance().SetWin2(1);
					win_ = false;
				}
			}
			if (players_[2]->IsAlive())
			{
				if (win_)
				{
					SceneManager::GetInstance().SetWin3(1);
					win_ = false;
				}
			}
			if (players_[3]->IsAlive())
			{
				if (win_)
				{
					SceneManager::GetInstance().SetWin4(1);
					win_ = false;
				}
			}
		}

	}

	// シーン遷移
	auto& ins = InputManager::GetInstance();
	// 全員がボタンを押したら次へ進む
	if (SceneManager::GetInstance().GetBattleMode())
	{
		if (inputNum_ == pNum || InputManager::GetInstance().IsTrgDown(KEY_INPUT_Z))
		{
			PlaySoundMem(decideSE_, DX_PLAYTYPE_BACK, false);
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME5);
			StopSoundMem(bgm_);
			return;
		}
	}

	if (inputNum_ == pNum || InputManager::GetInstance().IsTrgDown(KEY_INPUT_Z))
	{
		PlaySoundMem(decideSE_, DX_PLAYTYPE_BACK, false);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMESELECT);
		StopSoundMem(bgm_);
	}
	int i = 0;
}

void GameScene4::Rand(void)
{
	int pNum = SceneManager::GetInstance().GetPlayerNum();
	// ランダムに数字を割り当てる
	if (revival_)
	{
		for (int i = 0; i < pNum; i++)
		{
			if (pNum == 2)
			{
				if (i == 0 && players_[0]->GetHP() > 0 && players_[0]->GetInputRevival())
				{
					if (isRand1_)
					{
						players_[0]->SetRandNumber(GetRand(5) + 1);
						isRand1_ = false;
						inputRandNum_ += 1;
					}
					if (players_[0]->GetRandNumber() == players_[1]->GetRandNumber())
					{
						players_[0]->SetRandNumber(GetRand(5) + 1);
					}
				}

				if (i == 1 && players_[1]->GetHP() > 0 && players_[1]->GetInputRevival())
				{
					if (isRand2_)
					{
						players_[1]->SetRandNumber(GetRand(5) + 1);
						isRand2_ = false;
						inputRandNum_ += 1;
					}
					if (players_[1]->GetRandNumber() == players_[0]->GetRandNumber())
					{
						players_[1]->SetRandNumber(GetRand(5) + 1);
					}
				}
			}

			if (pNum == 3)
			{
				if (i == 0 && players_[0]->GetHP() > 0 && players_[0]->GetInputRevival())
				{
					if (isRand1_)
					{
						players_[0]->SetRandNumber(GetRand(5) + 1);
						isRand1_ = false;
						inputRandNum_ += 1;
					}
					if (players_[0]->GetRandNumber() == players_[1]->GetRandNumber() ||
						players_[0]->GetRandNumber() == players_[2]->GetRandNumber())
					{
						players_[0]->SetRandNumber(GetRand(5) + 1);
					}
				}

				if (i == 1 && players_[1]->GetHP() > 0 && players_[1]->GetInputRevival())
				{
					if (isRand2_)
					{
						players_[1]->SetRandNumber(GetRand(5) + 1);
						isRand2_ = false;
						inputRandNum_ += 1;
					}
					if (players_[1]->GetRandNumber() == players_[0]->GetRandNumber() ||
						players_[1]->GetRandNumber() == players_[2]->GetRandNumber())
					{
						players_[1]->SetRandNumber(GetRand(5) + 1);
					}
				}

				if (i == 2 && players_[2]->GetHP() > 0 && players_[2]->GetInputRevival())
				{
					if (isRand3_)
					{
						players_[2]->SetRandNumber(GetRand(5) + 1);
						isRand3_ = false;
						inputRandNum_ += 1;
					}
					if (players_[2]->GetRandNumber() == players_[0]->GetRandNumber() ||
						players_[2]->GetRandNumber() == players_[1]->GetRandNumber())
					{
						players_[2]->SetRandNumber(GetRand(5) + 1);
					}
				}
			}

			if (pNum == 4)
			{
				if (i == 0 && players_[0]->GetHP() > 0 && players_[0]->GetInputRevival())
				{
					if (isRand1_)
					{
						players_[0]->SetRandNumber(GetRand(5) + 1);
						isRand1_ = false;
						inputRandNum_ += 1;
					}
					if (players_[0]->GetRandNumber() == players_[1]->GetRandNumber() ||
						players_[0]->GetRandNumber() == players_[2]->GetRandNumber() ||
						players_[0]->GetRandNumber() == players_[3]->GetRandNumber())
					{
						players_[0]->SetRandNumber(GetRand(5) + 1);
					}
				}

				if (i == 1 && players_[1]->GetHP() > 0 && players_[1]->GetInputRevival())
				{
					if (isRand2_)
					{
						players_[1]->SetRandNumber(GetRand(5) + 1);
						isRand2_ = false;
						inputRandNum_ += 1;
					}
					if (players_[1]->GetRandNumber() == players_[0]->GetRandNumber() ||
						players_[1]->GetRandNumber() == players_[2]->GetRandNumber() ||
						players_[1]->GetRandNumber() == players_[3]->GetRandNumber())
					{
						players_[1]->SetRandNumber(GetRand(5) + 1);
					}
				}

				if (i == 2 && players_[2]->GetHP() > 0 && players_[2]->GetInputRevival())
				{
					if (isRand3_)
					{
						players_[2]->SetRandNumber(GetRand(5) + 1);
						isRand3_ = false;
						inputRandNum_ += 1;
					}
					if (players_[2]->GetRandNumber() == players_[0]->GetRandNumber() ||
						players_[2]->GetRandNumber() == players_[1]->GetRandNumber() ||
						players_[2]->GetRandNumber() == players_[3]->GetRandNumber())
					{
						players_[2]->SetRandNumber(GetRand(5) + 1);
					}
				}

				if (i == 3 && players_[3]->GetHP() > 0 && players_[3]->GetInputRevival())
				{
					if (isRand4_)
					{
						players_[3]->SetRandNumber(GetRand(5) + 1);
						isRand4_ = false;
						inputRandNum_ += 1;
					}
					if (players_[3]->GetRandNumber() == players_[0]->GetRandNumber() ||
						players_[3]->GetRandNumber() == players_[1]->GetRandNumber() ||
						players_[3]->GetRandNumber() == players_[2]->GetRandNumber())
					{
						players_[3]->SetRandNumber(GetRand(5) + 1);
					}
				}
			}
		}
	}

	if (pNum == inputRandNum_)
	{
		for (int i = 0; i < pNum; i++)
		{
			if (pNum == 2)
			{
				if (players_[0]->GetRandNumber() > players_[1]->GetRandNumber())
				{
					players_[0]->SetAlive(true);
					players_[1]->SetHP(-2);
					players_[1]->SetAlive(false);
				}
				if (players_[1]->GetRandNumber() > players_[0]->GetRandNumber())
				{
					players_[1]->SetAlive(true);
					players_[0]->SetHP(-2);
					players_[0]->SetAlive(false);
				}
			}
			if (pNum == 3)
			{
				if (players_[0]->GetRandNumber() > players_[1]->GetRandNumber() &&
					players_[0]->GetRandNumber() > players_[2]->GetRandNumber())
				{
					players_[0]->SetAlive(true);
					players_[1]->SetHP(-2);
					players_[2]->SetHP(-2);
					players_[1]->SetAlive(false);
					players_[2]->SetAlive(false);
				}
				if (players_[1]->GetRandNumber() > players_[0]->GetRandNumber() &&
					players_[1]->GetRandNumber() > players_[2]->GetRandNumber())
				{
					players_[1]->SetAlive(true);
					players_[0]->SetHP(-2);
					players_[2]->SetHP(-2);
					players_[0]->SetAlive(false);
					players_[2]->SetAlive(false);
				}
				if (players_[2]->GetRandNumber() > players_[0]->GetRandNumber() &&
					players_[2]->GetRandNumber() > players_[1]->GetRandNumber())
				{
					players_[2]->SetAlive(true);
					players_[0]->SetHP(-2);
					players_[1]->SetHP(-2);
					players_[0]->SetAlive(false);
					players_[1]->SetAlive(false);
				}
			}
			if (pNum == 4)
			{
				if (players_[0]->GetRandNumber() > players_[1]->GetRandNumber() &&
					players_[0]->GetRandNumber() > players_[2]->GetRandNumber() &&
					players_[0]->GetRandNumber() > players_[3]->GetRandNumber())
				{
					players_[0]->SetAlive(true);
					players_[1]->SetHP(-2);
					players_[2]->SetHP(-2);
					players_[3]->SetHP(-2);
					players_[1]->SetAlive(false);
					players_[2]->SetAlive(false);
					players_[3]->SetAlive(false);
				}
				if (players_[1]->GetRandNumber() > players_[0]->GetRandNumber() &&
					players_[1]->GetRandNumber() > players_[2]->GetRandNumber() &&
					players_[1]->GetRandNumber() > players_[3]->GetRandNumber())
				{
					players_[1]->SetAlive(true);
					players_[0]->SetHP(-2);
					players_[2]->SetHP(-2);
					players_[3]->SetHP(-2);
					players_[0]->SetAlive(false);
					players_[2]->SetAlive(false);
					players_[3]->SetAlive(false);
				}
				if (players_[2]->GetRandNumber() > players_[0]->GetRandNumber() &&
					players_[2]->GetRandNumber() > players_[1]->GetRandNumber() &&
					players_[2]->GetRandNumber() > players_[3]->GetRandNumber())
				{
					players_[2]->SetAlive(true);
					players_[0]->SetHP(-2);
					players_[1]->SetHP(-2);
					players_[3]->SetHP(-2);
					players_[0]->SetAlive(false);
					players_[1]->SetAlive(false);
					players_[3]->SetAlive(false);
				}
				if (players_[3]->GetRandNumber() > players_[0]->GetRandNumber() &&
					players_[3]->GetRandNumber() > players_[1]->GetRandNumber() &&
					players_[3]->GetRandNumber() > players_[2]->GetRandNumber())
				{
					players_[3]->SetAlive(true);
					players_[0]->SetHP(-2);
					players_[1]->SetHP(-2);
					players_[2]->SetHP(-2);
					players_[0]->SetAlive(false);
					players_[1]->SetAlive(false);
					players_[2]->SetAlive(false);
				}
			}
		}
	}
}


