#include <string>
#include <DxLib.h>
#include "../Utility/Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Object/Player2.h"
#include "../Object/Stage.h"
#include "../Object/Shot.h"
#include "../Object/StrartMes.h"
#include "../Scene/ResultScene.h"
#include "GameScene2.h"

GameScene2::GameScene2(void)
{
}

GameScene2::~GameScene2(void)
{
}

void GameScene2::Init(void)
{

	// �X�e�[�W�̏�����
	stage_ = new Stage();
	stage_->Init(this);

	// �Q�[�������p�̉摜
	expImage_ = LoadGraph("Data/Image/UI/game2UI.png");

	// �{�^���̉摜�̓ǂݍ���
	LoadDivGraph("Data/Image/UI/BbottonAnim.png",
		BOTTON_MAX_NUM_ANIM,
		BOTTON_NUM_X, BOTTON_NUM_Y,
		BOTTON_SIZE_X, BOTTON_SIZE_Y,
		&BbottonImage_[0]);

	// �X�e�B�b�N�̉摜�̓ǂݍ���
	LoadDivGraph("Data/Image/UI/Lstick.png",
		STICK_MAX_NUM_ANIM,
		STICK_NUM_X, STICK_NUM_Y,
		STICK_SIZE_X, STICK_SIZE_Y,
		&LstickIMage_[0]);

	// �����摜�̓ǂݍ���
	winImage1_ = LoadGraph("Data/Image/UI/1Pwin.png");
	winImage2_ = LoadGraph("Data/Image/UI/2Pwin.png");
	winImage3_ = LoadGraph("Data/Image/UI/3Pwin.png");
	winImage4_ = LoadGraph("Data/Image/UI/4Pwin.png");

	// �v���C���[��OK�摜�̓ǂݍ���
	OKImage1_ = LoadGraph("Data/Image/UI/1POK.png");
	OKImage2_ = LoadGraph("Data/Image/UI/2POK.png");
	OKImage3_ = LoadGraph("Data/Image/UI/3POK.png");
	OKImage4_ = LoadGraph("Data/Image/UI/4POK.png");

	// �S���̃T�C�R���̉摜�̓ǂݍ���
	LoadDivGraph("Data/Image/UI/AllDice.png",
		6, 6, 1,
		100, 100,
		&allDice_[0]);

	// 1���̃T�C�R���̉摜�̓ǂݍ���
	dice1_ = LoadGraph("Data/Image/UI/Dice1.png");
	dice2_ = LoadGraph("Data/Image/UI/Dice2.png");
	dice3_ = LoadGraph("Data/Image/UI/Dice3.png");
	dice4_ = LoadGraph("Data/Image/UI/Dice4.png");
	dice5_ = LoadGraph("Data/Image/UI/Dice5.png");
	dice6_ = LoadGraph("Data/Image/UI/Dice6.png");

	// �T�C�R����U��
	saikoro_ = LoadGraph("Data/Image/UI/saikoro.png");

	// �v���C���[�̐l���I��
	int pNum = SceneManager::GetInstance().GetPlayerNum();
	int pSize = Application::SCREEN_SIZE_X / pNum;
	for (int i = 0; i < pNum; i++)
	{
		Player2* p = new Player2();
		InputManager::JOYPAD_NO jno = static_cast<InputManager::JOYPAD_NO>(i + 1);
		p->Init(this, jno);

		if (i == 0)
		{
			p->SetPos({ 32 * 5, 32 * 5 });
		}

		if (i == 1)
		{
			p->SetPos({ 32 * 26, 32 * 5 });
		}

		if (i == 2)
		{
			p->SetPos({ 32 * 5, 32 * 15 });
		}

		if (i == 3)
		{
			p->SetPos({ 32 * 26, 32 * 15 });
		}

		players_.push_back(p);
	}

	// �X�^�[�g���b�Z�[�W�̏�����
	startMes_ = new StartMes();
	startMes_->Init();

	// �����c��̓ǂݍ���
	tekiwotaose_ = LoadGraph("Data/Image/UI/tekiwotaose.png");

	// �X�^�[�g�摜�̓ǂݍ���
	startImage_ = LoadGraph("Data/Image/UI/start.png");

	// �Q�[���������X�L�b�v����t���O
	skip_ = false;

	// �A�j���[�V�����̃J�E���^
	cntAnim_ = 0;

	// BGM�̓ǂݍ���
	bgm_ = LoadSoundMem("Data/Music/game2BGM.mp3");
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP, true);

	// ���񂾂Ƃ��̉�
	deathSE_ = LoadSoundMem("Data/Music/K.O..mp3");

	// ����{�^����SE�̓ǂݍ���
	decideSE_ = LoadSoundMem("Data/Music/decideGame.mp3");

	result_ = false;

	revival_ = false;

	isRand1_ = true;
	isRand2_ = true;
	isRand3_ = true;
	isRand4_ = true;

	win_ = true;

	inputRandNum_ = 0;

	revivalHP_ = true;

}

void GameScene2::Update(void)
{

	int pNum = SceneManager::GetInstance().GetPlayerNum();
	auto& ins = InputManager::GetInstance();
	if (startNum_ == pNum || InputManager::GetInstance().IsTrgDown(KEY_INPUT_Z))
	{
		skip_ = true;
	}

	if (skip_)
	{
		// �X�^�[�g���b�Z�[�W�̍X�V
		startMes_->Update();
	}


	if (startMes_->GetCnt() >= 240)
	{
		isStart_ = true;
	}
	// �X�e�[�W�̍X�V
	stage_->Update();

	// �v���C���[������ł����珈�����Ȃ�
	for (auto player : players_)
	{
		// �v���C���[�̍X�V
		player->Update();
	}

	// �e�̍X�V
	for (auto player : players_)
	{
		auto shots = player->GetShots();
		for (auto shot : shots)	// �͈�for��
		{
			shot->Update();
		}
	}

	// �Փ˔���
	Collision();

	// �V�[���J��
	int deathNum = 0;
	for (int i = 0; i < pNum; i++)
	{
		if (!players_[i]->IsAlive())
		{
			deathNum++;
		}
	}

	// �����Ɏ���ł��܂����Ƃ�
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
					players_[0]->SetHP(-10);
					players_[0]->SetAlive(true);
				}
				if (i == 1 && players_[1]->OldAlive())
				{
					players_[1]->SetHP(-10);
					players_[1]->SetAlive(true);
				}
				if (i == 2 && players_[2]->OldAlive())
				{
					players_[2]->SetHP(-10);
					players_[2]->SetAlive(true);
				}
				if (i == 3 && players_[3]->OldAlive())
				{
					players_[3]->SetHP(-10);
					players_[3]->SetAlive(true);
				}
			}
		}
	}

	if (pNum == deathNum + 1)
	{
		Result();
		result_ = true;
	}

	if (revival_)
	{
		Rand();
	}

}

void GameScene2::Draw(void)
{

	// �X�e�[�W�̕`��
	stage_->Draw();

	// �X�^�[�g���b�Z�[�W�̕`��
	startMes_->Draw();

	// �v���C���[������ł����珈�����Ȃ�
	for (auto player : players_)
	{
		// �v���C���[�̕`��
		player->Draw();
	}

	if (!skip_)
	{
		// �Q�[�������摜�̕`��
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 230, 1.0f, 0.0f, expImage_, true);
		DrawGraph(470, 340, BbottonImage_[(cntAnim_ / 10) % 4], true);
		DrawGraph(810, 365, BbottonImage_[(cntAnim_ / 10) % 4], true);
		DrawGraph(470, 380, LstickIMage_[cntAnim_ / 5 % 8], true);
	}

	if (skip_)
	{
		if (!result_ && !revival_)
		{
			// �G��|���̕`��
			DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 100, 1.0f, 0.0f, tekiwotaose_, true);
		}
	}

	// �e�̍X�V
	for (auto player : players_)
	{
		auto shots = player->GetShots();
		for (auto shot : shots)	// �͈�for��
		{
			shot->Draw();
		}
	}
	cntAnim_++;

	// ���������l�̉摜�̕`��
	int pNum = SceneManager::GetInstance().GetPlayerNum();
	if (result_)
	{
		for (int i = 0; i < pNum; i++)
		{
			if (pNum == 2)
			{
				if (players_[0]->IsAlive())
				{
					// 1P�̏����摜
					DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 200, 1.0f, 0.0f, winImage1_, true);
				}
				if (players_[1]->IsAlive())
				{
					// 2P�̏����摜
					DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 200, 1.0f, 0.0f, winImage2_, true);
				}
			}
			if (pNum == 3)
			{
				if (players_[0]->IsAlive())
				{
					// 1P�̏����摜
					DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 200, 1.0f, 0.0f, winImage1_, true);
				}
				if (players_[1]->IsAlive())
				{
					// 2P�̏����摜
					DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 200, 1.0f, 0.0f, winImage2_, true);
				}
				if (players_[2]->IsAlive())
				{
					// 3P�̏����摜
					DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 200, 1.0f, 0.0f, winImage3_, true);
				}
			}
			if (pNum == 4)
			{
				if (players_[0]->IsAlive())
				{
					// 1P�̏����摜
					DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 200, 1.0f, 0.0f, winImage1_, true);
				}
				if (players_[1]->IsAlive())
				{
					// 2P�̏����摜
					DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 200, 1.0f, 0.0f, winImage2_, true);
				}
				if (players_[2]->IsAlive())
				{
					// 3P�̏����摜
					DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 200, 1.0f, 0.0f, winImage3_, true);
				}
				if (players_[3]->IsAlive())
				{
					// 4P�̏����摜
					DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 200, 1.0f, 0.0f, winImage4_, true);
				}
			}
		}
	}

	int pSize = Application::SCREEN_SIZE_X / pNum;
	int pSpace = 0;	// 2�l�F150�@3�l�F100�@�S�l�F75
	// �l���摜�̕`��
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

	// �X�^�[�g�摜�̕`��
	if (result_)
	{
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 550, 1.0f, 0.0f, startImage_, true);
	}

	// �T�C�R���̉摜�̕`��
	for (int i = 0; i < pNum; i++)
	{
		if (revival_)
		{
			// �T�C�R����U��̕`��
			DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 140, 1.0f, 0.0f, saikoro_, true);
			// �S���̃T�C�R���̕`��
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

				// �v���C���[�Q�̃T�C�R��
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
				// �v���C���[�P�̃T�C�R��
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

				// �v���C���[�Q�̃T�C�R��
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

				// �v���C���[�R�̃T�C�R��
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
				// �v���C���[�P�̃T�C�R��
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

				// �v���C���[�Q�̃T�C�R��
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

				// �v���C���[�R�̃T�C�R��
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

				// �v���C���[�S�̃T�C�R��
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
		// �T�C�R����U��̕`��
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 140, 1.0f, 0.0f, saikoro_, true);
	}

}

void GameScene2::Release(void)
{

	// �X�^�[�g���b�Z�[�W�̍X�V
	startMes_->Release();
	delete startMes_;

	// �X�e�[�W�̊J��
	stage_->Release();

	// �v���C���[�̊J��
	auto players = players_;
	for (auto player : players_)
	{
		player->Release();
		delete player;
	}

	// �e�̍X�V
	for (auto player : players_)
	{
		auto shots = player->GetShots();
		for (auto shot : shots)	// �͈�for��
		{
			shot->Release();
		}
	}

}

Vector2 GameScene2::World2MapPos(Vector2 worldPos)
{

	Vector2 ret;

	int  mapX = worldPos.x / Stage::CHIP_SIZE_X;
	int  mapY = worldPos.y / Stage::CHIP_SIZE_Y;

	ret.x = mapX;
	ret.y = mapY;

	return ret;

}

bool GameScene2::IsCollisionStage(Vector2 worldPos)
{

	// ���[���h���W����}�b�v���W�ɕϊ�����
	Vector2 mapPos = World2MapPos(worldPos);

	// �}�b�v���W����}�b�v�`�b�v�ԍ����擾����
	int chipNo = stage_->GetCollisionStageNo(mapPos);

	if (chipNo != -1)
	{
		return true;
	}

	return false;

}

Stage* GameScene2::GetStage(void)
{
	return stage_;
}

bool GameScene2::GetResult(void)
{
	return result_;
}

bool GameScene2::GetSkip(void)
{
	return skip_;
}

bool GameScene2::IsStart(void)
{
	return isStart_;
}

void GameScene2::SetInputNum(int input)
{
	inputNum_ += input;
}

void GameScene2::SetStartNum(int start)
{
	startNum_ += start;
}

bool GameScene2::GetRevival(void)
{
	return revival_;
}

void GameScene2::Collision(void)
{

	// �e�����擾����
	for (auto player : players_)
	{
		std::vector<Shot*> shots = player->GetShots();
		for (Shot* shot : shots)
		{

			// �e���������Ă��Ȃ���΁A�������΂�
			if (!shot->IsAlive())
			{
				continue;
			}



			// �e�ƃX�e�[�W�̏Փ˔���
			Vector2 shotPos = shot->GetPos();

			if (IsCollisionStage(shotPos))
			{
				// �����G�t�F�N�g�𔭐�������
				shot->ShotBlast();
				shot->Blast(shotPos);
			}

			for (auto enemy : players_)
			{

				// �e���������Ă��Ȃ���΁A�������΂�
				if (!enemy->IsAlive())
				{
					continue;
				}

				if (enemy != player)
				{
					if (IsCollisionRectCenter(
						enemy->GetPos(), { PLAYER_SIZE_X, PLAYER_SIZE_Y },
						shot->GetPos(), { player->SHOT_SIZE_X, player->SHOT_SIZE_Y }))
					{
						// �����G�t�F�N�g�𔭐�������
						shot->ShotBlast();
						shot->Blast(shotPos);
						enemy->SetHP(10);
					}
				}
			}
		}
	}

}

bool GameScene2::IsCollisionRect(Vector2 stPos1, Vector2 edPos1, Vector2 stPos2, Vector2 edPos2)
{

	// ��`���m�̏Փ˔���
	// ��`�P�̍������A��`�Q�̉E���傫��
	// ��`�Q�̍������A��`�P�̉E���傫��
	if (stPos1.x < edPos2.x
		&& stPos2.x < edPos1.x
		&& stPos1.y < edPos2.y
		&& stPos2.y < edPos1.y)
	{
		return true;
	}
	return false;

}

bool GameScene2::IsCollisionRectCenter(Vector2 centerPos1, Vector2 size1, Vector2 centerPos2, Vector2 size2)
{

	// ��`1(������W�A�E����W)
	Vector2 stPos1 = centerPos1;
	Vector2 edPos1 = centerPos1;
	Vector2 hSize1 = { size1.x / 2, size1.y / 2 };

	stPos1.x -= hSize1.x;
	stPos1.y -= hSize1.y;
	edPos1.x += hSize1.x;
	edPos1.y += hSize1.y;

	// ��`�Q(������W�A�E����W)
	Vector2 stPos2 = centerPos2;
	Vector2 edPos2 = centerPos2;
	Vector2 hSize2 = { size2.x / 2, size2.y / 2 };

	stPos2.x -= hSize2.x;
	stPos2.y -= hSize2.y;
	edPos2.x += hSize2.x;
	edPos2.y += hSize2.y;

	// ��`���m�̏Փ˔���
	// ��`�P�̍������A��`�Q�̉E���傫��
	// ��`�Q�̍������A��`�P�̉E���傫��
	if (IsCollisionRect(stPos1, edPos1, stPos2, edPos2))
	{
		return true;
	}
	return false;

}

void GameScene2::Result(void)
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

	// �V�[���J��
	auto& ins = InputManager::GetInstance();
	// �S�����{�^�����������玟�֐i��
	if (SceneManager::GetInstance().GetBattleMode())
	{
		if (inputNum_ == pNum || InputManager::GetInstance().IsTrgDown(KEY_INPUT_Z))
		{
			PlaySoundMem(decideSE_, DX_PLAYTYPE_BACK, false);
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME3);
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

void GameScene2::Rand(void)
{
	int pNum = SceneManager::GetInstance().GetPlayerNum();
	// �����_���ɐ��������蓖�Ă�
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
				if (players_[0]->GetRandNumber() > players_[1]->GetRandNumber())
				{
					players_[0]->SetAlive(true);
					players_[1]->SetAlive(false);
				}
				if (players_[1]->GetRandNumber() > players_[0]->GetRandNumber())
				{
					players_[1]->SetAlive(true);
					players_[0]->SetAlive(false);
				}
			}
			if (pNum == 3)
			{
				if (players_[0]->GetRandNumber() > players_[1]->GetRandNumber() &&
					players_[0]->GetRandNumber() > players_[2]->GetRandNumber())
				{
					players_[0]->SetAlive(true);
					players_[1]->SetAlive(false);
					players_[2]->SetAlive(false);
				}
				if (players_[1]->GetRandNumber() > players_[0]->GetRandNumber() &&
					players_[1]->GetRandNumber() > players_[2]->GetRandNumber())
				{
					players_[1]->SetAlive(true);
					players_[0]->SetAlive(false);
					players_[2]->SetAlive(false);
				}
				if (players_[2]->GetRandNumber() > players_[0]->GetRandNumber() &&
					players_[2]->GetRandNumber() > players_[1]->GetRandNumber())
				{
					players_[2]->SetAlive(true);
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
					players_[1]->SetAlive(false);
					players_[2]->SetAlive(false);
					players_[3]->SetAlive(false);
				}
				if (players_[1]->GetRandNumber() > players_[0]->GetRandNumber() &&
					players_[1]->GetRandNumber() > players_[2]->GetRandNumber() &&
					players_[1]->GetRandNumber() > players_[3]->GetRandNumber())
				{
					players_[1]->SetAlive(true);
					players_[0]->SetAlive(false);
					players_[2]->SetAlive(false);
					players_[3]->SetAlive(false);
				}
				if (players_[2]->GetRandNumber() > players_[0]->GetRandNumber() &&
					players_[2]->GetRandNumber() > players_[1]->GetRandNumber() &&
					players_[2]->GetRandNumber() > players_[3]->GetRandNumber())
				{
					players_[2]->SetAlive(true);
					players_[0]->SetAlive(false);
					players_[1]->SetAlive(false);
					players_[3]->SetAlive(false);
				}
				if (players_[3]->GetRandNumber() > players_[0]->GetRandNumber() &&
					players_[3]->GetRandNumber() > players_[1]->GetRandNumber() &&
					players_[3]->GetRandNumber() > players_[2]->GetRandNumber())
				{
					players_[3]->SetAlive(true);
					players_[0]->SetAlive(false);
					players_[1]->SetAlive(false);
					players_[2]->SetAlive(false);
				}
			}
		}
	}
}
