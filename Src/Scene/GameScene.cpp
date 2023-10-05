#include <string>
#include <DxLib.h>
#include "../Utility/Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Object/Player.h"
#include "../Object/Meteor.h"
#include "../Object/MeteorChild.h"
#include "../Object/StrartMes.h"
#include "../Scene/ResultScene.h"
#include "GameScene.h"

GameScene::GameScene(void)
{
}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{

	// 背景画像の読み込み
	bgImage_ = LoadGraph("Data/Image/UI/BackGround.png");

	// ゲーム説明用の画像
	expImage_ = LoadGraph("Data/Image/UI/game1UI.png");

	// 生き残れの読み込み
	ikinokore_ = LoadGraph("Data/Image/UI/ikinokore.png");

	// 隕石の画像の読み込み
	LoadDivGraph("Data/Image/Object/Meteor.png",
		METEOR_MAX_NUM_ANIM,
		METEOR_MAX_NUM_ANIM, 1,
		METEOR_SIZE_X, METEOR_SIZE_Y,
		&meteorImage_[0]);

	// ボタンの画像の読み込み
	LoadDivGraph("Data/Image/UI/BbottonAnim.png",
		BOTTON_MAX_NUM_ANIM,
		BOTTON_NUM_X,BOTTON_NUM_Y,
		BOTTON_SIZE_X,BOTTON_SIZE_Y,
		&BbottonImage_[0]);

	// エフェクトの読み込み
	LoadDivGraph("Data/Image/Player/hitEffect.png",
		EFFECT_MAX_NUM_ANIM,
		EFFECT_NUM_X, EFFECT_NUM_Y,
		EFECT_SIZE_X, EFECT_SIZE_Y,
		&hitEffectImage_[0]);

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
		&allDice_[0]);

	// 1つずつのサイコロの画像の読み込み
	dice1_ = LoadGraph("Data/Image/UI/Dice1.png");
	dice2_ = LoadGraph("Data/Image/UI/Dice2.png");
	dice3_ = LoadGraph("Data/Image/UI/Dice3.png");
	dice4_ = LoadGraph("Data/Image/UI/Dice4.png");
	dice5_ = LoadGraph("Data/Image/UI/Dice5.png");
	dice6_ = LoadGraph("Data/Image/UI/Dice6.png");

	// サイコロを振れ
	saikoro_ = LoadGraph("Data/Image/UI/saikoro.png");

	// プレイヤーの人数選択
	int pNum = SceneManager::GetInstance().GetPlayerNum();
	int pSize = Application::SCREEN_SIZE_X / pNum;
	int pSpace = 0;	// 2人：150　3人：100　４人：75
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
		Player* p = new Player();
		InputManager::JOYPAD_NO jno = static_cast<InputManager::JOYPAD_NO>(i + 1);
		p->Init(this, jno);
		p->SetPos({ pSpace + (pSize * i), 500 });
		players_.push_back(p);
	}

	// 隕石の生成
	int mNum = SceneManager::GetInstance().GetPlayerNum();;
	int mSize = Application::SCREEN_SIZE_X / mNum;
	int mSpace = 0;	// 2人：150　3人：100　４人：50
	if (mNum == 2)
	{
		mSpace = 220;
	}
	if (mNum == 3)
	{
		mSpace = 120;
	}
	if (mNum == 4)
	{
		mSpace = 95;
	}
	for (int i = 0; i < mNum; i++)
	{
		auto m = new Meteor(meteorImage_, METEOR_MAX_NUM_ANIM);
		m->Init(this);
		m->SetPos({ mSpace + (mSize * i), 0 });
		meteors_.push_back(m);
	}

	// スタートメッセージの初期化
	startMes_ = new StartMes();
	startMes_->Init();

	// ゲーム説明をスキップするフラグ
	skip_ = false;

	// ダメージを食らった時の音の読み込み
	damageSE_ = LoadSoundMem("Data/Music/explosion1.mp3");

	// BGMの読み込み
	bgm_ = LoadSoundMem("Data/Music/game1BGM.mp3");
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP, true);

	// 決定ボタンのSEの読み込み
	decideSE_ = LoadSoundMem("Data/Music/decideGame.mp3");

	// アニメーションのカウンタ
	cntAnim_ = 0;

	// アニメーションスピード
	speedAnim_ = 0.3f;

	inputNum_ = 0;

	startNum_ = 0;

	isStart_ = false;

	result_ = false;

	revival_ = false;

	isRand1_ = true;
	isRand2_ = true;
	isRand3_ = true;
	isRand4_ = true;

	win_ = true;
	inputRandNum_ = 0;

	revivalHP_ = true;

	win_ = true;
}
 
void GameScene::Update(void)
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

	for (auto player : players_)
	{
		// プレイヤーの更新
		player->Update();
	}

	if (!revival_)
	{
		if (!result_)
		{
			// 隕石の更新
			for (auto meteor : meteors_)	// 範囲for文
			{
				meteor->Update();
			}
			// 衝突判定
			Collision();
		}
	}

	// シーン遷移
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
					players_[0]->SetHP(-100);
					players_[0]->SetAlive(true);
				}
				if (i == 1 && players_[1]->OldAlive())
				{
					players_[1]->SetHP(-100);
					players_[1]->SetAlive(true);
				}
				if (i == 2 && players_[2]->OldAlive())
				{
					players_[2]->SetHP(-100);
					players_[2]->SetAlive(true);
				}
				if (i == 3 && players_[3]->OldAlive())
				{
					players_[3]->SetHP(-100);
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

void GameScene::Draw(void)
{

	// 背景画像の描画
	DrawGraph(0, 0, bgImage_, true);

	// スタートメッセージの描画
	startMes_->Draw();

	if (skip_)
	{
		if (!result_ && !revival_)
		{
			// 生き残れ画像の描画
			DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 200, 1.0f, 0.0f, ikinokore_, true);
		}
	}

	if (!skip_)
	{
		// ゲーム説明画像の描画
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 230, 1.0f, 0.0f, expImage_, true);
		DrawGraph(450, 350, BbottonImage_[(cntAnim_ / 10) % 4], true);
		DrawGraph(840, 375, BbottonImage_[(cntAnim_ / 10) % 4], true);
	}

	for (auto player : players_)
	{
		// プレイヤーの描画
		player->Draw();
	}

	// 隕石の描画
	if (!result_)
	{
		for (auto meteor : meteors_)	// 範囲for文
		{
			meteor->Draw();
		}
	}
	cntAnim_++;

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

void GameScene::Release(void)
{

	// スタートメッセージの更新
	startMes_->Release();
	delete startMes_;

	// プレイヤーの開放
	auto players = players_;
	for (auto player : players_)
	{
		player->Release();
		delete player;
	}

	// 弾の開放
	for (auto meteor : meteors_)
	{
		meteor->Release();
		delete meteor;
	}

	DeleteGraph(bgImage_);
	DeleteGraph(expImage_);
	DeleteGraph(BbottonImage_[BOTTON_MAX_NUM_ANIM]);
	DeleteGraph(ikinokore_);
}

bool GameScene::GetResult(void)
{
	return result_;
}

bool GameScene::GetSkip(void)
{
	return skip_;
}

bool GameScene::IsStart(void)
{
	return isStart_;
}

void GameScene::SetInputNum(int input)
{
	inputNum_ += input;
}

void GameScene::SetStartNum(int start)
{
	startNum_ += start;
}

bool GameScene::GetRevival(void)
{
	return revival_;
}

void GameScene::Collision(void)
{

	// 隕石のY座標がプレイヤーのY座標が大きくなったらダメージを与える
	int pNum = SceneManager::GetInstance().GetPlayerNum();
	for (int i = 0; i < pNum; i++)
	{
		for (auto meteorChild : meteors_[i]->GetMeteorChildlen())
		{
			if (!meteorChild->IsAlive())
			{
				continue;
			}
			// 衝突判定
			if (meteorChild->GetMeteorPos().y >= players_[i]->GetPos().y)
			{
				if (!players_[i]->GetButton())
				{
					players_[i]->SetHP(10);
					meteorChild->SetAlive(false);
					// ダメージを食らった時の音
					ChangeVolumeSoundMem(255 * 0.5, damageSE_);
					// 弾の爆発
					meteorChild->Blast(meteorChild->GetMeteorPos());
					PlaySoundMem(damageSE_, DX_PLAYTYPE_BACK, true);
				}
			}
			if (meteorChild->GetMeteorPos().y >= players_[i]->GetPos().y)
			{
				if (players_[i]->GetButton())
				{
					meteorChild->SetAlive(false);
				}
			}
		}
	}
}

bool GameScene::IsCollisionRect(Vector2 stPos1, Vector2 edPos1, Vector2 stPos2, Vector2 edPos2)
{

	// 矩形同士の衝突判定
	// 矩形１の左よりも、矩形２の右が大きい
	// 矩形２の左よりも、矩形１の右が大きい
	if (stPos1.x < edPos2.x
		&& stPos2.x < edPos1.x
		&& stPos1.y < edPos2.y
		&& stPos2.y < edPos1.y)
	{
		return true;
	}
	return false;

}

bool GameScene::IsCollisionRectCenter(Vector2 centerPos1, Vector2 size1, Vector2 centerPos2, Vector2 size2)
{

	// 矩形1(左上座標、右上座標)
	Vector2 stPos1 = centerPos1;
	Vector2 edPos1 = centerPos1;
	Vector2 hSize1 = { size1.x / 2, size1.y / 2 };

	stPos1.x -= hSize1.x;
	stPos1.y -= hSize1.y;
	edPos1.x += hSize1.x;
	edPos1.y += hSize1.y;

	// 矩形２(左上座標、右上座標)
	Vector2 stPos2 = centerPos2;
	Vector2 edPos2 = centerPos2;
	Vector2 hSize2 = { size2.x / 2, size2.y / 2 };

	stPos2.x -= hSize2.x;
	stPos2.y -= hSize2.y;
	edPos2.x += hSize2.x;
	edPos2.y += hSize2.y;

	// 矩形同士の衝突判定
	// 矩形１の左よりも、矩形２の右が大きい
	// 矩形２の左よりも、矩形１の右が大きい
	if (IsCollisionRect(stPos1, edPos1, stPos2, edPos2))
	{
		return true;
	}
	return false;

}

void GameScene::Result(void)
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
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME2);
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

}

void GameScene::Rand(void)
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
				int i = 0;
				if (players_[0]->GetRandNumber() > players_[1]->GetRandNumber())
				{
						players_[0]->SetAlive(true);
						players_[1]->SetHP(100);
						players_[1]->SetAlive(false);
				}
				if (players_[1]->GetRandNumber() > players_[0]->GetRandNumber())
				{
					players_[1]->SetAlive(true);
					players_[0]->SetHP(100);
					players_[0]->SetAlive(false);
				}
			}
			if (pNum == 3)
			{
				if (players_[0]->GetRandNumber() > players_[1]->GetRandNumber() &&
					players_[0]->GetRandNumber() > players_[2]->GetRandNumber())
				{

					players_[0]->SetAlive(true);
					players_[1]->SetHP(100);
					players_[2]->SetHP(100);
					players_[1]->SetAlive(false);
					players_[2]->SetAlive(false);
				}
				if (players_[1]->GetRandNumber() > players_[0]->GetRandNumber() &&
					players_[1]->GetRandNumber() > players_[2]->GetRandNumber())
				{
					players_[0]->SetAlive(true);
					players_[0]->SetHP(100);
					players_[2]->SetHP(100);
					players_[0]->SetAlive(false);
					players_[2]->SetAlive(false);
				}
				if (players_[2]->GetRandNumber() > players_[0]->GetRandNumber() &&
					players_[2]->GetRandNumber() > players_[1]->GetRandNumber())
				{
					players_[0]->SetAlive(true);
					players_[0]->SetHP(100);
					players_[1]->SetHP(100);
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
					players_[1]->SetHP(100);
					players_[2]->SetHP(100);
					players_[3]->SetHP(100);
					players_[1]->SetAlive(false);
					players_[2]->SetAlive(false);
					players_[3]->SetAlive(false);
				}
				if (players_[1]->GetRandNumber() > players_[0]->GetRandNumber() &&
					players_[1]->GetRandNumber() > players_[2]->GetRandNumber() &&
					players_[1]->GetRandNumber() > players_[3]->GetRandNumber())
				{
					players_[1]->SetAlive(true);
					players_[0]->SetHP(100);
					players_[2]->SetHP(100);
					players_[3]->SetHP(100);
					players_[0]->SetAlive(false);
					players_[2]->SetAlive(false);
					players_[3]->SetAlive(false);
				}
				if (players_[2]->GetRandNumber() > players_[0]->GetRandNumber() &&
					players_[2]->GetRandNumber() > players_[1]->GetRandNumber() &&
					players_[2]->GetRandNumber() > players_[3]->GetRandNumber())
				{
					players_[2]->SetAlive(true);
					players_[0]->SetHP(100);
					players_[1]->SetHP(100);
					players_[3]->SetHP(100);
					players_[0]->SetAlive(false);
					players_[1]->SetAlive(false);
					players_[3]->SetAlive(false);
				}
				if (players_[3]->GetRandNumber() > players_[0]->GetRandNumber() &&
					players_[3]->GetRandNumber() > players_[1]->GetRandNumber() &&
					players_[3]->GetRandNumber() > players_[2]->GetRandNumber())
				{
					players_[3]->SetAlive(true);
					players_[0]->SetHP(100);
					players_[1]->SetHP(100);
					players_[2]->SetHP(100);
					players_[0]->SetAlive(false);
					players_[1]->SetAlive(false);
					players_[2]->SetAlive(false);
				}
			}
		}
	}
}
