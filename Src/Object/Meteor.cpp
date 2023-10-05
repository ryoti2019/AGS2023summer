#include <DxLib.h>
#include "../Manager/SceneManager.h"
#include "Player.h"
#include "Meteor.h"

Meteor::Meteor(int* imgs, int imgNum)
{
	imgs_ = imgs;
	imgNum_ = imgNum;
}

Meteor::~Meteor(void)
{
}

void Meteor::Init(GameScene* scene)
{
	// ゲームシーンの機能を使えるようにする
	gameScene_ = scene;

	step_ = 0;
	nextStep_ = 80;

}

void Meteor::Update(void)
{

	if (gameScene_->GetSkip())
	{
		if (gameScene_->IsStart())
		{
			step_++;

			if (step_ > nextStep_)
			{
				step_ = 0;
				nextStep_ = 20 + GetRand(20);
				auto meteor = GetValidMeteor();
				meteor->CreateShot(pos_, Vector2F(0.0f, 1.0f));
			}

			for (auto meteor : children_)
			{
				meteor->Update();
			}

		}
	}
}

void Meteor::Draw(void)
{

	for (auto meteor : children_)
	{
		meteor->Draw();
	}

}

void Meteor::Release(void)
{

	for (auto meteor : children_)
	{
		meteor->Release();
		delete meteor;
	}

}

Vector2 Meteor::GetPos(void)
{
	return pos_;
}

void Meteor::SetPos(Vector2 pos)
{
	pos_ = pos;
}

std::vector<Meteor*> Meteor::GetMeteors(void)
{
	return meteors_;
}

std::vector<MeteorChild*> Meteor::GetMeteorChildlen(void)
{
	return children_;
}

MeteorChild* Meteor::GetValidMeteor(void)
{

	size_t size = children_.size();
	for (int i = 0; i < size; i++)
	{
		if (!children_[i]->IsAlive())
		{
			return children_[i];
		}
	}

	MeteorChild* meteor = new MeteorChild(imgs_, imgNum_);
	children_.push_back(meteor);

	return meteor;

}
