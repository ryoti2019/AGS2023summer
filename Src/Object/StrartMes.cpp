#include <DxLib.h>
#include "../Utility/Application.h"
#include "StrartMes.h"

StartMes::StartMes()
{
}

StartMes::~StartMes()
{
}

void StartMes::Init()
{
    LoadDivGraph("Data/Image/UI/StartMes.png",
	static_cast<int>(Mes::Max),
		1,
		static_cast<int>(Mes::Max),
		SIZE_X,
		SIZE_Y,
		&imageHdl_[0]);

	count_ = 0;

	// カウントダウンの音
	cntDown_ = LoadSoundMem("Data/Music/CountDown.mp3");

	// カウントダウンのスタート
	start_ = true;

}

void StartMes::Update(void)
{

	if (count_ >= 300)
	{
		return;
	}
	count_++;
	if (start_)
	{
		PlaySoundMem(cntDown_, DX_PLAYTYPE_BACK, true);
		start_ = false;
	}

}

void StartMes::Release(void)
{
	for (int j = 0; j < static_cast<int>(Mes::Max); j++)
	{
		DeleteGraph(imageHdl_[j]);
	}
}

void StartMes::Draw(void)
{

	if (count_ >= 240)
	{
		return;
	}
	if (count_ <= 60)
	{
		DrawGraph(
			(Application::SCREEN_SIZE_X - SIZE_X) / 2,
			(Application::SCREEN_SIZE_Y - SIZE_Y) / 2,
			imageHdl_[0],
			true);
	}
	if (count_ >= 61 && count_ <= 120)
	{
		DrawGraph(
			(Application::SCREEN_SIZE_X - SIZE_X) / 2,
			(Application::SCREEN_SIZE_Y - SIZE_Y) / 2,
			imageHdl_[1],
			true);
	}
	if (count_ >= 121 && count_ <= 180)
	{
		DrawGraph(
			(Application::SCREEN_SIZE_X - SIZE_X) / 2,
			(Application::SCREEN_SIZE_Y - SIZE_Y) / 2,
			imageHdl_[2],
			true);
	}
	if (count_ >= 181 && count_ <= 240)
	{
		DrawGraph(
			(Application::SCREEN_SIZE_X - SIZE_X) / 2,
			(Application::SCREEN_SIZE_Y - SIZE_Y) / 2,
			imageHdl_[3],
			true);
	}

}

int StartMes::GetCnt(void)
{
    return count_;
}
