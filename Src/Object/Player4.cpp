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
		// �v���C���[�摜�̓ǂݍ���
		LoadDivGraph("Data/Image/Player/1P.png",
			allNum,
			NUM_X, dirNum,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImg_[0][0]);
		playerUIImage_ = LoadGraph("Data/Image/UI/1P.png");
		break;
	case InputManager::JOYPAD_NO::PAD2:
		// �v���C���[�摜�̓ǂݍ���
		LoadDivGraph("Data/Image/Player/2P.png",
			allNum,
			NUM_X, dirNum,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImg_[0][0]);
		playerUIImage_ = LoadGraph("Data/Image/UI/2P.png");
		break;
	case InputManager::JOYPAD_NO::PAD3:
		// �v���C���[�摜�̓ǂݍ���
		LoadDivGraph("Data/Image/Player/3P.png",
			allNum,
			NUM_X, dirNum,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImg_[0][0]);
		playerUIImage_ = LoadGraph("Data/Image/UI/3P.png");
		break;
	case InputManager::JOYPAD_NO::PAD4:
		// �v���C���[�摜�̓ǂݍ���
		LoadDivGraph("Data/Image/Player/4P.png",
			allNum,
			NUM_X, dirNum,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImg_[0][0]);
		playerUIImage_ = LoadGraph("Data/Image/UI/4P.png");
		break;
	}

	// �n�[�g�摜�̓ǂݍ���
	heartImage_ = LoadGraph("Data/Image/UI/Heart.png");

	// �Q�[���V�[���̋@�\���g����悤�ɂ���
	gameScene_ = scene;

	// �Q�[���p�b�h�̔ԍ�
	padNo_ = playerNo;

	// ����
	dir_ = AsoUtility::DIR::DOWN;

	// �ړ����x
	speed_ = 5.0f;

	// �����t���O
	isAlive_ = true;

	// �P�O�̐����t���O
	oldAlive_ = true;

	// HP
	hp_ = 2;

	// HP��1���炷���߂̃t���O
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
			}

			if (pad.AKeyLY > 0.0f)
			{
				// ���ړ�
				movedPos.y += speed_;

				// �����̕ύX
				dir_ = AsoUtility::DIR::DOWN;
			}

			// �ړ�����(X)
			if (pad.AKeyLX < 0.0f)
			{
				// ���ړ�
				movedPos.x -= speed_;

				// �����̕ύX
				dir_ = AsoUtility::DIR::LEFT;
			}

			if (pad.AKeyLX > 0.0f)
			{
				// �E�ړ�
				movedPos.x += speed_;

				// �����̕ύX
				dir_ = AsoUtility::DIR::RIGHT;
			}

			// �Փ˔���
			footPos = movedPos;
			footPos.y += 50;

			leftFootPos = movedPos;
			leftFootPos.x -= 25;
			leftFootPos.y += 50;

			rightFootPos = movedPos;
			rightFootPos.x += 25;
			rightFootPos.y += 50;

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

			// ���E�̔��������
			if (pos_.x <= Application::SCREEN_SIZE_X / 2)
			{
				// ��
				left_ = true;
				right_ = false;
			}
			else if (pos_.x >= Application::SCREEN_SIZE_X / 2)
			{
				// �E
				left_ = false;
				right_ = true;
			}

			// �E���������Ă��Ȃ�������HP�����炷
			// ��
			if (left_ && gameScene_->GetL() && subtract_)
			{
				hp_ -= 1;
				subtract_ = false;
			}

			if (right_ && gameScene_->GetL() && subtract_)
			{
				subtract_ = false;
			}
			// �E
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

	// HP��0�ɂȂ����珈���𒆎~����
	if (hp_ <= 0)
	{
		return;
	}
	// �v���C���[�摜�̕`��
	// �A�j���[�V�����̃`�b�v�ԍ�(0�`3)�����
	animData_[0] = 0;
	animData_[1] = 1;
	animData_[2] = 2;
	animData_[3] = 1;
	DrawRotaGraph(pos_.x, pos_.y, 1.0f, 0.0f, playerImg_[static_cast<int>(dir_)][animData_[(cntAnim_ / 10) % 4]], true);
	cntAnim_++;


	// �n�[�g�摜�̕`��
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
	footPos.y += 50;

	// �f�o�b�O�p�F�������Փ˔���
	Vector2 leftFootPos = movedPos;
	leftFootPos.x -= 25;
	leftFootPos.y += 50;

	// �f�o�b�O�p�F�����E�Փ˔���
	Vector2 rightFootPos = movedPos;
	rightFootPos.x += 25;
	rightFootPos.y += 50;

	// �����F����
	DrawBox(footPos.x - 3, footPos.y - 3,
		footPos.x + 3, footPos.y + 3, color, true);

	// �����F��
	DrawBox(leftFootPos.x - 3, leftFootPos.y - 3,
		leftFootPos.x + 3, leftFootPos.y + 3, color, true);

	// �����F�E
	DrawBox(rightFootPos.x - 3, rightFootPos.y - 3,
		rightFootPos.x + 3, rightFootPos.y + 3, color, true);

	if (right_)
	{
		DrawFormatString(0, (int)padNo_ * 20, 0xffffff, "�E");
	}
	if (left_)
	{
		DrawFormatString(0, (int)padNo_ * 20, 0xffffff, "��");
	}

}


