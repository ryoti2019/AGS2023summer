#include <DxLib.h>
#include "../Utility/Application.h"
#include "../Manager/SceneManager.h"
#include "Player4.h"

Player4::Player4()
{
}

Player4::~Player4(void)
{
}

void Player4::Init(GameScene4* scene, InputManager::JOYPAD_NO playerNo)
{

	int dirNum = static_cast<int>(AsoUtility::DIR::MAX);
	int allNum = PLAYER_MAX_NUM_ANIM * dirNum;
	switch (playerNo)
	{
	case InputManager::JOYPAD_NO::PAD1:
		// プレイヤー画像の読み込み
		LoadDivGraph("Data/Image/Player/1P.png",
			allNum,
			NUM_X, dirNum,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImg_[0][0]);
		playerUIImage_ = LoadGraph("Data/Image/UI/1P.png");
		break;
	case InputManager::JOYPAD_NO::PAD2:
		// プレイヤー画像の読み込み
		LoadDivGraph("Data/Image/Player/2P.png",
			allNum,
			NUM_X, dirNum,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImg_[0][0]);
		playerUIImage_ = LoadGraph("Data/Image/UI/2P.png");
		break;
	case InputManager::JOYPAD_NO::PAD3:
		// プレイヤー画像の読み込み
		LoadDivGraph("Data/Image/Player/3P.png",
			allNum,
			NUM_X, dirNum,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImg_[0][0]);
		playerUIImage_ = LoadGraph("Data/Image/UI/3P.png");
		break;
	case InputManager::JOYPAD_NO::PAD4:
		// プレイヤー画像の読み込み
		LoadDivGraph("Data/Image/Player/4P.png",
			allNum,
			NUM_X, dirNum,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImg_[0][0]);
		playerUIImage_ = LoadGraph("Data/Image/UI/4P.png");
		break;
	}

	// ハート画像の読み込み
	heartImage_ = LoadGraph("Data/Image/UI/Heart.png");

	// ゲームシーンの機能を使えるようにする
	gameScene_ = scene;

	// ゲームパッドの番号
	padNo_ = playerNo;

	// 方向
	dir_ = AsoUtility::DIR::DOWN;

	// 移動速度
	speed_ = 5.0f;

	// 生存フラグ
	isAlive_ = true;

	// １個前の生存フラグ
	oldAlive_ = true;

	// HP
	hp_ = 2;

	// HPを1減らすためのフラグ
	subtract_ = false;

	int pNum = SceneManager::GetInstance().GetPlayerNum();
	if (pNum == 2)
	{
		pSpace_ = 224;
	}
	if (pNum == 3)
	{
		pSpace_ = 140;
	}
	if (pNum == 4)
	{
		pSpace_ = 96;
	}

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

void Player4::Update(void)
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

	if (gameScene_->GetSkip())
	{
		if (gameScene_->IsStart())
		{
			if (hp_ <= 0)
			{
				isAlive_ = false;
			}
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
			}

			if (pad.AKeyLY > 0.0f)
			{
				// 下移動
				movedPos.y += speed_;

				// 向きの変更
				dir_ = AsoUtility::DIR::DOWN;
			}

			// 移動処理(X)
			if (pad.AKeyLX < 0.0f)
			{
				// 左移動
				movedPos.x -= speed_;

				// 向きの変更
				dir_ = AsoUtility::DIR::LEFT;
			}

			if (pad.AKeyLX > 0.0f)
			{
				// 右移動
				movedPos.x += speed_;

				// 向きの変更
				dir_ = AsoUtility::DIR::RIGHT;
			}

			// 衝突判定
			footPos = movedPos;
			footPos.y += 50;

			leftFootPos = movedPos;
			leftFootPos.x -= 25;
			leftFootPos.y += 50;

			rightFootPos = movedPos;
			rightFootPos.x += 25;
			rightFootPos.y += 50;

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

			// 左右の判定をする
			if (pos_.x <= Application::SCREEN_SIZE_X / 2)
			{
				// 左
				left_ = true;
				right_ = false;
			}
			else if (pos_.x >= Application::SCREEN_SIZE_X / 2)
			{
				// 右
				left_ = false;
				right_ = true;
			}

			// 右左が合っていなかったらHPを減らす
			// 左
			if (left_ && gameScene_->GetL() && subtract_)
			{
				hp_ -= 1;
				subtract_ = false;
			}

			if (right_ && gameScene_->GetL() && subtract_)
			{
				subtract_ = false;
			}
			// 右
			if (right_ && gameScene_->GetR() && subtract_)
			{
				hp_ -= 1;
				subtract_ = false;
			}
			if (left_ && gameScene_->GetR() && subtract_)
			{
				subtract_ = false;
			}

			if (hp_ <= 0)
			{
				isAlive_ = false;
			}
		}
	}

	if (!isAlive_ && !death_)
	{
		PlaySoundMem(deathSE_, DX_PLAYTYPE_BACK, true);
		death_ = true;
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

	if (gameScene_->GetRevival())
	{
		if (ins.IsPadBtnTrgDown(padNo_, InputManager::JOYPAD_BTN::RIGHT) && !inputRevival_)
		{
			inputRevival_ = true;
		}
	}

}

void Player4::Draw(void)
{

	int pNum = SceneManager::GetInstance().GetPlayerNum();
	int pSize = Application::SCREEN_SIZE_X / pNum;
	DrawRotaGraph(pSpace_ + ((int)padNo_ - 1) * pSize + 32, 25, 1.0f, 0.0f, playerUIImage_, true);

	// HPが0になったら処理を中止する
	if (hp_ <= 0)
	{
		return;
	}
	// プレイヤー画像の描画
	// アニメーションのチップ番号(0～3)を作る
	animData_[0] = 0;
	animData_[1] = 1;
	animData_[2] = 2;
	animData_[3] = 1;
	DrawRotaGraph(pos_.x, pos_.y, 1.0f, 0.0f, playerImg_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
	cntAnim_++;


	// ハート画像の描画
	if (pNum == 2)
	{
		for (int i = 0; i < hp_; i++)
		{
			DrawRotaGraph(pSpace_ + ((int)padNo_ - 1) * pSize + i * 64, 75, 1.0f, 0.0f, heartImage_, true);
		}
	}
	if (pNum == 3)
	{
		for (int i = 0; i < hp_; i++)
		{
			DrawRotaGraph(pSpace_ + ((int)padNo_ - 1) * pSize + i * 64, 75, 1.0f, 0.0f, heartImage_, true);
		}
	}
	if (pNum == 4)
	{
		for (int i = 0; i < hp_; i++)
		{
			DrawRotaGraph(pSpace_ + ((int)padNo_ - 1) * pSize + i * 64, 75, 1.0f, 0.0f, heartImage_, true);
		}
	}
}

void Player4::Release(void)
{
	DeleteGraph(playerImg_[static_cast<int>(AsoUtility::DIR::MAX) - 1][PLAYER_MAX_NUM_ANIM]);
}

Vector2 Player4::GetPos(void)
{
	return pos_;
}

void Player4::SetPos(Vector2 pos)
{
	pos_ = pos;
}

void Player4::SetDir(AsoUtility::DIR dir)
{
	dir_ = dir;
}

bool Player4::GetR(void)
{
	return right_;
}

void Player4::SetR(bool right)
{
	right_ = right;
}

bool Player4::GetL(void)
{
	return left_;
}

void Player4::SetL(bool left)
{
	left_ = left;
}

void Player4::SetSubTract(bool subtract)
{
	subtract_ = subtract;
}

bool Player4::IsAlive(void)
{
	return isAlive_;
}

void Player4::SetAlive(bool alive)
{
	isAlive_ = alive;
}

bool Player4::OldAlive(void)
{
	return oldAlive_;
}

bool Player4::GetInputStart(void)
{
	return inputStart_;
}

bool Player4::GetInputPlayer(void)
{
	return inputPlayer_;
}

void Player4::SetHP(int hp)
{
	hp_ += hp;
}

int Player4::GetHP(void)
{
	return hp_;
}

int Player4::GetRandNumber(void)
{
	return randNumber_;
}

void Player4::SetRandNumber(int rand)
{
	randNumber_ = rand;
}

bool Player4::GetInputRevival(void)
{
	return inputRevival_;
}

void Player4::DrawDebug(void)
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
	footPos.y += 50;

	// デバッグ用：足元左衝突判定
	Vector2 leftFootPos = movedPos;
	leftFootPos.x -= 25;
	leftFootPos.y += 50;

	// デバッグ用：足元右衝突判定
	Vector2 rightFootPos = movedPos;
	rightFootPos.x += 25;
	rightFootPos.y += 50;

	// 足元：中央
	DrawBox(footPos.x - 3, footPos.y - 3,
		footPos.x + 3, footPos.y + 3, color, true);

	// 足元：左
	DrawBox(leftFootPos.x - 3, leftFootPos.y - 3,
		leftFootPos.x + 3, leftFootPos.y + 3, color, true);

	// 足元：右
	DrawBox(rightFootPos.x - 3, rightFootPos.y - 3,
		rightFootPos.x + 3, rightFootPos.y + 3, color, true);

	if (right_)
	{
		DrawFormatString(0, (int)padNo_ * 20, 0xffffff, "右");
	}
	if (left_)
	{
		DrawFormatString(0, (int)padNo_ * 20, 0xffffff, "左");
	}

}


