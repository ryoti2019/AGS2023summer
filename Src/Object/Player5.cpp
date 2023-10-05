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
		// �v���C���[�摜�̓ǂݍ���
		LoadDivGraph("Data/Image/Player/1P.png",
			allNum,
			NUM_X, dirNum,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImg_[0][0]);
		break;
	case InputManager::JOYPAD_NO::PAD2:
		// �v���C���[�摜�̓ǂݍ���
		LoadDivGraph("Data/Image/Player/2P.png",
			allNum,
			NUM_X, dirNum,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImg_[0][0]);
		break;
	case InputManager::JOYPAD_NO::PAD3:
		// �v���C���[�摜�̓ǂݍ���
		LoadDivGraph("Data/Image/Player/3P.png",
			allNum,
			NUM_X, dirNum,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImg_[0][0]);
		break;
	case InputManager::JOYPAD_NO::PAD4:
		// �v���C���[�摜�̓ǂݍ���
		LoadDivGraph("Data/Image/Player/4P.png",
			allNum,
			NUM_X, dirNum,
			PLAYER_SIZE_X, PLAYER_SIZE_Y,
			&playerImg_[0][0]);
		break;
	}

	// ���͂����Ƃ��̉摜�̓ǂݍ���
	inputImage_ = LoadGraph("Data/Image/UI/Green.png");

	// �܂����͂���Ă��Ȃ��Ƃ��̉摜�̓ǂݍ���
	notInputImage_ = LoadGraph("Data/Image/UI/Black.png");

	arrowImage_ = LoadGraph("Data/Image/UI/playerArrow.png");

	// �Z�摜
	maruImage_ = LoadGraph("Data/Image/UI/maru.png");

	// �~�摜
	batuImage_ = LoadGraph("Data/Image/UI/batu.png");

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

	// �̗�
	hpMax_ = 5;
	hp_ = hpMax_;

	// HP��1���炷���߂̃t���O
	subtract_ = true;

	// ���͂�����
	pushCnt_ = 0;

	// ���͂��Ȃ��Ƃ����Ȃ���
	pushMax_ = 5;

	// ���͂������̂��i�[����z��
	direction_ = std::vector<int>(pushMax_);

	inputAlive_ = false;

	// ��󂪍ő�l���`�悳���邽�߂̃J�E���^
	arrowCnt_ = 0;

	// �_���[�W��H�������
	damage_ = false;

	// ���͂����Ƃ��̉�
	inputSE_ = LoadSoundMem("Data/Music/DirSelect.mp3");

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
	// ���̃X�e�B�b�N�̏����擾����
	auto isTrgLStick = ins.IsPadStickTrgDown((InputManager::JOYPAD_NO)padNo_, InputManager::JOYPAD_BTN::DOWN);
	// �X�e�B�b�N�̊p�x���擾����
	float rad = atan2f(pad.AKeyLY, pad.AKeyLX);
	float deg = rad * 180.0f / DX_PI_F;

	// ���͂��Ȃ��ƍs���Ȃ����𒴂���܂œ��͂���
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
							// �X�e�B�b�N��|���Ɛ������i�[�����
							if (isTrgLStick)
							{
								// �����
								if (deg >= -105.0f && deg <= -75.0f)
								{
									direction_[pushCnt_] = (int)DIR::UP;
									pushCnt_++;
									PlaySoundMem(inputSE_, DX_PLAYTYPE_BACK, true);
								}
								// �E����
								if (deg >= -15.0f && deg <= 15.0f)
								{
									direction_[pushCnt_] = (int)DIR::RIGHT;
									pushCnt_++;
									PlaySoundMem(inputSE_, DX_PLAYTYPE_BACK, true);
								}
								// ������
								if (deg >= 45.0f && deg <= 105.0f)
								{
									direction_[pushCnt_] = (int)DIR::DOWN;
									pushCnt_++;
									PlaySoundMem(inputSE_, DX_PLAYTYPE_BACK, true);
								}
								// ������
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

	// ����ł�����pushCnt��Max�ɂ��Ă�����
	if (!isAlive_)
	{
		pushCnt_ = pushMax_;
	}

	// ���͂��Ȃ��Ƃ����Ȃ����Ɠ��͂��������ꏏ�ȏ�ł�������if���ɓ���
	if (pushMax_ == pushCnt_)
	{
		inputAlive_ = true;
		damage_ = false;
	}

	// �����_���Ō��߂������Ɠ��͂��������������Ă��邩
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
				// �v�f���������łȂ��Ɣ�r���Ȃ�
				if (pushMax_ == dir.size())
				{
					// �����_���Ō��߂������Ɠ��͂��������r����
					if (direction_[i] != dir[i])
					{
						// ���͂����������Ԉ���Ă�����_���[�W���󂯂�
						hp_ -= 1;
					}
				}
			}
			damage_ = true;
		}

		//}
	}

	// HP���[���ɂȂ�Ǝ��S����
	if (hp_ <= 0)
	{
		isAlive_ = false;
	}

	// �݂�Ȃ̓��͂��I�������v�f���𑫂�
	if (gameScene_->GetInputEnd())
	{
		gameScene_->SetPushBack(true);
	}

	// �S���̓��͂��I�������true�ɂȂ�
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
				// ���͂�����������������
				pushCnt_ = 0;
				if (pushMax_ < 12)
				{
					// ���͂��Ȃ��Ƃ����Ȃ����𑝂₷
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
	// �v���C���[�摜�̕`��
	// �A�j���[�V�����̃`�b�v�ԍ�(0�`3)�����
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
				// �v�f���������łȂ��Ɣ�r���Ȃ�
				if (pushMax_ == dir.size())
				{
					// �����_���Ō��߂������Ɠ��͂��������r����
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
		DrawBox(pos_.x - 50, 615, pos_.x  - 50 + hpGauge, 640, GetColor(R, G, B), true);
	}

	// �f�o�b�O�`��
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

	// �z��̒��g���m�F����
	std::string arrayString;
	for (int i = 0; i < sizeof(direction_) / sizeof(direction_[0]); i++) {
		if (pushMax_ - 1 < i) break;
		arrayString += std::to_string(direction_[i]) + " ";
	}
	DrawString(0, (int)padNo_ * 20, arrayString.c_str(), GetColor(255, 255, 255));

}
