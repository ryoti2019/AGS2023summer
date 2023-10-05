#include <DxLib.h>
#include "RockChild.h"

RockChild::RockChild(int img)
{
	image_ = img;
}

RockChild::~RockChild(void)
{
}

void RockChild::CreateRock(Vector2 pos)
{
	pos_ = pos;
}

void RockChild::Update(void)
{

}

void RockChild::Draw(void)
{

	if (!isAlive_)
	{
		return;
	}

	DrawGraph(pos_.x, pos_.y, image_, true);

}

void RockChild::Release(void)
{

	// “Ç‚İ‚ñ‚¾‰æ‘œ‚ÌŠJ•ú
	for (int i = 0; i < ROCK_NUM; i++)
	{
		DeleteGraph(image_);
	}

}

bool RockChild::IsAlive(void)
{
    return isAlive_;
}

Vector2 RockChild::GetPos(void)
{
	return pos_;
}

void RockChild::SetAlive(bool alive)
{
	isAlive_ = alive;
}

