#include <string>
#include "Player5.h"

Player5::Player5()
{
}

Player5::~Player5(void)
{
}

void Player5::Init(GameScene5* scene, InputManager::JOYPAD_NO playerNo)
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
		break;
	case InputManager::JOYPAD_NO::PAD2:
		// プレイヤー画像の読み込み
		LoadDivGraph("Data/Image/Player/2P.png",
			allNum,
			NUM_X, dirNum,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImg_[0][0]);
		break;
	case InputManager::JOYPAD_NO::PAD3:
		// プレイヤー画像の読み込み
		LoadDivGraph("Data/Image/Player/3P.png",
			allNum,
			NUM_X, dirNum,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImg_[0][0]);
		break;
	case InputManager::JOYPAD_NO::PAD4:
		// プレイヤー画像の読み込み
		LoadDivGraph("Data/Image/Player/4P.png",
			allNum,
			NUM_X, dirNum,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImg_[0][0]);
		break;
	}

	// 入力したときの画像の読み込み
	inputImage_ = LoadGraph("Data/Image/UI/Green.png");

	// まだ入力されていないときの画像の読み込み
	notInputImage_ = LoadGraph("Data/Image/UI/Black.png");

	arrowImage_ = LoadGraph("Data/Image/UI/playerArrow.png");

	// 〇画像
	maruImage_ = LoadGraph("Data/Image/UI/maru.png");

	// ×画像
	batuImage_ = LoadGraph("Data/Image/UI/batu.png");

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

	// 体力
	hpMax_ = 5;
	hp_ = hpMax_;

	// HPを1減らすためのフラグ
	subtract_ = true;

	// 入力した数
	pushCnt_ = 0;

	// 入力しないといけない数
	pushMax_ = 5;

	// 入力したものを格納する配列
	direction_ = std::vector<int>(pushMax_);

	inputAlive_ = false;

	// 矢印が最大値分描画させるためのカウンタ
	arrowCnt_ = 0;

	// ダメージを食らった時
	damage_ = false;

	// 入力したときの音
	inputSE_ = LoadSoundMem("Data/Music/DirSelect.mp3");

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

void Player5::Update(void)
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

	auto pad = ins.GetJPadInputState(padNo_);
	// 左のスティックの情報を取得する
	auto isTrgLStick = ins.IsPadStickTrgDown((InputManager::JOYPAD_NO)padNo_, InputManager::JOYPAD_BTN::DOWN);
	// スティックの角度を取得する
	float rad = atan2f(pad.AKeyLY, pad.AKeyLX);
	float deg = rad * 180.0f / DX_PI_F;

	// 入力しないと行けない数を超えるまで入力する
	if (!gameScene_->GetRevival())
	{
		if (isAlive_)
		{
			int i = 0;
			if (!inputAlive_)
			{
				int i = 0;
				if (pushCnt_ < pushMax_)
				{
					int i = 0;
					if (gameScene_->GetImageTime() <= 0)
					{
						int i = 0;
						if (!gameScene_->GetIsAnswer())
						{
							int i = 0;
							// スティックを倒すと数字が格納される
							if (isTrgLStick)
							{
								// 上方向
								if (deg >= -105.0f && deg <= -75.0f)
								{
									direction_[pushCnt_] = (int)DIR::UP;
									pushCnt_++;
									PlaySoundMem(inputSE_, DX_PLAYTYPE_BACK, true);
								}
								// 右方向
								if (deg >= -15.0f && deg <= 15.0f)
								{
									direction_[pushCnt_] = (int)DIR::RIGHT;
									pushCnt_++;
									PlaySoundMem(inputSE_, DX_PLAYTYPE_BACK, true);
								}
								// 下方向
								if (deg >= 45.0f && deg <= 105.0f)
								{
									direction_[pushCnt_] = (int)DIR::DOWN;
									pushCnt_++;
									PlaySoundMem(inputSE_, DX_PLAYTYPE_BACK, true);
								}
								// 左方向
								if (deg >= 165.0f && deg <= 180.0f || deg <= -165.0f && deg >= -180.0f)
								{
									direction_[pushCnt_] = (int)DIR::LEFT;
									pushCnt_++;
									PlaySoundMem(inputSE_, DX_PLAYTYPE_BACK, true);
								}
							}
						}
					}
				}
			}
		}
	}

	// 死んでいたらpushCntをMaxにしてあげる
	if (!isAlive_)
	{
		pushCnt_ = pushMax_;
	}

	// 入力しないといけない数と入力した数が一緒以上であったらif文に入る
	if (pushMax_ == pushCnt_)
	{
		inputAlive_ = true;
		damage_ = false;
	}

	// ランダムで決めた方向と入力した方向があっているか
	if (gameScene_->GetInputEnd())
	{
		int i = 0;
		//if (arrowCnt_ == pushMax_)
		//{
		if (gameScene_->GetIsAnswer())
		{
			for (int i = 0; i < pushMax_; i++)
			{
				//if (player->GetPushMax() - 1 < i) break;
				auto dir = gameScene_->GetDir();
				// 要素数が同じでないと比較しない
				if (pushMax_ == dir.size())
				{
					// ランダムで決めた方向と入力した数を比較する
					if (direction_[i] != dir[i])
					{
						// 入力した方向が間違っていたらダメージを受ける
						hp_ -= 1;
					}
				}
			}
			damage_ = true;
		}

		//}
	}

	// HPがゼロになると死亡判定
	if (hp_ <= 0)
	{
		isAlive_ = false;
	}

	// みんなの入力が終わったら要素数を足す
	if (gameScene_->GetInputEnd())
	{
		gameScene_->SetPushBack(true);
	}

	// 全員の入力が終わったらtrueになる
	if (gameScene_->GetInputEnd())
	{
		//if (arrowCnt_ == pushMax_)
		//{
			if (gameScene_->GetIsAnswer())
			{
				inputAlive_ = false;
				for (int i = 0; i < pushMax_; i++)
				{
					direction_[i] = 0;
				}
				// 入力した数を初期化する
				pushCnt_ = 0;
				if (pushMax_ < 12)
				{
					// 入力しないといけない数を増やす
					pushMax_++;
					direction_.emplace_back();
				}
			}
		//}
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

void Player5::Draw(void)
{

	if (!isAlive_)
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

	if (!gameScene_->GetIsAnswer())
	{
		if (!inputAlive_)
		{
			for (int i = 0; i < pushMax_; i++)
			{
				DrawRotaGraph(pos_.x - 60 + (i % 6) * 25, pos_.y - 50 + (15 * ((i / 6) * 2)), 1.0f, 0.0f, notInputImage_, true);
			}

			for (int i = 0; i < pushCnt_; i++)
			{
				DrawRotaGraph(pos_.x - 60 + (i % 6) * 25, pos_.y - 50 + (15 * ((i / 6) * 2)), 1.0f, 0.0f, inputImage_, true);
			}
		}
	}
	//DrawRotaGraph(pos_.x + (i % 6) * 25 - 50, pos_.y + 100 * ((i / 6) * 2) - 50, 1.0f, AsoUtility::Deg2RadF(270.0f), arrowImage_, true);
	//DrawRotaGraph(125 * (i % 6) + 180, 100 * ((i / 6) * 2) + 100, 1.0f, AsoUtility::Deg2RadF(90.0f), arrowImage_, true);

	//DrawFormatString(0, (int)padNo_ * 20, 0xffffff, "HP:%d", hp_);

	if (gameScene_->GetInputEnd())
	{
		int i = 0;
		if (gameScene_->GetAnswerTime() >= 0)
		{
			int i = 0;
			for (int i = 0; i < pushMax_; i++)
			{
				if (direction_[i] == 1)
				{
					DrawRotaGraph(pos_.x - 60 + (i % 6) * 25, pos_.y - 50 + (15 * ((i / 6) * 2)), 1.0f, AsoUtility::Deg2RadF(90.0f), arrowImage_, true);
				}
				if (direction_[i] == 2)
				{
					DrawRotaGraph(pos_.x - 60 + (i % 6) * 25, pos_.y - 50 + (15 * ((i / 6) * 2)), 1.0f, AsoUtility::Deg2RadF(180.0f), arrowImage_, true);
				}
				if (direction_[i] == 3)
				{
					DrawRotaGraph(pos_.x - 60 + (i % 6) * 25, pos_.y - 50 + (15 * ((i / 6) * 2)), 1.0f, AsoUtility::Deg2RadF(270.0f), arrowImage_, true);
				}
				if (direction_[i] == 4)
				{
					DrawRotaGraph(pos_.x - 60 + (i % 6) * 25, pos_.y - 50 + (15 * ((i / 6) * 2)), 1.0f, 0.0f, arrowImage_, true);
				}
				auto dir = gameScene_->GetDir();
				// 要素数が同じでないと比較しない
				if (pushMax_ == dir.size())
				{
					// ランダムで決めた方向と入力した数を比較する
					if (direction_[i] != dir[i])
					{
						DrawRotaGraph(pos_.x - 60 + (i % 6) * 25, pos_.y - 50 + (15 * ((i / 6) * 2)), 0.1f, 0.0f, batuImage_, true);
					}
					if (direction_[i] == dir[i])
					{
						DrawRotaGraph(pos_.x - 60 + (i % 6) * 25, pos_.y - 50 + (15 * ((i / 6) * 2)), 0.1f, 0.0f, maruImage_, true);
					}
				}
			}
		}
	}
	// HPバー
	int hpLength = 100;
	int H;
	int hpGauge;
	H = hp_ * (512.0f / hpMax_) - 100;
	int R = min(max((384 - H), 0), 0xff);
	int G = min(max((H + 64), 0), 0xff);
	int B = max((H - 384), 0);
	hpGauge = hpLength * hp_ / hpMax_;

	if (hp_ >= 0)
	{
		DrawBox(pos_.x - 50, 615, pos_.x  - 50 + hpGauge, 640, GetColor(R, G, B), true);
	}

	// デバッグ描画
	//DrawDebug();

}

void Player5::Release(void)
{
	DeleteGraph(playerImg_[static_cast<int>(AsoUtility::DIR::MAX) - 1][PLAYER_MAX_NUM_ANIM]);
}

Vector2 Player5::GetPos(void)
{
    return pos_;
}

void Player5::SetPos(Vector2 pos)
{
	pos_ = pos;
}

bool Player5::IsAlive(void)
{
    return isAlive_;
}

void Player5::SetAlive(bool alive)
{
	isAlive_ = alive;
}

bool Player5::OldAlive(void)
{
	return oldAlive_;
}

std::vector<int> Player5::GetDir(void)
{
	return direction_;
}

int Player5::GetPushMax(void)
{
	return pushMax_;
}

int Player5::GetHP(void)
{
	return hp_;
}

void Player5::SetHP(int hp)
{
	hp_ = hp;
}

bool Player5::GetinputAlive(void)
{
	return inputAlive_;
}

int Player5::GetArrowCnt(void)
{
	return arrowCnt_;
}

void Player5::SetArrowCnt(int cnt)
{
	arrowCnt_ = cnt;
}

bool Player5::GetDamage(void)
{
	return damage_;
}

bool Player5::GetInputStart(void)
{
	return inputStart_;
}

bool Player5::GetInputPlayer(void)
{
	return inputPlayer_;
}

int Player5::GetRandNumber(void)
{
	return randNumber_;
}

void Player5::SetRandNumber(int rand)
{
	randNumber_ = rand;
}

bool Player5::GetInputRevival(void)
{
	return inputRevival_;
}

void Player5::DrawDebug(void)
{

	// 配列の中身を確認する
	std::string arrayString;
	for (int i = 0; i < sizeof(direction_) / sizeof(direction_[0]); i++) {
		if (pushMax_ - 1 < i) break;
		arrayString += std::to_string(direction_[i]) + " ";
	}
	DrawString(0, (int)padNo_ * 20, arrayString.c_str(), GetColor(255, 255, 255));

}
