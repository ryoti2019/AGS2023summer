#include <DxLib.h>
#include "Rock.h"

Rock::Rock(int img)
{
	image_ = img;
}

Rock::~Rock(void)
{
}

void Rock::Init(void)
{
	cnt_ = 0;
}

void Rock::Update(void)
{



	if (cnt_ == 0)
	{

		for (int i = 0; i < ROCK_NUM; i++)
		{
			RockChild* rock = new RockChild(image_);
			children_.push_back(rock);
			rock->CreateRock({ pos_.x, pos_.y + i * 5 });
		}
		cnt_++;
	}

	for (auto rock : children_)
	{
		rock->Update();
	}

}

void Rock::Draw(void)
{
	for (auto rock : children_)
	{
		rock->Draw();
	}


}

void Rock::Release(void)
{

	for (auto rock : children_)
	{
		rock->Release();
		delete rock;
	}

}

Vector2 Rock::GetPos(void)
{
	return pos_;
}

void Rock::SetPos(Vector2 pos)
{
	pos_ = pos;
}

bool Rock::IsAlive(void)
{
	return isAlive_;
}

void Rock::SetAlive(bool isAlive)
{
	isAlive_ = isAlive;
}

std::vector<RockChild*> Rock::GetRockChild(void)
{
	return children_;
}

void Rock::AddCnt(int i)
{
	rockConter_ += i;
}

int Rock::GetRockCount(void)
{
	return rockConter_;
}
