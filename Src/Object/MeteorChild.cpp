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

	// �G�t�F�N�g�̓ǂݍ���
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

	// �e�̔��ˈʒu��ݒ�
	pos_ = pos;

	// �e�̔��˕����̐ݒ�
	dir_ = dir;

	// �e�̐������Ԃ̐ݒ�
	isAlive_ = true;

	// �e�̑��x
	speed_ = 10.0f;

	// �A�j���[�V�����X�s�[�h
	speedAnim_ = 0.3f;

	// �����̃A�j���[�V�������x
	blastSpeedAnim_ = 1.0f;

	// �����A�j���[�V�����p�J�E���^
	blastCntAnim_ = 0;

	// ��Ԃ̏�����
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
	// �������Ă��Ȃ������珈�����I������
	if (!isAlive_)
	{
		return;
	}

	pos_.x += dir_.x * speed_;
	pos_.y += dir_.y * speed_;

	// �v���C���[��艺�ɍs������false�ɂ���
	Vector2 pos = pos_;
	pos.x += SIZE_X / 2;
	pos.y += SIZE_Y - 10;
}

void MeteorChild::UpdateBlast(void)
{
	// �����̃A�j���[�V����
	blastCntAnim_++;

	// �����̃A�j���[�V�����ԍ�
	blastIdxAnim_ = static_cast<int>(static_cast<float>(blastCntAnim_) * blastSpeedAnim_) % EFFECT_MAX_NUM_ANIM;

	// �����̃A�j���[�V�����̏I������
	if (blastIdxAnim_ + 1 >= EFFECT_MAX_NUM_ANIM)
	{
		ChangeState(STATE::END);
	}
}

void MeteorChild::UpdateEnd(void)
{
	// �e�̏�������
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
		// �������Ă��Ȃ���Ώ������f
		return;
	}

	// �A�j���[�V�����̃`�b�v�ԍ�(0�`3)�����
	int animNo = static_cast<int>(static_cast<float>(cntAnim_) * speedAnim_) % imgNum_;

	// �e��`��
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

	// �ǂݍ��񂾉摜�̊J��
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
	// �f�o�b�O�p
	DrawBox(pos_.x - 3,
		pos_.y - 3,
		pos_.x + 3,
		pos_.y + 3,
		0xff0000, true);

	Vector2 headPos = pos_;
	headPos.x += SIZE_X / 2;

	// �I�����W
	int color = 0xff8c00;

	// �����F����
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

	// ��Ԃ̍X�V
	state_ = state;

	// ��ԑJ�ڎ��̏�����
	switch (state_)
	{
	case MeteorChild::STATE::BLAST:
		blastCntAnim_ = 0;
		break;
	case MeteorChild::STATE::END:
		break;
	}

}
