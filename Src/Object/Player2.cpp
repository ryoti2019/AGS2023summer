#include <DxLib.h>
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Utility/Application.h"
#include "../Common/Vector2.h"
#include "../Object/shot.h"
#include "Player2.h"

Player2::Player2()
{
}

Player2::~Player2(void)
{
}

void Player2::Init(GameScene2* scene, InputManager::JOYPAD_NO playerNo)
{

	int dirNum = static_cast<int>(AsoUtility::DIR::MAX);
	int allNum = PLAYER_MAX_NUM_ANIM * dirNum;
	switch (playerNo)
	{
	case InputManager::JOYPAD_NO::PAD1:
		// プレイヤー画像の読み込み
		LoadDivGraph("Data/Image/Player/1P_1.png",
			allNum,
			NUM_X, dirNum,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImg_[0][0]);
		// プレイヤーの死亡画像の読み込み
		playerDeathImage = LoadGraph("Data/Image/Player/1P_1Death.png");
		break;
	case InputManager::JOYPAD_NO::PAD2:
		// プレイヤー画像の読み込み
		LoadDivGraph("Data/Image/Player/2P_1.png",
			allNum,
			NUM_X, dirNum,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImg_[0][0]);
		// プレイヤーの死亡画像の読み込み
		playerDeathImage = LoadGraph("Data/Image/Player/2P_1Death.png");
		break;
	case InputManager::JOYPAD_NO::PAD3:
		// プレイヤー画像の読み込み
		LoadDivGraph("Data/Image/Player/3P_1.png",
			allNum,
			NUM_X, dirNum,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImg_[0][0]);
		// プレイヤーの死亡画像の読み込み
		playerDeathImage = LoadGraph("Data/Image/Player/3P_1Death.png");
		break;
	case InputManager::JOYPAD_NO::PAD4:
		// プレイヤー画像の読み込み
		LoadDivGraph("Data/Image/Player/4P_1.png",
			allNum,
			NUM_X, dirNum,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImg_[0][0]);
		// プレイヤーの死亡画像の読み込み
		playerDeathImage = LoadGraph("Data/Image/Player/4P_1Death.png");
		break;
	}

	// 弾画像の初期化
	LoadDivGraph("Data/Image/Player/shot.png",
		SHOT_MAX_NUM_ANIM,
		SHOT_NUM_X, SHOT_NUM_Y,
		SHOT_SIZE_X, SHOT_SIZE_Y,
		&shotImgs_[0]);

	// ゲームシーンの機能を使えるようにする
	gameScene_ = scene;

	// ゲームパッドの番号
	padNo_ = playerNo;

	// 方向
	dir_ = AsoUtility::DIR::DOWN;

	// 移動速度
	speed_ = 5.0f;

	// 生存の判定
	isAlive_ = true;

	// 点滅の判定
	isBlink_ = false;

	// ボタンの押下判定
	button_ = false;

	// 体力
	hpMax_ = 10;
	hp_ = hpMax_;

	// 攻撃の音
	shotSE_ = LoadSoundMem("Data/Music/shot.mp3");

	// 決定ボタンのSEの読み込み
	decideSE_ = LoadSoundMem("Data/Music/decideGame.mp3");

	// プレイヤーがOKボタンを押したときの音の読み込み
	playerDecideSE_ = LoadSoundMem("Data/Music/PlayerDecide.mp3");

	// 死んだときの音
	deathSE_ = LoadSoundMem("Data/Music/K.O..mp3");

	death_ = false;

	inputStart_ = false;

	inputPlayer_ = false;

	randNumber_ = 0;

}

void Player2::Update(void)
{

	auto& ins = InputManager::GetInstance();
	if (ins.IsPadBtnTrgDown(padNo_, InputManager::JOYPAD_BTN::RIGHT) && !inputStart_)
	{
		inputStart_ = true;
		gameScene_->SetStartNum(1);
		PlaySoundMem(decideSE_, DX_PLAYTYPE_BACK, true);
	}

	aliveCnt_++;
	if (aliveCnt_ <= 1)
	{
		oldAlive_ = isAlive_;
		aliveCnt_ = 0;
	}

	if (!gameScene_->GetRevival())
	{
		if (gameScene_->GetSkip())
		{
			if (gameScene_->IsStart())
			{
				if (hp_ <= 0)
				{
					isAlive_ = false;
				}

				if (!gameScene_->GetResult())
				{
					auto& ins = InputManager::GetInstance();
					auto pad = ins.GetJPadInputState(padNo_);

					// 移動前座標を確保
					Vector2 prePos = pos_;

					// 移動予定の座標を確保
					Vector2 movedPos = pos_;

					// 足元衝突判定
					Vector2 footPos;

					// 足元右衝突判定
					Vector2 rightFootPos;

					// 足元右衝突判定
					Vector2 leftFootPos;

					// 移動処理(Y)
					if (pad.AKeyLY < 0.0f)
					{
						// 上移動
						movedPos.y -= speed_;

						// 向きの変更
						dir_ = AsoUtility::DIR::UP;

						// アニメーションカウンタの進行
						cntAnim_++;
					}

					if (pad.AKeyLY > 0.0f)
					{
						// 下移動
						movedPos.y += speed_;

						// 向きの変更
						dir_ = AsoUtility::DIR::DOWN;

						// アニメーションカウンタの進行
						cntAnim_++;
					}

					// 移動処理(X)
					if (pad.AKeyLX < 0.0f)
					{
						// 左移動
						movedPos.x -= speed_;

						// 向きの変更
						dir_ = AsoUtility::DIR::LEFT;

						// アニメーションカウンタの進行
						cntAnim_++;
					}

					if (pad.AKeyLX > 0.0f)
					{
						// 右移動
						movedPos.x += speed_;

						// 向きの変更
						dir_ = AsoUtility::DIR::RIGHT;

						// アニメーションカウンタの進行
						cntAnim_++;
					}

					// 衝突判定
					footPos = movedPos;
					footPos.y += 10;

					leftFootPos = movedPos;
					leftFootPos.x -= 10;
					leftFootPos.y += 10;

					rightFootPos = movedPos;
					rightFootPos.x += 10;
					rightFootPos.y += 10;

					// ステージの衝突判定
					if (gameScene_->IsCollisionStage(movedPos) == true
						|| gameScene_->IsCollisionStage(footPos) == true
						|| gameScene_->IsCollisionStage(rightFootPos) == true
						|| gameScene_->IsCollisionStage(leftFootPos) == true)
					{
						// 衝突している -> 座標を元に戻す
						movedPos = pos_;
					}
					else
					{
						// 移動可能と判断できたので、現座標を更新
						pos_ = movedPos;
					}

					// 攻撃
					Attack();
				}
				if (!isAlive_ && !death_)
				{
					PlaySoundMem(deathSE_, DX_PLAYTYPE_BACK, true);
					death_ = true;
				}


			}

		}
	}

	if (gameScene_->GetRevival())
	{
		if (ins.IsPadBtnTrgDown(padNo_, InputManager::JOYPAD_BTN::RIGHT) && !inputRevival_)
		{
			inputRevival_ = true;
		}
	}

	if (gameScene_->GetResult())
	{
		if (ins.IsPadBtnTrgDown(padNo_, InputManager::JOYPAD_BTN::RIGHT) && !inputPlayer_)
		{
			inputPlayer_ = true;
			gameScene_->SetInputNum(1);
			PlaySoundMem(playerDecideSE_, DX_PLAYTYPE_BACK, true);
		}
	}
}


void Player2::Draw(void)
{

	if (!isAlive_)
	{
		pos_.y -= 5;
	}

	if (!isAlive_)
	{
		DrawRotaGraph(pos_.x, pos_.y, 1.0f, 0.0f, playerDeathImage, true);
	}

	// プレイヤー画像の描画
	// アニメーションのチップ番号(0～3)を作る
	animData_[0] = 0;
	animData_[1] = 1;
	animData_[2] = 2;
	animData_[3] = 1;
	if (isAlive_)
	{
		DrawRotaGraph(pos_.x, pos_.y, 1.0f, 0.0f, playerImg_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
	}
	cntAnim_++;
}

void Player2::Release(void)
{
	DeleteGraph(playerImg_[static_cast<int>(AsoUtility::DIR::MAX) - 1][PLAYER_MAX_NUM_ANIM]);
}

int Player2::GetHP(void)
{
	return hp_;
}

void Player2::SetHP(int hp)
{
	hp_ -= hp;
}

Vector2 Player2::GetPos(void)
{
	return pos_;
}

void Player2::SetPos(Vector2 pos)
{
	pos_ = pos;
}

bool Player2::IsAlive(void)
{
	return isAlive_;
}

void Player2::SetAlive(bool alive)
{
	isAlive_ = alive;
}

bool Player2::OldAlive(void)
{
	return oldAlive_;
}

bool Player2::GetButton(void)
{
	return button_;
}

std::vector<Shot*> Player2::GetShots(void)
{
	return shots_;
}

bool Player2::GetInputStart(void)
{
	return inputStart_;
}

bool Player2::GetInputPlayer(void)
{
	return inputPlayer_;
}

int Player2::GetRandNumber(void)
{
	return randNumber_;
}

void Player2::SetRandNumber(int rand)
{
	randNumber_ = rand;
}

bool Player2::GetInputRevival(void)
{
	return inputRevival_;
}

void Player2::DrawDebug(void)
{

	// 移動予定の座標を確保
	Vector2 movedPos = pos_;

	// デバッグ用
	DrawBox(pos_.x - 3,
		pos_.y - 3,
		pos_.x + 3,
		pos_.y + 3,
		0xff0000, true);

	// オレンジ
	int color = 0xff8c00;

	// デバッグ用：足元衝突判定
	Vector2 footPos = movedPos;
	footPos.y += 10;

	// デバッグ用：足元左衝突判定
	Vector2 leftFootPos = movedPos;
	leftFootPos.x -= 10;
	leftFootPos.y += 10;

	// デバッグ用：足元右衝突判定
	Vector2 rightFootPos = movedPos;
	rightFootPos.x += 10;
	rightFootPos.y += 10;

	// 足元：中央
	DrawBox(footPos.x - 3, footPos.y - 3, 
		footPos.x + 3, footPos.y + 3, color, true);

	// 足元：左
	DrawBox(leftFootPos.x - 3, leftFootPos.y - 3,
		leftFootPos.x + 3, leftFootPos.y + 3, color, true);

	// 足元：右
	DrawBox(rightFootPos.x - 3, rightFootPos.y - 3,
		rightFootPos.x + 3, rightFootPos.y + 3, color, true);

}

void Player2::Attack(void)
{

	auto& ins = InputManager::GetInstance();
	auto pad = ins.GetJPadInputState(padNo_);

	// 攻撃キーを押すと、弾を生成する
	if (InputManager::GetInstance().IsPadBtnTrgDown(padNo_, InputManager::JOYPAD_BTN::RIGHT) && stepShotDelay_ <= 0.0f)
	{
		// 攻撃の音
		PlaySoundMem(shotSE_,DX_PLAYTYPE_BACK,true);

		// 有効な球を取得する
		Shot* shot = GetValidShot();

		// 座標をずらす
		Vector2 pos = pos_;

		// 弾を生成(弾発射の準備)
		Vector2F dir = AsoUtility::Normalize(dir_);

		shot->CreateShot(pos.ToVector2F(), dir);

		// 弾の発射後の硬直時間セット
		stepShotDelay_ = SHOT_DELAY;

	}

	if (stepShotDelay_ > 0.0f)
	{

		// 弾発射後の硬直時間を減らしていく
		stepShotDelay_ -= 1.0f / SceneManager::DEFAULT_FPS;

	}

}

Shot* Player2::GetValidShot(void)
{

	size_t size = shots_.size();
	for (int i = 0; i < size; i++)
	{
		if (!shots_[i]->IsAlive())
		{
			return shots_[i];
		}
	}

	Shot* shot = new Shot(shotImgs_, SHOT_MAX_NUM_ANIM);
	shots_.push_back(shot);

	return shot;

}
