#include <DxLib.h>
#include "Application.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"

Application::Application(void)
{
	isError_ = false;
}

Application::~Application(void)
{
}

void Application::Init(void)
{

	// アプリケーションの初期設定
	SetWindowText("2216008_寺師遼");

	// ウィンドウサイズ
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)
	{
		isError_ = true;
		return;
	}

	// キー制御初期化
	SetUseDirectInputFlag(true);

	// シーン管理インスタンス生成＆初期化
	SceneManager::CreateInstance();

	// 入力管理インスタンス生成＆初期化
	InputManager::CreateInstance();

}

void Application::Run(void)
{

	// ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		InputManager::GetInstance().Update();

		SceneManager::GetInstance().Update();

		SceneManager::GetInstance().Draw();

		ScreenFlip();

	}

}

void Application::Release(void)
{

	if (DxLib_End() == -1)
	{
		isError_ = true;
		return;
	}

}

bool Application::IsError(void)
{
	return isError_;
}
