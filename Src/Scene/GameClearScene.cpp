#include <DxLib.h>
#include "GameClearScene.h"
#include "../Manager/SceneManager.h"
#include "../Utility/Application.h"
#include "../Manager/InputManager.h"

GameClearScene::GameClearScene(void)
{
}

GameClearScene::~GameClearScene(void)
{
}

void GameClearScene::Init(void)
{

	// �摜�̓ǂݍ���
	imgGameClear_ = LoadGraph("Data/Image/UI/GameOver.png");

}

void GameClearScene::Update(void)
{

	SceneManager& sceneIns = SceneManager::GetInstance();
	auto& ins = InputManager::GetInstance();
	auto pad = InputManager::JOYPAD_NO::PAD1;
	auto input = ins.IsPadBtnTrgDown(pad, InputManager::JOYPAD_BTN::RIGHT);
	// �^�C�g����ʂɖ߂�
	if (CheckHitKey(KEY_INPUT_SPACE) || input)
	{

		// �X�y�[�X�L�[���������ꂽ��A�^�C�g���V�[���֑J�ڂ���
		sceneIns.GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);

	}

}

void GameClearScene::Draw(void)
{

	DrawGraph(0, 0, imgGameClear_, true);

}

void GameClearScene::Release(void)
{

	DeleteGraph(imgGameClear_);

}
