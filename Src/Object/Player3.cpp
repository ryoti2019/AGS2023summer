#include <DxLib.h>
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Utility/Application.h"
#include "../Common/Vector2.h"
#include "../Object/shot2.h"
#include "Player3.h"

Player3::Player3()
{

}

Player3::~Player3(void)
{
}

void Player3::Init(GameScene3* scene, InputManager::JOYPAD_NO playerNo)
{

	int dirNum = static_cast<int>(AsoUtility::DIR::MAX);
	int allNum = PLAYER_MAX_NUM_ANIM * dirNum;
	switch (playerNo)
	{
	case InputManager::JOYPAD_NO::PAD1:
		// �v���C���[�摜�̓ǂݍ���
		LoadDivGraph("Data/Image/Player/1P_1.png",
			allNum,
			NUM_X, dirNum,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImg_[0][0]);
		break;
	case InputManager::JOYPAD_NO::PAD2:
		// �v���C���[�摜�̓ǂݍ���
		LoadDivGraph("Data/Image/Player/2P_1.png",
			allNum,
			NUM_X, dirNum,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImg_[0][0]);
		break;
	case InputManager::JOYPAD_NO::PAD3:
		// �v���C���[�摜�̓ǂݍ���
		LoadDivGraph("Data/Image/Player/3P_1.png",
			allNum,
			NUM_X, dirNum,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImg_[0][0]);
		break;
	case InputManager::JOYPAD_NO::PAD4:
		// �v���C���[�摜�̓ǂݍ���
		LoadDivGraph("Data/Image/Player/4P_1.png",
			allNum,
			NUM_X, dirNum,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImg_[0][0]);
		break;
	}

	// �e�摜�̏�����
	LoadDivGraph("Data/Image/Player/shot.png",
		SHOT_MAX_NUM_ANIM,
		SHOT_NUM_X, SHOT_NUM_Y,
		SHOT_SIZE_X, SHOT_SIZE_Y,
		&shotImgs_[0]);

	// �Q�[���V�[���̋@�\���g����悤�ɂ���
	gameScene_ = scene;

	// �Q�[���p�b�h�̔ԍ�
	padNo_ = playerNo;

	// ����
	dir_ = AsoUtility::DIR::UP;

	// �U���̉�
	shotSE_ = LoadSoundMem("Data/Music/shot2.mp3");

	// ����{�^����SE�̓ǂݍ���
	decideSE_ = LoadSoundMem("Data/Music/decideGame.mp3");

	// �v���C���[��OK�{�^�����������Ƃ��̉��̓ǂݍ���
	playerDecideSE_ = LoadSoundMem("Data/Music/PlayerDecide.mp3");

	death_ = false;

	inputStart_ = false;

	inputPlayer_ = false;
}

void Player3::Update(void)
{
	auto& ins = InputManager::GetInstance();
	if (ins.IsPadBtnTrgDown(padNo_, InputManager::JOYPAD_BTN::RIGHT) && !inputStart_)
	{
		inputStart_ = true;
		gameScene_->SetStartNum(1);
		PlaySoundMem(decideSE_, DX_PLAYTYPE_BACK, true);
	}

	if (gameScene_->GetSkip())
	{
		if (gameScene_->IsStart())
		{
			if (!gameScene_->GetResult())
			{
				// �U��
				Attack();
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

}

void Player3::Draw(void)
{

	// �v���C���[�摜�̕`��
	// �A�j���[�V�����̃`�b�v�ԍ�(0�`3)�����
	animData_[0] = 0;
	animData_[1] = 1;
	animData_[2] = 2;
	animData_[3] = 1;
	DrawRotaGraph(pos_.x, pos_.y, 1.0f, 0.0f, playerImg_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
	cntAnim_++;

}

void Player3::Release(void)
{
	DeleteGraph(playerImg_[static_cast<int>(AsoUtility::DIR::MAX) - 1][PLAYER_MAX_NUM_ANIM]);
}

Vector2 Player3::GetPos(void)
{
	return pos_;
}

void Player3::SetPos(Vector2 pos)
{
	pos_ = pos;
}

std::vector<Shot2*> Player3::GetShots(void)
{
	return shots_;
}

bool Player3::GetInputStart(void)
{
	return inputStart_;
}

bool Player3::GetInputPlayer(void)
{
	return inputPlayer_;
}

void Player3::Attack(void)
{

	auto& ins = InputManager::GetInstance();
	auto pad = ins.GetJPadInputState(padNo_);

	// �U���L�[�������ƁA�e�𐶐�����
	if (InputManager::GetInstance().IsPadBtnTrgDown(padNo_, InputManager::JOYPAD_BTN::RIGHT))
	{

		// �U���̉�
		PlaySoundMem(shotSE_, DX_PLAYTYPE_BACK, true);

		// �L���ȋ����擾����
		Shot2* shot = GetValidShot();

		// ���W�����炷
		Vector2 pos = pos_;

		// �e�𐶐�(�e���˂̏���)
		Vector2F dir = AsoUtility::Normalize(dir_);
		shot->CreateShot(pos.ToVector2F(), dir);

	}

}

Shot2* Player3::GetValidShot(void)
{

	size_t size = shots_.size();
	for (int i = 0; i < size; i++)
	{
		if (!shots_[i]->IsAlive())
		{
			return shots_[i];
		}
	}

	Shot2* shot = new Shot2(shotImgs_, SHOT_MAX_NUM_ANIM);
	shots_.push_back(shot);

	return shot;

}
