#include <string>
#include <DxLib.h>
#include "../Utility/Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Object/Player3.h"
#include "../Object/Shot2.h"
#include "../Object/Rock.h"
#include "../Object/RockChild.h"
#include "../Object/StrartMes.h"
#include "GameScene3.h"

GameScene3::GameScene3(void)
{
}

GameScene3::~GameScene3(void)
{
}

void GameScene3::Init(void)
{

	// 画像の読み込み
	rockImg_ = LoadGraph("Data/Image/Object/rock.png");

	// ゲーム説明用の画像の読み込み
	expImage_ = LoadGraph("Data/Image/UI/game3UI.png");

	// 連打しろの画像の読み込み
	renndasiroImage_ = LoadGraph("Data/Image/UI/renndasiro.png");

	// ボタンの画像の読み込み
	LoadDivGraph("Data/Image/UI/BbottonAnim.png",
		BOTTON_MAX_NUM_ANIM,
		BOTTON_NUM_X, BOTTON_NUM_Y,
		BOTTON_SIZE_X, BOTTON_SIZE_Y,
		&BbottonImage_[0]);

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

	// プレイヤーの人数選択
	int pNum = SceneManager::GetInstance().GetPlayerNum();
	int pSize = Application::SCREEN_SIZE_X / pNum;
	int pSpace = 0;	// 2人：150　3人：100　４人：75
	if (pNum == 2)
	{
		pSpace = 242;
	}
	if (pNum == 3)
	{
		pSpace = 142;
	}
	if (pNum == 4)
	{
		pSpace = 117;
	}

	for (int i = 0; i < pNum; i++)
	{
		Player3* p = new Player3();
		InputManager::JOYPAD_NO jno = static_cast<InputManager::JOYPAD_NO>(i + 1);
		p->Init(this, jno);
		p->SetPos({ pSpace + (pSize * i), 600 });
		players_.push_back(p);
	}

	// 岩の生成
	int rNum = SceneManager::GetInstance().GetPlayerNum();;
	int rSize = Application::SCREEN_SIZE_X / rNum;
	int rSpace = 0;	// 2人：150　3人：100　４人：50
	if (rNum == 2)
	{
		rSpace = 226;
	}
	if (rNum == 3)
	{
		rSpace = 126;
	}
	if (rNum == 4)
	{
		rSpace = 101;
	}
	for (int i = 0; i < rNum; i++)
	{
		auto r = new Rock(rockImg_);
		r->SetPos({ rSpace + (rSize * i), 0 });
		rocks_.push_back(r);
	}

	// スタートメッセージの初期化
	startMes_ = new StartMes();
	startMes_->Init();

	// 背景画像の読み込み
	bgImage_ = LoadGraph("Data/Image/UI/stage3.png");

	// ゲーム説明をスキップするフラグ
	skip_ = false;

	// アニメーションのカウンタ
	cntAnim_ = 0;

	// BGMの読み込み
	bgm_ = LoadSoundMem("Data/Music/game3BGM.mp3");
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP, true);

	// 決定ボタンのSEの読み込み
	decideSE_ = LoadSoundMem("Data/Music/decideGame.mp3");

	// 爆発音
	explosionSE_ = LoadSoundMem("Data/Music/explosion1.mp3");

	inputNum_ = 0;

	startNum_ = 0;

	isStart_ = false;

	result_ = false;

	win_ = true;
}

void GameScene3::Update(void)
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

	// 弾の更新
	for (auto player : players_)
	{
		auto shots = player->GetShots();
		for (auto shot : shots)	// 範囲for文
		{
			shot->Update();
		}
	}

	for (auto rock : rocks_)
	{
		// 岩の更新
		rock->Update();

		if (rock->GetRockCount() == 100)
		{
			Result();
			result_ = true;
		}
	}
	// 衝突判定
	Collision();

}
	

void GameScene3::Draw(void)
{

	// 背景画像の描画
	DrawGraph(0, 0, bgImage_, true);

	for (auto player : players_)
	{
		// プレイヤーの描画
		player->Draw();
	}

	// 弾の描画
	for (auto player : players_)
	{
		auto shots = player->GetShots();
		for (auto shot : shots)	// 範囲for文
		{
			shot->Draw();
		}
	}

	for (auto rock : rocks_)
	{
		// 岩の描画
		rock->Draw();
	}

	// スタートメッセージの描画
	startMes_->Draw();

	cntAnim_++;

	if (!skip_)
	{
		// ゲーム説明画像の描画
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 230, 1.0f, 0.0f, expImage_, true);
		DrawGraph(470, 340, BbottonImage_[(cntAnim_ / 10) % 4], true);
		DrawGraph(820, 370, BbottonImage_[(cntAnim_ / 10) % 4], true);
	}

	if (skip_)
	{
		if (!result_)
		{
			// 敵を倒せの描画
			DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 100, 1.0f, 0.0f, renndasiroImage_, true);
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
				if (i == 0 && rocks_[i]->GetRockCount() >= 100)
				{
					// 1Pの勝利画像
					DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 200, 1.0f, 0.0f, winImage1_, true);
				}
				if (i == 0 && rocks_[i]->GetRockCount() >= 100)
				{
					// 2Pの勝利画像
					DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 200, 1.0f, 0.0f, winImage2_, true);
				}
			}
			if (pNum == 3)
			{
				if (i == 0 && rocks_[i]->GetRockCount() >= 100)
				{
					// 1Pの勝利画像
					DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 200, 1.0f, 0.0f, winImage1_, true);
				}
				if (i == 0 && rocks_[i]->GetRockCount() >= 100)
				{
					// 2Pの勝利画像
					DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 200, 1.0f, 0.0f, winImage2_, true);
				}
				if (i == 0 && rocks_[i]->GetRockCount() >= 100)
				{
					// 3Pの勝利画像
					DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 200, 1.0f, 0.0f, winImage3_, true);
				}
			}
			if (pNum == 4)
			{
				if (i == 0 && rocks_[i]->GetRockCount() >= 100)
				{
					// 1Pの勝利画像
					DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 200, 1.0f, 0.0f, winImage1_, true);
				}
				if (i == 0 && rocks_[i]->GetRockCount() >= 100)
				{
					// 2Pの勝利画像
					DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 200, 1.0f, 0.0f, winImage2_, true);
				}
				if (i == 0 && rocks_[i]->GetRockCount() >= 100)
				{
					// 3Pの勝利画像
					DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 200, 1.0f, 0.0f, winImage3_, true);
				}
				if (i == 0 && rocks_[i]->GetRockCount() >= 100)
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

}

void GameScene3::Release(void)
{

	// スタートメッセージの更新
	startMes_->Release();
	delete startMes_;

	for (auto player : players_)
	{
		// プレイヤーの開放
		player->Release();
		delete player;
	}

	// 弾の開放
	for (auto player : players_)
	{
		auto shots = player->GetShots();
		for (auto shot : shots)	// 範囲for文
		{
			shot->Release();
		}
	}

	for (auto rock : rocks_)
	{
		// 岩の開放
		rock->Release();
		delete rock;
	}

}

bool GameScene3::GetResult(void)
{
	return result_;
}

bool GameScene3::GetSkip(void)
{
	return skip_;
}

bool GameScene3::IsStart(void)
{
	return isStart_;
}

void GameScene3::SetInputNum(int input)
{
	inputNum_ += input;
}

void GameScene3::SetStartNum(int start)
{
	startNum_ += start;
}

void GameScene3::Collision(void)
{

	// 弾情報を取得する
	for (auto player : players_)
	{
		for (auto rock : rocks_)
		{

			std::vector<Shot2*> shots = player->GetShots();
			for (Shot2* shot : shots)
			{

				// 弾が生存していなければ、処理を飛ばす
				if (!shot->IsAlive())
				{
					continue;
				}

				// 弾とステージの衝突判定
				Vector2 shotPos = shot->GetPos();

				// 岩の子を取得
				std::vector<RockChild*> children = rock->GetRockChild();
				for (auto child : children)
				{
					if (child->IsAlive())
					{
						if (IsCollisionRectCenter(
							child->GetPos(), { child->SIZE_X, child->SIZE_Y },
							shot->GetPos(), { shot->SIZE_X, shot->SIZE_Y }))
						{
							// 爆発エフェクトを発生させる
							PlaySoundMem(explosionSE_, DX_PLAYTYPE_BACK, true);
							shot->ShotBlast();
							shot->Blast(shotPos);
							child->SetAlive(false);
							rock->AddCnt(1);
						}
					}
				}

			}
		}

	}
}

bool GameScene3::IsCollisionRect(Vector2 stPos1, Vector2 edPos1, Vector2 stPos2, Vector2 edPos2)
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

bool GameScene3::IsCollisionRectCenter(Vector2 centerPos1, Vector2 size1, Vector2 centerPos2, Vector2 size2)
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

void GameScene3::Result(void)
{

	int pNum = SceneManager::GetInstance().GetPlayerNum();
	for (int i = 0; i < pNum; i++)
	{
		if (pNum == 2)
		{
			if (rocks_[0]->GetRockCount() >= 100)
			{
				if(win_)
				{
					SceneManager::GetInstance().SetWin1(1);
					win_ = false;
				}
			}
			if (rocks_[1]->GetRockCount() >= 100)
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
			if (i == 0 && rocks_[0]->GetRockCount() >= 100)
			{
				if (win_)
				{
					SceneManager::GetInstance().SetWin1(1);
					win_ = false;
				}
			}
			if (i == 1 && rocks_[1]->GetRockCount() >= 100)
			{
				if (win_)
				{
					SceneManager::GetInstance().SetWin2(1);
					win_ = false;
				}
			}
			if (i == 2 && rocks_[2]->GetRockCount() >= 100)
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
			if (i == 0 && rocks_[0]->GetRockCount() >= 100)
			{
				if (win_)
				{
					SceneManager::GetInstance().SetWin1(1);
					win_ = false;
				}
			}
			if (i == 1 && rocks_[1]->GetRockCount() >= 100)
			{
				if (win_)
				{
					SceneManager::GetInstance().SetWin2(1);
					win_ = false;
				}
			}
			if (i == 2 && rocks_[2]->GetRockCount() >= 100)
			{
				if (win_)
				{
					SceneManager::GetInstance().SetWin3(1);
					win_ = false;
				}
			}
			if (i == 3 && rocks_[3]->GetRockCount() >= 100)
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
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME4);
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
