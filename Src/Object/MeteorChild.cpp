#include <DxLib.h>
#include "../Utility/Application.h"
#include "../Manager/SceneManager.h"
#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"
#include "Player.h"
#include "MeteorChild.h"

MeteorChild::MeteorChild(int* imgs, int imgNum)
{
	imgs_ = imgs;
	imgNum_ = imgNum;

	// エフェクトの読み込み
	LoadDivGraph("Data/Image/Player/hitEffect.png",
		EFFECT_MAX_NUM_ANIM,
		EFFECT_NUM_X, EFFECT_NUM_Y,
		EFECT_SIZE_X, EFECT_SIZE_Y,
		&hitEffectImage_[0]);

}

MeteorChild::~MeteorChild(void)
{
}

void MeteorChild::CreateShot(Vector2 pos, Vector2F dir)
{

	// 弾の発射位置を設定
	pos_ = pos;

	// 弾の発射方向の設定
	dir_ = dir;

	// 弾の生存時間の設定
	isAlive_ = true;

	// 弾の速度
	speed_ = 10.0f;

	// アニメーションスピード
	speedAnim_ = 0.3f;

	// 爆発のアニメーション速度
	blastSpeedAnim_ = 1.0f;

	// 爆発アニメーション用カウンタ
	blastCntAnim_ = 0;

	// 状態の初期化
	state_ = STATE::NONE;

	ChangeState(STATE::SHOT);

}

void MeteorChild::Update(void)
{

	switch (state_)
	{

	case MeteorChild::STATE::SHOT:
		UpdateShot();
		break;
	case MeteorChild::STATE::BLAST:
		UpdateBlast();
		break;
	case MeteorChild::STATE::END:
		UpdateEnd();
		break;

	}

}

void MeteorChild::UpdateShot(void)
{
	// 生存していなかったら処理を終了する
	if (!isAlive_)
	{
		return;
	}

	pos_.x += dir_.x * speed_;
	pos_.y += dir_.y * speed_;

	// プレイヤーより下に行ったらfalseにする
	Vector2 pos = pos_;
	pos.x += SIZE_X / 2;
	pos.y += SIZE_Y - 10;
}

void MeteorChild::UpdateBlast(void)
{
	// 爆発のアニメーション
	blastCntAnim_++;

	// 爆発のアニメーション番号
	blastIdxAnim_ = static_cast<int>(static_cast<float>(blastCntAnim_) * blastSpeedAnim_) % EFFECT_MAX_NUM_ANIM;

	// 爆発のアニメーションの終了判定
	if (blastIdxAnim_ + 1 >= EFFECT_MAX_NUM_ANIM)
	{
		ChangeState(STATE::END);
	}
}

void MeteorChild::UpdateEnd(void)
{
	// 弾の消失判定
	state_ = STATE::END;
}

void MeteorChild::Draw(void)
{


	switch (state_)
	{

	case MeteorChild::STATE::SHOT:
		DrawShot();
		break;
	case MeteorChild::STATE::BLAST:
		DrawBlast();
		break;
	case MeteorChild::STATE::END:
		DrawEnd();
		break;

	}

}

void MeteorChild::DrawShot(void)
{
	if (!IsAlive())
	{
		// 生存していなければ処理中断
		return;
	}

	// アニメーションのチップ番号(0～3)を作る
	int animNo = static_cast<int>(static_cast<float>(cntAnim_) * speedAnim_) % imgNum_;

	// 弾を描画
	Vector2 pos = pos_;
	DrawGraph(pos.x, pos.y, imgs_[animNo], true);
	cntAnim_++;
}

void MeteorChild::DrawBlast(void)
{
	DrawGraph(blastPos_.x - 20, blastPos_.y, hitEffectImage_[blastIdxAnim_], true);
}

void MeteorChild::DrawEnd(void)
{
}


void MeteorChild::Release(void)
{

	// 読み込んだ画像の開放
	for (int i = 0; i < imgNum_; i++)
	{
		DeleteGraph(imgs_[i]);
	}

}

bool MeteorChild::IsAlive(void)
{
	return isAlive_;
}

Vector2 MeteorChild::GetMeteorPos(void)
{
	Vector2 pos = pos_;
	pos.y += SIZE_Y;
	return pos_;
}

void MeteorChild::SetAlive(bool alive)
{
	isAlive_ = alive;
}

void MeteorChild::Blast(Vector2F pos)
{
	blastPos_ = pos;
	ChangeState(STATE::BLAST);
}

void MeteorChild::DrawDebug(void)
{
	// デバッグ用
	DrawBox(pos_.x - 3,
		pos_.y - 3,
		pos_.x + 3,
		pos_.y + 3,
		0xff0000, true);

	Vector2 headPos = pos_;
	headPos.x += SIZE_X / 2;

	// オレンジ
	int color = 0xff8c00;

	// 足元：中央
	DrawBox(headPos.x - 3, headPos.y - 3,
		headPos.x + 3, headPos.y + 3, 0xff0000, true);

	Vector2 pos = pos_;
	pos.x += SIZE_X / 2;
	pos.y += SIZE_Y - 10;
	DrawBox(pos.x - 3, pos.y - 3,
		pos.x + 3, pos.y + 3, 0xff0000, true);

	DrawLine(0, 510, Application::SCREEN_SIZE_X, 510, 0xff0000);
}

void MeteorChild::ChangeState(STATE state)
{

	// 状態の更新
	state_ = state;

	// 状態遷移時の初期化
	switch (state_)
	{
	case MeteorChild::STATE::BLAST:
		blastCntAnim_ = 0;
		break;
	case MeteorChild::STATE::END:
		break;
	}

}
