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
		// �v���C���[�摜�̓ǂݍ���
		LoadDivGraph("Data/Image/Player/1P_1.png",
			allNum,
			NUM_X, dirNum,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImg_[0][0]);
		// �v���C���[�̎��S�摜�̓ǂݍ���
		playerDeathImage = LoadGraph("Data/Image/Player/1P_1Death.png");
		break;
	case InputManager::JOYPAD_NO::PAD2:
		// �v���C���[�摜�̓ǂݍ���
		LoadDivGraph("Data/Image/Player/2P_1.png",
			allNum,
			NUM_X, dirNum,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImg_[0][0]);
		// �v���C���[�̎��S�摜�̓ǂݍ���
		playerDeathImage = LoadGraph("Data/Image/Player/2P_1Death.png");
		break;
	case InputManager::JOYPAD_NO::PAD3:
		// �v���C���[�摜�̓ǂݍ���
		LoadDivGraph("Data/Image/Player/3P_1.png",
			allNum,
			NUM_X, dirNum,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImg_[0][0]);
		// �v���C���[�̎��S�摜�̓ǂݍ���
		playerDeathImage = LoadGraph("Data/Image/Player/3P_1Death.png");
		break;
	case InputManager::JOYPAD_NO::PAD4:
		// �v���C���[�摜�̓ǂݍ���
		LoadDivGraph("Data/Image/Player/4P_1.png",
			allNum,
			NUM_X, dirNum,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImg_[0][0]);
		// �v���C���[�̎��S�摜�̓ǂݍ���
		playerDeathImage = LoadGraph("Data/Image/Player/4P_1Death.png");
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
	dir_ = AsoUtility::DIR::DOWN;

	// �ړ����x
	speed_ = 5.0f;

	// �����̔���
	isAlive_ = true;

	// �_�ł̔���
	isBlink_ = false;

	// �{�^���̉�������
	button_ = false;

	// �̗�
	hpMax_ = 10;
	hp_ = hpMax_;

	// �U���̉�
	shotSE_ = LoadSoundMem("Data/Music/shot.mp3");

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

					// �ړ��O���W���m��
					Vector2 prePos = pos_;

					// �ړ��\��̍��W���m��
					Vector2 movedPos = pos_;

					// �����Փ˔���
					Vector2 footPos;

					// �����E�Փ˔���
					Vector2 rightFootPos;

					// �����E�Փ˔���
					Vector2 leftFootPos;

					// �ړ�����(Y)
					if (pad.AKeyLY < 0.0f)
					{
						// ��ړ�
						movedPos.y -= speed_;

						// �����̕ύX
						dir_ = AsoUtility::DIR::UP;

						// �A�j���[�V�����J�E���^�̐i�s
						cntAnim_++;
					}

					if (pad.AKeyLY > 0.0f)
					{
						// ���ړ�
						movedPos.y += speed_;

						// �����̕ύX
						dir_ = AsoUtility::DIR::DOWN;

						// �A�j���[�V�����J�E���^�̐i�s
						cntAnim_++;
					}

					// �ړ�����(X)
					if (pad.AKeyLX < 0.0f)
					{
						// ���ړ�
						movedPos.x -= speed_;

						// �����̕ύX
						dir_ = AsoUtility::DIR::LEFT;

						// �A�j���[�V�����J�E���^�̐i�s
						cntAnim_++;
					}

					if (pad.AKeyLX > 0.0f)
					{
						// �E�ړ�
						movedPos.x += speed_;

						// �����̕ύX
						dir_ = AsoUtility::DIR::RIGHT;

						// �A�j���[�V�����J�E���^�̐i�s
						cntAnim_++;
					}

					// �Փ˔���
					footPos = movedPos;
					footPos.y += 10;

					leftFootPos = movedPos;
					leftFootPos.x -= 10;
					leftFootPos.y += 10;

					rightFootPos = movedPos;
					rightFootPos.x += 10;
					rightFootPos.y += 10;

					// �X�e�[�W�̏Փ˔���
					if (gameScene_->IsCollisionStage(movedPos) == true
						|| gameScene_->IsCollisionStage(footPos) == true
						|| gameScene_->IsCollisionStage(rightFootPos) == true
						|| gameScene_->IsCollisionStage(leftFootPos) == true)
					{
						// �Փ˂��Ă��� -> ���W�����ɖ߂�
						movedPos = pos_;
					}
					else
					{
						// �ړ��\�Ɣ��f�ł����̂ŁA�����W���X�V
						pos_ = movedPos;
					}

					// �U��
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

	// �v���C���[�摜�̕`��
	// �A�j���[�V�����̃`�b�v�ԍ�(0�`3)�����
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

	// �ړ��\��̍��W���m��
	Vector2 movedPos = pos_;

	// �f�o�b�O�p
	DrawBox(pos_.x - 3,
		pos_.y - 3,
		pos_.x + 3,
		pos_.y + 3,
		0xff0000, true);

	// �I�����W
	int color = 0xff8c00;

	// �f�o�b�O�p�F�����Փ˔���
	Vector2 footPos = movedPos;
	footPos.y += 10;

	// �f�o�b�O�p�F�������Փ˔���
	Vector2 leftFootPos = movedPos;
	leftFootPos.x -= 10;
	leftFootPos.y += 10;

	// �f�o�b�O�p�F�����E�Փ˔���
	Vector2 rightFootPos = movedPos;
	rightFootPos.x += 10;
	rightFootPos.y += 10;

	// �����F����
	DrawBox(footPos.x - 3, footPos.y - 3, 
		footPos.x + 3, footPos.y + 3, color, true);

	// �����F��
	DrawBox(leftFootPos.x - 3, leftFootPos.y - 3,
		leftFootPos.x + 3, leftFootPos.y + 3, color, true);

	// �����F�E
	DrawBox(rightFootPos.x - 3, rightFootPos.y - 3,
		rightFootPos.x + 3, rightFootPos.y + 3, color, true);

}

void Player2::Attack(void)
{

	auto& ins = InputManager::GetInstance();
	auto pad = ins.GetJPadInputState(padNo_);

	// �U���L�[�������ƁA�e�𐶐�����
	if (InputManager::GetInstance().IsPadBtnTrgDown(padNo_, InputManager::JOYPAD_BTN::RIGHT) && stepShotDelay_ <= 0.0f)
	{
		// �U���̉�
		PlaySoundMem(shotSE_,DX_PLAYTYPE_BACK,true);

		// �L���ȋ����擾����
		Shot* shot = GetValidShot();

		// ���W�����炷
		Vector2 pos = pos_;

		// �e�𐶐�(�e���˂̏���)
		Vector2F dir = AsoUtility::Normalize(dir_);

		shot->CreateShot(pos.ToVector2F(), dir);

		// �e�̔��ˌ�̍d�����ԃZ�b�g
		stepShotDelay_ = SHOT_DELAY;

	}

	if (stepShotDelay_ > 0.0f)
	{

		// �e���ˌ�̍d�����Ԃ����炵�Ă���
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
