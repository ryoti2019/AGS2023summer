#include <DxLib.h>
#include "../Manager/InputManager.h"
#include "../Utility/Application.h"
#include "Meteor.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player(void)
{
}

void Player::Init(GameScene* scene, InputManager::JOYPAD_NO playerNo)
{

	switch (playerNo)
	{
	case InputManager::JOYPAD_NO::PAD1:
		// �v���C���[�摜�̓ǂݍ���
		LoadDivGraph("Data/Image/Player/1P.png",
			PLAYER_MAX_NUM_ANIM,
			NUM_X, NUM_Y,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImage_[0][0]);
		// �v���C���[�̎��S�摜�̓ǂݍ���
		playerDeathImage = LoadGraph("Data/Image/Player/1PDeath.png");
		// �v���C���[��UI�摜�̓ǂݍ���
		playerUIImage_ = LoadGraph("Data/Image/UI/1P.png");
		break;
	case InputManager::JOYPAD_NO::PAD2:
		// �v���C���[�摜�̓ǂݍ���
		LoadDivGraph("Data/Image/Player/2P.png",
			PLAYER_MAX_NUM_ANIM,
			NUM_X, NUM_Y,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImage_[0][0]);
		// �v���C���[�̎��S�摜
		playerDeathImage = LoadGraph("Data/Image/Player/2PDeath.png");
		// �v���C���[��UI�摜�̓ǂݍ���
		playerUIImage_ = LoadGraph("Data/Image/UI/2P.png");
		break;
	case InputManager::JOYPAD_NO::PAD3:
		// �v���C���[�摜�̓ǂݍ���
		LoadDivGraph("Data/Image/Player/3P.png",
			PLAYER_MAX_NUM_ANIM,
			NUM_X, NUM_Y,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImage_[0][0]);
		// �v���C���[�̎��S�摜
		playerDeathImage = LoadGraph("Data/Image/Player/3PDeath.png");
		// �v���C���[��UI�摜�̓ǂݍ���
		playerUIImage_ = LoadGraph("Data/Image/UI/3P.png");
		break;
	case InputManager::JOYPAD_NO::PAD4:
		// �v���C���[�摜�̓ǂݍ���
		LoadDivGraph("Data/Image/Player/4P.png",
			PLAYER_MAX_NUM_ANIM,
			NUM_X, NUM_Y,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImage_[0][0]);
		// �v���C���[�̎��S�摜
		playerDeathImage = LoadGraph("Data/Image/Player/4PDeath.png");
		// �v���C���[��UI�摜�̓ǂݍ���
		playerUIImage_ = LoadGraph("Data/Image/UI/4P.png");
		break;
	}

	// �o���A�摜�̓ǂݍ���
	barrierImage_ = LoadGraph("Data/Image/Player/barrier.png");

	// �Q�[���V�[���̋@�\���g����悤�ɂ���
	gameScene_ = scene;

	// �Q�[���p�b�h�̔ԍ�
	padNo_ = playerNo;

	// ���W
	pos_ = { 0,0 };

	// ����
	dir_ = AsoUtility::DIR::DOWN;

	// �����̔���
	isAlive_ = true;

	// �P�O�̐����t���O
	oldAlive_ = true;

	// �_�ł̔���
	isBlink_ = false;

	// �{�^���̉�������
	button_ = false;

	// �̗�
	hpMax_ = 100;
	hp_ = hpMax_;

	// �A�j���[�V�����X�s�[�h
	speedAnim_ = 1.0f;

	// �o���A�̓W�J���̓ǂݍ���
	barrierSE_ = LoadSoundMem("Data/Music/barrier.mp3");

	// ����{�^����SE�̓ǂݍ���
	decideSE_ = LoadSoundMem("Data/Music/decideGame.mp3");

	// �v���C���[��OK�{�^�����������Ƃ��̉��̓ǂݍ���
	playerDecideSE_ = LoadSoundMem("Data/Music/PlayerDecide.mp3");

	// ���񂾂Ƃ��̉�
	deathSE_ = LoadSoundMem("Data/Music/K.O..mp3");

	death_ = false;

	inputStart_ = false;

	inputPlayer_ = false;

	randNumber_ = 0;
}

void Player::Update(void)
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

				// �E�{�^���������ƃK�[�h����
				button_ = ins.IsPadBtnNew(padNo_, InputManager::JOYPAD_BTN::RIGHT);
				if (!gameScene_->GetResult())
				{
					if (button_ && isAlive_)
					{
						hp_ -= 0.5f;
						PlaySoundMem(barrierSE_, DX_PLAYTYPE_BACK, true);
					}
				}

				if (!isAlive_)
				{
					pos_.y -= 5;
				}

				if (!isAlive_ && !death_)
				{
					PlaySoundMem(deathSE_, DX_PLAYTYPE_BACK, true);
					death_ = true;
				}


			}
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

	if (gameScene_->GetRevival())
	{
		if (ins.IsPadBtnTrgDown(padNo_, InputManager::JOYPAD_BTN::RIGHT) && !inputRevival_)
		{
			inputRevival_ = true;
		}
	}
}

void Player::Draw(void)
{

	if (!isAlive_)
	{
		DrawGraph(pos_.x, pos_.y, playerDeathImage, true);
	}

	// �v���C���[�摜�̕`��
	// �A�j���[�V�����̃`�b�v�ԍ�(0�`3)�����
	animData_[0] = 0;
	animData_[1] = 1;
	animData_[2] = 2;
	animData_[3] = 1;
	if (isAlive_)
	{
		// �v���C���[�摜�̕`��
		DrawGraph(pos_.x, pos_.y, playerImage_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
	}
	cntAnim_++;

	if (!gameScene_->GetResult())
	{
		if (button_ && isAlive_)
		{
			// �o���A�摜�̕`��
			DrawGraph(pos_.x, pos_.y, barrierImage_, true);
		}
	}

	// �v���C���[��UI�摜�̕`��
	DrawBox(pos_.x + 85, 585, pos_.x + 115, 615, 0x000000, true);
	DrawRotaGraph(pos_.x + 100, 600, 0.5f, 0.0f, playerUIImage_, true);

	// HP�o�[
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
		DrawBox(pos_.x, 615, pos_.x + hpGauge, 640, GetColor(R, G, B), true);
	}

	//DrawGraph(pos_.x + 25, 565, playerUI_, true);
	SetFontSize(25);
	DrawString(pos_.x - 30, 615, "HP", 0x00ff00);

}

void Player::Release(void)
{
	DeleteGraph(playerImage_[static_cast<int>(AsoUtility::DIR::MAX) - 1][PLAYER_MAX_NUM_ANIM]);
	DeleteGraph(playerDeathImage);
	DeleteGraph(barrierImage_);
}

int Player::GetHP(void)
{
	return hp_;
}

void Player::SetHP(int hp)
{
	hp_ -= hp;
}

int Player::GetRandNumber(void)
{
	return randNumber_;
}

void Player::SetRandNumber(int rand)
{
	randNumber_ = rand;
}

bool Player::GetInputRevival(void)
{
	return inputRevival_;
}

void Player::SetPos(Vector2 pos)
{
	pos_ = pos;
}

Vector2 Player::GetPos(void)
{
	//Vector2 pos = pos_;
	return pos_;
}

bool Player::IsAlive(void)
{
	return isAlive_;
}

void Player::SetAlive(bool alive)
{
	isAlive_ = alive;
}

bool Player::OldAlive(void)
{
	return oldAlive_;
}

bool Player::GetButton(void)
{
	return button_;
}

bool Player::GetInputStart(void)
{
	return inputStart_;
}

bool Player::GetInputPlayer(void)
{
	return inputPlayer_;
}

void Player::DrawDebug(void)
{

	// �f�o�b�O�p
	DrawBox(pos_.x - 3,
		pos_.y - 3,
		pos_.x + 3,
		pos_.y + 3,
		0xff0000, true);

	Vector2 headPos = pos_;
	headPos.x += PLAYER_SIZE_X / 2;

	// �I�����W
	int color = 0xff8c00;

	// �����F����
	DrawBox(headPos.x - 3, headPos.y - 3,
		headPos.x + 3, headPos.y + 3, 0xff0000, true);

	DrawLine(0, 500, Application::SCREEN_SIZE_X, 500, 0xff0000, true);

}
