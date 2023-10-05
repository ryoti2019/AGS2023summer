#pragma once
#include "../Scene/GameScene.h"
#include "../Utility/AsoUtility.h"
#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"

class Player;

class MeteorChild
{

public:

	// �e�̐�������
	static constexpr float SHOT_ALIVE = 3.0f;

	// ���e�I�̃T�C�Y
	static constexpr int SIZE_X = 64;
	static constexpr int SIZE_Y = 64;

	// �G�t�F�N�g�̍ő�A�j���[�V����
	static constexpr int EFFECT_MAX_NUM_ANIM = 60;

	// �G�t�F�N�g�̃T�C�Y
	static constexpr int EFECT_SIZE_X = 108;
	static constexpr int EFECT_SIZE_Y = 116;

	// �G�t�F�N�g�̕�����
	static constexpr int EFFECT_NUM_X = 10;
	static constexpr int EFFECT_NUM_Y = 8;

	// �e�̏��
	enum class STATE
	{
		NONE,
		SHOT,
		BLAST,
		END
	};

	// �R���X�g���N�^
	MeteorChild(int* imgs, int imgNum);

	// �f�X�g���N�^
	~MeteorChild(void);

	// 覐΂̐���(覐΂̐i�s�����A�\���J�n���W)
	void CreateShot(Vector2 pos, Vector2F dir);

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
	Vector2 GetMeteorPos(void);

	// ��������̐ݒ�
	void SetAlive(bool alive);

	// �����J�n
	void Blast(Vector2F pos);

private:

	// �v���C���[
	std::vector<Player*> players_;

	// �e�̏��
	STATE state_;

	// ����
	Vector2F dir_;

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

	// ��������
	bool isAlive_;

	// 覐΂̈ړ����x
	float speed_;

	// �f�o�b�O�`��
	void DrawDebug(void);

	// �e�������郉�C��
	int deathLine_;
	
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

