#include <DxLib.h>
#include "../Utility/Application.h"
#include "../Manager/SceneManager.h"
#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"
#include "Shot2.h"

Shot2::Shot2(int* imgs, int imgNum)
{
    imgs_ = imgs;
    imgNum_ = imgNum;

	// エフェクトの読み込み
	LoadDivGraph("Data/Image/Player/hitEffect3.png",
		EFFECT_MAX_NUM_ANIM,
		EFFECT_NUM_X, EFFECT_NUM_Y,
		EFECT_SIZE_X, EFECT_SIZE_Y,
		&hitEffectImage_[0]);

}

Shot2::~Shot2(void)
{
}

void Shot2::CreateShot(Vector2 pos, Vector2F dir)
{

	// 弾の発射位置を設定
	pos_ = pos;

	// 弾の発射方向の設定
	dir_ = dir;

	// 弾の生存時間の設定
	stepAlive_ = SHOT_ALIVE;

	// 弾の速度
	speed_ = 5.0f;

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

void Shot2::Init(void)
{
}

void Shot2::Update(void)
{

	switch (state_)
	{

	case Shot2::STATE::SHOT:
		UpdateShot();
		break;
	case Shot2::STATE::BLAST:
		UpdateBlast();
		break;
	case Shot2::STATE::END:
		UpdateEnd();
		break;

	}



}

void Shot2::UpdateShot(void)
{
	// 弾を移動させる
	pos_.x += dir_.x * speed_;
	pos_.y += dir_.y * speed_;
}

void Shot2::UpdateBlast(void)
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

void Shot2::UpdateEnd(void)
{
	// 弾の消失判定
	state_ = STATE::END;
}

void Shot2::Draw(void)
{


	switch (state_)
	{

	case Shot2::STATE::SHOT:
		DrawShot();
		break;
	case Shot2::STATE::BLAST:
		DrawBlast();
		break;
	case Shot2::STATE::END:
		DrawEnd();
		break;

	}
	if (!IsAlive())
	{
		// 生存していなければ処理中断
		return;
	}

	float rad = atan2f(dir_.y, dir_.x);
	float deg = rad * 180.0f / DX_PI_F;

	if (deg == -90.0f)
	{
		dir2_ = AsoUtility::DIR::UP;
	}

	// プレイヤー画像の描画
	// アニメーションのチップ番号(0～3)を作る
	animData_[0] = 0;
	animData_[1] = 1;
	animData_[2] = 2;
	animData_[3] = 3;

	DrawRotaGraph(pos_.x, pos_.y, 1.0f, 0.0f, imgs_[static_cast<int>(dir2_) * 4 + animData_[(cntAnim_ / 10) % 4]], true);
	cntAnim_++;

}

void Shot2::DrawShot(void)
{
	if (!IsAlive())
	{
		// 生存していなければ処理中断
		return;
	}

	float rad = atan2f(dir_.y, dir_.x);
	float deg = rad * 180.0f / DX_PI_F;

	if (deg == -90.0f)
	{
		dir2_ = AsoUtility::DIR::UP;
	}

	// プレイヤー画像の描画
	// アニメーションのチップ番号(0～3)を作る
	animData_[0] = 0;
	animData_[1] = 1;
	animData_[2] = 2;
	animData_[3] = 3;

	DrawRotaGraph(pos_.x, pos_.y, 1.0f, 0.0f, imgs_[static_cast<int>(dir2_) * 4 + animData_[(cntAnim_ / 10) % 4]], true);
	cntAnim_++;
}

void Shot2::DrawBlast(void)
{
	DrawRotaGraph(blastPos_.x, blastPos_.y, 0.5f, 0.0f, hitEffectImage_[blastIdxAnim_], true);
}

void Shot2::DrawEnd(void)
{
}

void Shot2::Release(void)
{

	// 読み込んだ画像の開放
	for (int i = 0; i < imgNum_; i++)
	{
		DeleteGraph(imgs_[i]);
	}

}

bool Shot2::IsAlive(void)
{
	return stepAlive_ > 0.0f;
}

Vector2 Shot2::GetPos(void)
{
	return pos_;
}

void Shot2::SetAlive(bool alive)
{
}

void Shot2::ShotBlast(void)
{
	stepAlive_ = 0.0f;
}

void Shot2::Blast(Vector2F pos)
{
	blastPos_ = pos;
	ChangeState(STATE::BLAST);
}

void Shot2::ChangeState(STATE state)
{
	// 状態の更新
	state_ = state;

	// 状態遷移時の初期化
	switch (state_)
	{
	case Shot2::STATE::BLAST:
		blastCntAnim_ = 0;
		break;
	case Shot2::STATE::END:
		break;
	}

}
