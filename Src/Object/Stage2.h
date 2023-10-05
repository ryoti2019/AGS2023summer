#pragma once
#include "../Common/Vector2.h"

class GameScene4;

class Stage2
{

public:

	// �X�e�[�W�摜�̉��̕�����
	static constexpr int NUM_MAP_CHIPS_X = 32;

	// �X�e�[�W�摜�̏c�̕�����
	static constexpr int NUM_MAP_CHIPS_Y = 24;

	// �X�e�[�W�摜�̕�������
	static constexpr int
		NUM_MAP_CHIPS = NUM_MAP_CHIPS_X * NUM_MAP_CHIPS_Y;

	// �}�b�v�`�b�v�T�C�Y
	static constexpr int CHIP_SIZE_X = 32;
	static constexpr int CHIP_SIZE_Y = 32;

	// �}�b�v�̍ő�T�C�Y
	static constexpr int MAP_MAX_SIZE_X = 32;
	static constexpr int MAP_MAX_SIZE_Y = 20;

	// �R���X�g���N�^
	Stage2(void);

	// �f�X�g���N�^
	~Stage2(void);

	void Init(GameScene4* scene);
	void Update(void);
	void Draw(void);
	void Release(void);

	// �O���t�@�C�����珰�E�ǂ̃X�e�[�W�f�[�^��ǂݍ���
	void LoadCsvStageData(void);

	// �O���t�@�C�����珰�E�ǂ̏Փ˂̃X�e�[�W�f�[�^��ǂݍ���
	void LoadCsvCollisionStageData(void);

	// �O���t�@�C������g�Q���̃X�e�[�W�f�[�^��ǂݍ���
	void LoadCsvSpinaHoleData(void);

	// �O���t�@�C������g�Q���̃X�e�[�W�f�[�^��ǂݍ���
	void LoadCsvSpinaLeftData(void);

	// �O���t�@�C������g�Q�E�̃X�e�[�W�f�[�^��ǂݍ���
	void LoadCsvSpinaRightData(void);

	// �X�e�[�W�̏Փ˗p�̃`�b�v�ԍ����擾����
	int GetCollisionStageNo(Vector2 mapPos);

private:

	// �Q�[���V�[���̃|�C���^�ϐ�
	GameScene4* gameScene_;

	// �}�b�v�摜
	int imgMapChips_[NUM_MAP_CHIPS];

	// �g�p���Ă���}�b�v�̃T�C�Y
	Vector2 usedMapSize_;

	// ���E�ǂ̃}�b�v
	int StageMap_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// ���E�ǂ̏Փ˂̃}�b�v
	int CollisionStageMap_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// �g�Q�̃}�b�v
	int SpinaHoleMap_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// �g�Q���̃}�b�v
	int SpinaLeftMap_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// �g�Q���̃}�b�v
	int SpinaRightMap_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

};

