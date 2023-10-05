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

	// 画像の読み込み
	imgGameOver_ = LoadGraph("Data/Image/UI/GameOver.png");

}

void GameOverScene::Update(void)
{

	SceneManager& sceneIns = SceneManager::GetInstance();
	auto& ins = InputManager::GetInstance();
	auto pad = InputManager::JOYPAD_NO::PAD1;
	auto input = ins.IsPadBtnTrgDown(pad, InputManager::JOYPAD_BTN::RIGHT);
	// タイトル画面に戻る
	if (CheckHitKey(KEY_INPUT_SPACE) || input)
	{

		// スペースキーが押下されたら、タイトルシーンへ遷移する
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
