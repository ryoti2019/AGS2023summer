#include <string>
#include <DxLib.h>
#include "../Utility/Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Object/Player5.h"
#include "../Object/StrartMes.h"
#include "ResultScene.h"
#include "GameScene5.h"

GameScene5::GameScene5(void)
{
}

GameScene5::~GameScene5(void)
{
}

void GameScene5::Init(void)
{

	// �w�i�摜�̓ǂݍ���
	bgImage_ = LoadGraph("Data/Image/UI/Sky.png");

	// �w�i�摜�̕`��̓ǂݍ���
	kokubanImage_ = LoadGraph("Data/Image/UI/kokuban2.png");

	// ���̓ǂݍ���
	arrowImage_ = LoadGraph("Data/Image/Object/yajirushi.png");

	// �Q�[�������p�̉摜�̓ǂݍ���
	expImage_ = LoadGraph("Data/Image/UI/game5UI.png");

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

	// �X�^�[�g�摜�̓ǂݍ���
	startImage_ = LoadGraph("Data/Image/UI/start.png");

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
	int pSpace = 0;	// 2�l�F150�@3�l�F100�@�S�l�F75
	if (pNum == 2)
	{
		pSpace = 232;
	}
	if (pNum == 3)
	{
		pSpace = 132;
	}
	if (pNum == 4)
	{
		pSpace = 107;
	}
	for (int i = 0; i < pNum; i++)
	{
		Player5* p = new Player5();
		InputManager::JOYPAD_NO jno = static_cast<InputManager::JOYPAD_NO>(i + 1);
		p->Init(this, jno);
		p->SetPos({ pSpace + (pSize * i), 550 });
		players_.push_back(p);
	}

	// ���͂��Ȃ��Ƃ����Ȃ���
	pushMax_ = 5;

	// ���������߂�O�̃t���O
	dirAlive_ = true;

	// ���͂������̂��i�[����z��
	direction_ = std::vector<int>(pushMax_);

	// ���ɗv�f���𑫂�
	pushBack_ = false;

	// �摜���o�Ă��鎞��
	imageTime_ = 180;

	// �����Ă���v���C���[�̃t���O�ɍ��킹��
	playerInput_ = false;

	// �X�^�[�g���b�Z�[�W�̏�����
	startMes_ = new StartMes();
	startMes_->Init();

	// ���͂���̓ǂݍ���
	nyuuryokusiro_ = LoadGraph("Data/Image/UI/nyuuryokusiro.png");

	// �Q�[���������X�L�b�v����t���O
	skip_ = false;

	// �A�j���[�V�����̃J�E���^
	cntAnim_ = 0;

	// BGM�̓ǂݍ���
	bgm_ = LoadSoundMem("Data/Music/game5BGM.mp3");
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP, true);

	// ��肪�o���ꂽ�Ƃ��̉�
	questionSE_ = LoadSoundMem("Data/Music/Question.mp3");

	// �_���[�W��H��������̉��̓ǂݍ���
	damageSE_ = LoadSoundMem("Data/Music/explosion1.mp3");

	// ����{�^����SE�̓ǂݍ���
	decideSE_ = LoadSoundMem("Data/Music/decideGame.mp3");

	// ������\�������I�����
	isAnswer_ = false;

	// ������\�������鎞��
	answerTime_ = 0;

	// ����{�^����SE�̓ǂݍ���
	decideSE_ = LoadSoundMem("Data/Music/decideGame.mp3");

	// �A�j���[�V�����̃J�E���^
	cntAnim_ = 0;

	inputNum_ = 0;

	startNum_ = 0;

	isStart_ = false;

	result_ = false;

	revival_ = false;

	isRand1_ = true;
	isRand2_ = true;
	isRand3_ = true;
	isRand4_ = true;

	inputRandNum_ = 0;

	revivalHP_ = true;

	win_ = true;
}

void GameScene5::Update(void)
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

	for (auto player : players_)
	{
		// �v���C���[�̍X�V
		player->Update();
	}

	if (!revival_)
	{
		if (isStart_)
		{
			if (!result_)
			{
				// �����������_���Ɍ��߂�
				if (dirAlive_)
				{
					for (int i = 0; i < pushMax_; i++)
					{
						direction_[i] = (GetRand(3)) + 1;
					}
					dirAlive_ = false;
					PlaySoundMem(questionSE_, DX_PLAYTYPE_BACK, true);
				}

				int pNum = SceneManager::GetInstance().GetPlayerNum();
				int inputNum = 0;
				// �v���C���[���S�����͂��I������i��
				for (int i = 0; i < pNum; i++)
				{
					if (players_[i]->GetinputAlive())
					{
						inputNum++;
					}
					if (pNum == inputNum)
					{
						inputEnd_ = true;
					}
				}

				// ���͂��Ȃ��Ƃ����Ȃ����Ɠ��͂��������ꏏ�ȏ�ł�������if���ɓ���
				if (inputEnd_)
				{
					int i = 0;
					for (auto player : players_)
					{
						if (isAnswer_)
						{
							int i = 0;
							int damage = 0;
							for (int i = 0; i < pNum; i++)
							{
								if (players_[i]->GetDamage())
								{
									damage += 1;
								}
							}
							if (damage == pNum)
							{
								int i = 0;
								if (pushBack_)
								{
									int i = 0;
									for (int i = 0; i < pushMax_; i++)
									{
										direction_[i] = 0;
									}
									// ���͂�����������������
									dirAlive_ = true;
									imageTime_ = 180;
									answerTime_ = 0;
									if (answerTime_ == 0)
									{
										isAnswer_ = false;
									}
									if (pushMax_ < 12)
									{
										// ���͂��Ȃ��Ƃ����Ȃ����𑝂₷
										pushMax_++;
										// �V���ɔz���t��������
										direction_.emplace_back();
									}
								}
							}
						}
					}

					if (inputEnd_ && answerTime_ <= 180)
					{
						answerTime_++;
					}

					// HP�����炵�I������܂������������_���Ō��܂�
					int notInputNum = 0;
					if (!isAnswer_)
					{
						for (int i = 0; i < pNum; i++)
						{
							if (!players_[i]->GetinputAlive())
							{
								notInputNum++;
							}
							if (pNum == notInputNum)
							{
								inputEnd_ = false;
								pushBack_ = false;
							}
						}
					}

					if (answerTime_ >= 180)
					{
						isAnswer_ = true;
					}
				}
			}
		}
	}

	// �v���C���[�̎��S�����l���ɍ��킹�ăV�[���J�ڂ���
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
					players_[0]->SetHP(5);
					players_[0]->SetAlive(true);
				}
				if (i == 1 && players_[1]->OldAlive())
				{
					players_[1]->SetHP(5);
					players_[1]->SetAlive(true);
				}
				if (i == 2 && players_[2]->OldAlive())
				{
					players_[2]->SetHP(5);
					players_[2]->SetAlive(true);
				}
				if (i == 3 && players_[3]->OldAlive())
				{
					players_[3]->SetHP(5);
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
	

void GameScene5::Draw(void)
{

	// �w�i�摜�̕`��
	DrawGraph(0, 0, bgImage_, true);

	// ���摜�̕`��
	DrawGraph(100, 0, kokubanImage_, true);

	for (auto player : players_)
	{
		// �v���C���[�̕`��
		player->Draw();
	}

	if (skip_)
	{
		// �X�^�[�g���b�Z�[�W�̕`��
		startMes_->Draw();

		if (startMes_->GetCnt() >= 240)
		{
			if (imageTime_ >= 0)
			{
				for (int i = 0; i < pushMax_; i++)
				{
					if (direction_[i] == 1)
					{
						DrawRotaGraph(125 * (i % 6) + 180, 100 * ((i / 6) * 2) + 100, 1.0f, AsoUtility::Deg2RadF(90.0f), arrowImage_, true);
					}
					if (direction_[i] == 2)
					{
						DrawRotaGraph(125 * (i % 6) + 180, 100 * ((i / 6) * 2) + 100, 1.0f, AsoUtility::Deg2RadF(180.0f), arrowImage_, true);
					}
					if (direction_[i] == 3)
					{
						DrawRotaGraph(125 * (i % 6) + 180, 100 * ((i / 6) * 2) + 100, 1.0f, AsoUtility::Deg2RadF(270.0f), arrowImage_, true);
					}
					if (direction_[i] == 4)
					{
						DrawRotaGraph(125 * (i % 6) + 180, 100 * ((i / 6) * 2) + 100, 1.0f, 0.0f, arrowImage_, true);
					}
				}
				imageTime_--;
			}
		}

		if (inputEnd_)
		{
			if (answerTime_ >= 0)
			{
				for (int i = 0; i < pushMax_; i++)
				{
					if (direction_[i] == 1)
					{
						DrawRotaGraph(125 * (i % 6) + 180, 100 * ((i / 6) * 2) + 100, 1.0f, AsoUtility::Deg2RadF(90.0f), arrowImage_, true);
					}
					if (direction_[i] == 2)
					{
						DrawRotaGraph(125 * (i % 6) + 180, 100 * ((i / 6) * 2) + 100, 1.0f, AsoUtility::Deg2RadF(180.0f), arrowImage_, true);
					}
					if (direction_[i] == 3)
					{
						DrawRotaGraph(125 * (i % 6) + 180, 100 * ((i / 6) * 2) + 100, 1.0f, AsoUtility::Deg2RadF(270.0f), arrowImage_, true);
					}
					if (direction_[i] == 4)
					{
						DrawRotaGraph(125 * (i % 6) + 180, 100 * ((i / 6) * 2) + 100, 1.0f, 0.0f, arrowImage_, true);
					}
				}
			}
		}
		// �f�o�b�O�`��
		//DrawDebug();
	}
	cntAnim_++;
	if (!skip_)
	{
		// �Q�[�������摜�̕`��
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 230, 1.0f, 0.0f, expImage_, true);
		DrawGraph(820, 367, BbottonImage_[(cntAnim_ / 10) % 4], true);
		DrawGraph(470, 360, LstickIMage_[cntAnim_ / 5 % 8], true);
	}

	if (imageTime_ <= 0)
	{
		if (!inputEnd_)
		{
			DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 200, 1.0f, 0.0f, nyuuryokusiro_, true);
		}
	}

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

void GameScene5::Release(void)
{

	// �X�^�[�g���b�Z�[�W�̍X�V
	startMes_->Release();
	delete startMes_;

	for (auto player : players_)
	{
		// �v���C���[�̊J��
		player->Release();
	}
}

bool GameScene5::GetInputEnd(void)
{
	return inputEnd_;
}

void GameScene5::SetInputEnd(bool inputEnd)
{
	inputEnd_ = inputEnd;
}

std::vector<int> GameScene5::GetDir(void)
{
	return direction_;
}

void GameScene5::SetPushBack(bool pushback)
{
	pushBack_ = pushback;
}

int GameScene5::GetImageTime(void)
{
	return imageTime_;
}

bool GameScene5::GetPlayerInput(void)
{
	return playerInput_;
}

int GameScene5::GetAnswerTime(void)
{
	return answerTime_;
}

bool GameScene5::GetIsAnswer(void)
{
	return isAnswer_;
}

bool GameScene5::GetResult(void)
{
	return result_;
}

bool GameScene5::GetSkip(void)
{
	return skip_;
}

bool GameScene5::IsStart(void)
{
	return isStart_;
}

void GameScene5::SetInputNum(int input)
{
	inputNum_ += input;
}

void GameScene5::SetStartNum(int start)
{
	startNum_ += start;
}

bool GameScene5::GetRevival(void)
{
	return revival_;
}

void GameScene5::DrawDebug(void)
{

	// �z��̒��g���m�F����
	std::string arrayString;
	for (int i = 0; i < sizeof(direction_) / sizeof(direction_[0]); i++) {
		if (pushMax_ - 1 < i) break;
		arrayString += std::to_string(direction_[i]) + " ";
	}
	DrawString(0, 0, arrayString.c_str(), GetColor(255, 255, 255));

}

void GameScene5::Result(void)
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
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::RESULT);
			StopSoundMem(bgm_);
			return;
		}
	}

	if (inputNum_ == pNum || InputManager::GetInstance().IsTrgDown(KEY_INPUT_Z))
	{
		PlaySoundMem(decideSE_, DX_PLAYTYPE_BACK, false);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::RESULT);
		StopSoundMem(bgm_);
	}

}

void GameScene5::Rand(void)
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
					players_[1]->SetHP(-5);
					players_[1]->SetAlive(false);
				}
				if (players_[1]->GetRandNumber() > players_[0]->GetRandNumber())
				{
					players_[1]->SetAlive(true);
					players_[0]->SetHP(-5);
					players_[0]->SetAlive(false);
				}
			}
			if (pNum == 3)
			{
				if (players_[0]->GetRandNumber() > players_[1]->GetRandNumber() &&
					players_[0]->GetRandNumber() > players_[2]->GetRandNumber())
				{
					players_[0]->SetAlive(true);
					players_[1]->SetHP(-5);
					players_[2]->SetHP(-5);
					players_[1]->SetAlive(false);
					players_[2]->SetAlive(false);
				}
				if (players_[1]->GetRandNumber() > players_[0]->GetRandNumber() &&
					players_[1]->GetRandNumber() > players_[2]->GetRandNumber())
				{
					players_[1]->SetAlive(true);
					players_[0]->SetHP(-5);
					players_[2]->SetHP(-5);
					players_[0]->SetAlive(false);
					players_[2]->SetAlive(false);
				}
				if (players_[2]->GetRandNumber() > players_[0]->GetRandNumber() &&
					players_[2]->GetRandNumber() > players_[1]->GetRandNumber())
				{
					players_[2]->SetAlive(true);
					players_[0]->SetHP(-5);
					players_[1]->SetHP(-5);
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
					players_[1]->SetHP(-5);
					players_[2]->SetHP(-5);
					players_[3]->SetHP(-5);
					players_[1]->SetAlive(false);
					players_[2]->SetAlive(false);
					players_[3]->SetAlive(false);
				}
				if (players_[1]->GetRandNumber() > players_[0]->GetRandNumber() &&
					players_[1]->GetRandNumber() > players_[2]->GetRandNumber() &&
					players_[1]->GetRandNumber() > players_[3]->GetRandNumber())
				{
					players_[1]->SetAlive(true);
					players_[0]->SetHP(-5);
					players_[2]->SetHP(-5);
					players_[3]->SetHP(-5);
					players_[0]->SetAlive(false);
					players_[2]->SetAlive(false);
					players_[3]->SetAlive(false);
				}
				if (players_[2]->GetRandNumber() > players_[0]->GetRandNumber() &&
					players_[2]->GetRandNumber() > players_[1]->GetRandNumber() &&
					players_[2]->GetRandNumber() > players_[3]->GetRandNumber())
				{
					players_[2]->SetAlive(true);
					players_[0]->SetHP(-5);
					players_[1]->SetHP(-5);
					players_[3]->SetHP(-5);
					players_[0]->SetAlive(false);
					players_[1]->SetAlive(false);
					players_[3]->SetAlive(false);
				}
				if (players_[3]->GetRandNumber() > players_[0]->GetRandNumber() &&
					players_[3]->GetRandNumber() > players_[1]->GetRandNumber() &&
					players_[3]->GetRandNumber() > players_[2]->GetRandNumber())
				{
					players_[3]->SetAlive(true);
					players_[0]->SetHP(-5);
					players_[1]->SetHP(-5);
					players_[2]->SetHP(-5);
					players_[0]->SetAlive(false);
					players_[1]->SetAlive(false);
					players_[2]->SetAlive(false);
				}
			}
		}
	}

}
