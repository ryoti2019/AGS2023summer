#pragma once
#include "SceneBase.h"
#include "../Common/Vector2F.h"
#include "../Utility/AsoUtility.h"

class SceneManager;
class Player;
class Meteor;
class MeteorChild;
class StartMes;
class ResultScene;

class GameScene : public SceneBase
{

public:

	// 覐΂̍ő�A�j���[�V����
	static constexpr int METEOR_MAX_NUM_ANIM = 3;

	// 覐΂̃T�C�Y
	static const int METEOR_SIZE_X = 64; // ���T�C�Y
	static const int METEOR_SIZE_Y = 64; // �c�T�C�Y

	// �e���ˌ�̍d������
	static constexpr float SHOT_DELAY = 1.0f;

	// B�{�^���̍ő�A�j���[�V����
	static constexpr int BOTTON_MAX_NUM_ANIM = 4;

	// B�{�^���̃T�C�Y
	static constexpr int BOTTON_SIZE_X = 32;
	static constexpr int BOTTON_SIZE_Y = 32;

	// �{�^���̏c���̕�����
	static constexpr int BOTTON_NUM_X = 4;
	static constexpr int BOTTON_NUM_Y = 1;

	// �G�t�F�N�g�̍ő�A�j���[�V����
	static constexpr int EFFECT_MAX_NUM_ANIM = 60;

	// �G�t�F�N�g�̃T�C�Y
	static constexpr int EFECT_SIZE_X = 108;
	static constexpr int EFECT_SIZE_Y = 116;

	// �G�t�F�N�g�̕�����
	static constexpr int EFFECT_NUM_X = 10;
	static constexpr int EFFECT_NUM_Y = 8;

	// �R���X�g���N�^
	GameScene(void);

	// �f�X�g���N�^
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	// ���U���g�̎擾
	bool GetResult(void);

	// �X�L�b�v�̎擾
	bool GetSkip(void);

	// �X�^�[�g�̏��
	bool IsStart(void);

	void SetInputNum(int input);

	void SetStartNum(int start);

	bool GetRevival(void);

private:

	// �V�[���̊Ǘ�
	SceneManager* sceneManager_;

	// �v���C���[
	std::vector<Player*> players_;
	
	// 覐�
	std::vector<Meteor*> meteors_;

	// ���U���g
	ResultScene* resultScene_;

	// 覐΂̉摜
	int meteorImage_[METEOR_MAX_NUM_ANIM];

	// �X�^�[�g���b�Z�[�W
	StartMes* startMes_;

	// �w�i�摜
	int bgImage_;

	// �Փ˔���
	void Collision(void);

	// �Փ˔���
	bool IsCollisionRect(Vector2 stPos1, Vector2 edPos1, Vector2 stPos2, Vector2 edPos2);

	// �Փ˔���
	bool IsCollisionRectCenter(Vector2 centerPos1, Vector2 size1, Vector2 centerPos2, Vector2 size2);

	// �Q�[�������p�̉摜
	int expImage_;

	// �Q�[���������X�L�b�v���邽�߂̃t���O
	bool skip_;

	// �_���[�W��H��������̉�
	int damageSE_;

	// ���艹
	int decideSE_;

	// BGM
	int bgm_;

	// �����c��̉摜
	int ikinokore_;

	// B�{�^���̉摜
	int BbottonImage_[BOTTON_MAX_NUM_ANIM];

	// �A�j���[�V�����̃J�E���^
	int cntAnim_;

	// �����������̃G�t�F�N�g
	int hitEffectImage_[EFFECT_MAX_NUM_ANIM];

	// �A�j���[�V�����X�s�[�h
	float speedAnim_;

	// ���U���g
	void Result(void);

	// ���U���g�̃t���O
	bool result_;

	// �����摜
	int winImage1_;
	int winImage2_;
	int winImage3_;
	int winImage4_;

	// ���͂��ꂽ����
	int inputNum_;

	// �v���C���[���Ƃɓ��͂�����
	bool inputPlayer1_;
	bool inputPlayer2_;
	bool inputPlayer3_;
	bool inputPlayer4_;

	// �X�^�[�g�̉摜
	int startImage_;

	// �X�^�[�g���邽�߂̓���
	int startNum_;

	bool isStart_;

	// �v���C���[��OK�摜�̓ǂݍ���
	int OKImage1_;
	int OKImage2_;
	int OKImage3_;
	int OKImage4_;

	// ���������Ƃ��̃t���O
	bool revival_;

	// ���������Ƃ���HP�𑝂₷�t���O
	bool revivalHP_;

	// �����_���ɐ�����1��I��
	bool isRand1_;
	bool isRand2_;
	bool isRand3_;
	bool isRand4_;

	// �����_���Ɍ��܂������̑���
	int inputRandNum_;

	// �����_��
	void Rand(void);

	// �S���̃T�C�R���̉摜
	int allDice_[6];

	// 1���̃T�C�R���̉摜
	int dice1_;
	int dice2_;
	int dice3_;
	int dice4_;
	int dice5_;
	int dice6_;

	// �T�C�R����U��
	int saikoro_;

	// �������Ƃ������𑫂�
	bool win_;

};