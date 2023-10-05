#include <chrono>
#include <DxLib.h>
#include "../Common/Fader.h"
#include "../Scene/TitleScene.h"
#include "../Scene/PlayerSelectScene.h"
#include "../Scene/SelectScene.h"
#include "../Scene/GameSelectScene.h"
#include "../Scene/GameScene.h"
#include "../Scene/GameScene2.h"
#include "../Scene/GameScene3.h"
#include "../Scene/GameScene4.h"
#include "../Scene/GameScene5.h"
#include "../Scene/ResultScene.h"
#include "SceneManager.h"

SceneManager* SceneManager::instance_ = nullptr;


void SceneManager::CreateInstance(void)
{

    if (instance_ == nullptr)
    {
        instance_ = new SceneManager();
    }
    instance_->Init();

}

SceneManager& SceneManager::GetInstance(void)
{

    return *instance_;

}

void SceneManager::Init(void)
{

	sceneId_ = SCENE_ID::TITLE;
	waitSceneId_ = SCENE_ID::NONE;

	// �Ó]�E���]�̏�����
	fader_ = new Fader();
	fader_->Init();

	isSceneChanging_ = false;

	// �f���^�^�C��
	preTime_ = std::chrono::system_clock::now();

	// �����V�[���̐ݒ�
	DoChangeScene(SCENE_ID::TITLE);

	// �o�g�����[�h
	battleMode_ = false;

	win1_ = 0;
	win2_ = 0;
	win3_ = 0;
	win4_ = 0;
}

void SceneManager::Update(void)
{

	if (scene_ == nullptr)
	{
		return;
	}

	// �f���^�^�C��
	auto nowTime = std::chrono::system_clock::now();
	deltaTime_ = static_cast<float>(
		std::chrono::duration_cast<std::chrono::nanoseconds>(nowTime - preTime_).count() / 1000000000.0);
	preTime_ = nowTime;

	// �Ó]�E���]�̍X�V
	fader_->Update();
	if (isSceneChanging_)
	{
		Fade();
	}
	else
	{
		scene_->Update();
	}

}

void SceneManager::Draw(void)
{

	// �`���O���t�B�b�N�̈�̎w��
	// (�R�c�`��Ŏg�p����J�����̐ݒ�Ȃǂ����Z�b�g�����)
	SetDrawScreen(DX_SCREEN_BACK);

	// ��ʂ�������
	ClearDrawScreen();

	scene_->Draw();

	// �Ó]�E���]�̕`��
	fader_->Draw();

}

void SceneManager::Release(void)
{

	scene_->Release();
	delete scene_;

}

void SceneManager::ChangeScene(SCENE_ID nextId)
{

	// �t�F�[�h�������I����Ă���V�[����ς���ꍇ�����邽�߁A
	// �J�ڐ�V�[���������o�ϐ��ɕێ�
	waitSceneId_ = nextId;

	// �t�F�[�h�A�E�g(�Ó])���J�n����
	fader_->SetFade(Fader::STATE::FADE_OUT);
	isSceneChanging_ = true;

}

SceneManager::SCENE_ID SceneManager::GetSceneID(void)
{
	return sceneId_;
}

float SceneManager::GetDeltaTime(void) const
{

	//return 1.0f / 60.0f;
	return deltaTime_;

}

int SceneManager::GetPlayerNum(void)
{
	return playerNum_;
}

void SceneManager::SetPlayerNum(int num)
{
	playerNum_ = num;
}

bool SceneManager::GetBattleMode(void)
{
	return battleMode_;
}

void SceneManager::SetBattleMode(bool battleMode)
{
	battleMode_ = battleMode;
}

void SceneManager::SetWin1(int win)
{
	win1_ += win;
}

void SceneManager::SetWin2(int win)
{
	win2_ += win;
}

void SceneManager::SetWin3(int win)
{
	win3_ += win;
}

void SceneManager::SetWin4(int win)
{
	win4_ += win;
}

int SceneManager::GetWin1(void)
{
	return win1_;
}

int SceneManager::GetWin2(void)
{
	return win2_;
}

int SceneManager::GetWin3(void)
{
	return win3_;
}

int SceneManager::GetWin4(void)
{
	return win4_;
}

SceneManager::SceneManager(void)
{

	sceneId_ = SCENE_ID::NONE;
	waitSceneId_ = SCENE_ID::NONE;

	scene_ = nullptr;
	fader_ = nullptr;

	isSceneChanging_ = false;

	// �f���^�^�C��
	deltaTime_ = 1.0f / 60.0f;

}

SceneManager::SceneManager(const SceneManager&)
{
	delete instance_;
}

SceneManager::~SceneManager(void)
{
}

void SceneManager::ResetDeltaTime(void)
{

	deltaTime_ = 0.016f;
	preTime_ = std::chrono::system_clock::now();

}

void SceneManager::DoChangeScene(SCENE_ID sceneId)
{

	// �V�[����ύX����
	sceneId_ = sceneId;

	// ���݂̃V�[�������
	if (scene_ != nullptr)
	{
		scene_->Release();
		delete scene_;
	}

	switch (sceneId_)
	{
	case SCENE_ID::TITLE:
		scene_ = new TitleScene();
		break;
	case SCENE_ID::PLAYERSELECT:
		scene_ = new PlayerSelectScene();
		break;
	case SCENE_ID::SELECT:
		scene_ = new SelectScene();
		break;
	case SCENE_ID::GAMESELECT:
		scene_ = new GameSelectScene();
		break;
	case SCENE_ID::GAME:
		scene_ = new GameScene();
		break;
	case SCENE_ID::GAME2:
		scene_ = new GameScene2();
		break;
	case SCENE_ID::GAME3:
		scene_ = new GameScene3();
		break;
	case SCENE_ID::GAME4:
		scene_ = new GameScene4();
		break;
	case SCENE_ID::GAME5:
		scene_ = new GameScene5();
		break;
	case SCENE_ID::RESULT:
		scene_ = new ResultScene();
		break;
	}
	scene_->Init();
	ResetDeltaTime();

	waitSceneId_ = SCENE_ID::NONE;

}

void SceneManager::Fade(void)
{

	Fader::STATE fState = fader_->GetState();
	switch (fState)
	{
	case Fader::STATE::FADE_IN:
		// ���]��
		if (fader_->IsEnd())
		{
			// ���]���I��������A�t�F�[�h�����I��
			fader_->SetFade(Fader::STATE::NONE);
			isSceneChanging_ = false;
		}
		break;
	case Fader::STATE::FADE_OUT:
		// �Ó]��
		if (fader_->IsEnd())
		{
			// ���S�ɈÓ]���Ă���V�[���J��
			DoChangeScene(waitSceneId_);
			// �Ó]���疾�]��
			fader_->SetFade(Fader::STATE::FADE_IN);
		}
		break;
	}

}
