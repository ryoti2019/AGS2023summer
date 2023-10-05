#pragma once
#include "../Common/Vector2.h"
class GameScene2;

class Stage
{

public:

	// �X�e�[�W�摜�̉��̕�����
	static constexpr int NUM_MAP_CHIPS_X = 16;

	// �X�e�[�W�摜�̏c�̕�����
	static constexpr int NUM_MAP_CHIPS_Y = 14;

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
	Stage(void);

	// �f�X�g���N�^
	~Stage(void);

	void Init(GameScene2* scene);
	void Update(void);
	void Draw(void);
	void Release(void);

	// �O���t�@�C�����珰�E�ǂ̃X�e�[�W�f�[�^��ǂݍ���
	void LoadCsvStageData(void);

	// �O���t�@�C������I�u�W�F�N�g�̃X�e�[�W�f�[�^��ǂݍ���
	void LoadCsvObjectData(void);

	// �O���t�@�C�����珰�E�ǂ̏Փ˂̃X�e�[�W�f�[�^��ǂݍ���
	void LoadCsvCollisionStageData(void);

	// �X�e�[�W�̏Փ˗p�̃`�b�v�ԍ����擾����
	int GetCollisionStageNo(Vector2 mapPos);

private:

	// �Q�[���V�[���̃|�C���^�ϐ�
	GameScene2* gameScene_;

	// �}�b�v�摜
	int imgMapChips_[NUM_MAP_CHIPS];

	// �g�p���Ă���}�b�v�̃T�C�Y
	Vector2 usedMapSize_;

	// ���E�ǂ̃}�b�v
	int StageMap_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// �I�u�W�F�N�g�̃}�b�v
	int ObjectMap_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// ���E�ǂ̏Փ˂̃}�b�v
	int CollisionStageMap_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

};