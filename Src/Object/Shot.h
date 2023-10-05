#pragma once
#include <vector>
#include "../Scene/GameScene.h"
#include "../Utility/AsoUtility.h"
#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"

class Shot
{
public:

	// �e�̐�������
	static constexpr float SHOT_ALIVE = 3.0f;

	// �e�̃T�C�Y
	static constexpr int SIZE_X = 64;
	static constexpr int SIZE_Y = 64;

	// �G�t�F�N�g�̍ő�A�j���[�V����
	static constexpr int EFFECT_MAX_NUM_ANIM = 27;

	// �G�t�F�N�g�̃T�C�Y
	static constexpr int EFECT_SIZE_X = 516;
	static constexpr int EFECT_SIZE_Y = 528;

	// �G�t�F�N�g�̕�����
	static constexpr int EFFECT_NUM_X = 9;
	static constexpr int EFFECT_NUM_Y = 3;

	// �e�̏��
	enum class STATE
	{
		NONE,
		SHOT,
		BLAST,
		END
	};

	// �R���X�g���N�^
	Shot(int* imgs, int imgNum);

	// �f�X�g���N�^
	~Shot(void);

	// 覐΂̐���(覐΂̐i�s�����A�\���J�n���W)
	void CreateShot(Vector2 pos, Vector2F dir);

	void Init(void);

	void Update(void);
	void UpdateShot(void);
	void UpdateBlast(void);
	void UpdateEnd(void);

	void Draw(void);
	void DrawShot(void);
	void DrawBlast(void);
	void DrawEnd(void);

	void Release(void);

	// ��������
	bool IsAlive(void);

	// ���W�̎擾
	Vector2 GetPos(void);

	// ��������̐ݒ�
	void SetAlive(bool alive);

	// �e�𔚔�������
	void ShotBlast(void);

	// �����J�n
	void Blast(Vector2F pos);

private:

	// �v���C���[
	Player* player_;

	// �e�̏��
	STATE state_;

	// ����
	Vector2F dir_;

	// �A�j���[�V�����̕���
	AsoUtility::DIR dir2_;

	// ���W
	Vector2 pos_;

	// �������W
	Vector2F blastPos_;

	// �摜
	int* imgs_;
	int imgNum_;

	// �A�j���[�V�����X�s�[�h
	float speedAnim_;

	// �A�j���[�V�����̃J�E���g
	int cntAnim_;

	// �A�j���[�V�����̃f�[�^
	int animData_[5];

	// ��������
	bool isAlive_;

	// 覐΂̈ړ����x
	float speed_;

	// �e�̐������Ԍv�Z�p
	float stepAlive_;

	// �����̃A�j���[�V�����J�E���^
	int blastCntAnim_;

	// �����̃A�j���[�V�������x
	float blastSpeedAnim_;

	// �����̃A�j���[�V�����ԍ�
	int blastIdxAnim_;

	// ��ԑJ��
	void ChangeState(STATE state);

	// �����������̃G�t�F�N�g
	int hitEffectImage_[EFFECT_MAX_NUM_ANIM];

};

