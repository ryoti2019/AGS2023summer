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

	// �G�t�F�N�g�̓ǂݍ���
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

	// �e�̔��ˈʒu��ݒ�
	pos_ = pos;

	// �e�̔��˕����̐ݒ�
	dir_ = dir;

	// �e�̐������Ԃ̐ݒ�
	stepAlive_ = SHOT_ALIVE;

	// �e�̑��x
	speed_ = 5.0f;

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
	// �e���ړ�������
	pos_.x += dir_.x * speed_;
	pos_.y += dir_.y * speed_;
}

void Shot2::UpdateBlast(void)
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

void Shot2::UpdateEnd(void)
{
	// �e�̏�������
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
		// �������Ă��Ȃ���Ώ������f
		return;
	}

	float rad = atan2f(dir_.y, dir_.x);
	float deg = rad * 180.0f / DX_PI_F;

	if (deg == -90.0f)
	{
		dir2_ = AsoUtility::DIR::UP;
	}

	// �v���C���[�摜�̕`��
	// �A�j���[�V�����̃`�b�v�ԍ�(0�`3)�����
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
		// �������Ă��Ȃ���Ώ������f
		return;
	}

	float rad = atan2f(dir_.y, dir_.x);
	float deg = rad * 180.0f / DX_PI_F;

	if (deg == -90.0f)
	{
		dir2_ = AsoUtility::DIR::UP;
	}

	// �v���C���[�摜�̕`��
	// �A�j���[�V�����̃`�b�v�ԍ�(0�`3)�����
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

	// �ǂݍ��񂾉摜�̊J��
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
	// ��Ԃ̍X�V
	state_ = state;

	// ��ԑJ�ڎ��̏�����
	switch (state_)
	{
	case Shot2::STATE::BLAST:
		blastCntAnim_ = 0;
		break;
	case Shot2::STATE::END:
		break;
	}

}
