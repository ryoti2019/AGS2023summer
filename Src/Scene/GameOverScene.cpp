#include <DxLib.h>
#include "GameOverScene.h"
#include "../Manager/SceneManager.h"
#include "../Utility/Application.h"
#include "../Manager/InputManager.h"

GameOverScene::GameOverScene(void)
{
}

GameOverScene::~GameOverScene(void)
{
}

void GameOverScene::Init(void)
{

	// �摜�̓ǂݍ���
	imgGameOver_ = LoadGraph("Data/Image/UI/GameOver.png");

}

void GameOverScene::Update(void)
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

void GameOverScene::Draw(void)
{

	DrawGraph(0, 0, imgGameOver_, true);

}

void GameOverScene::Release(void)
{

	DeleteGraph(imgGameOver_);

}
