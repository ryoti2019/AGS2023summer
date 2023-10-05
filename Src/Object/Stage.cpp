#include<string>
#include <fstream>
#include <sstream>
#include <DxLib.h>
#include "../Utility/AsoUtility.h"
#include "../Utility/Application.h"
#include "../Scene/GameScene2.h"
#include "Stage.h"
#include "Player2.h"

Stage::Stage(void)
{
}

Stage::~Stage(void)
{
}

void Stage::Init(GameScene2* scene)
{

	// �Q�[���V�[���̋@�\�����ł��g����悤�Ƀ����o�ϐ��Ɋi�[
	gameScene_ = scene;

	// �������ꂽ�摜��ǂݍ���
	LoadDivGraph("Data/Image/Stage/stage.png",
		NUM_MAP_CHIPS,
		NUM_MAP_CHIPS_X,
		NUM_MAP_CHIPS_Y,
		CHIP_SIZE_X,
		CHIP_SIZE_Y,
		&imgMapChips_[0]
	);

	// �}�b�v�̃T�C�Y��ݒ肷��
	usedMapSize_.x = MAP_MAX_SIZE_X;
	usedMapSize_.y = MAP_MAX_SIZE_Y;

	// �O���t�@�C�����珰�E�ǃX�e�[�W�f�[�^��ǂݍ���
	LoadCsvStageData();

	// �O���t�@�C������I�u�W�F�N�g�X�e�[�W�f�[�^��ǂݍ���
	LoadCsvObjectData();

	// �O���t�@�C������Փ˃X�e�[�W�f�[�^��ǂݍ���
	LoadCsvCollisionStageData();

}

void Stage::Update(void)
{
}

void Stage::Draw(void)
{

	// �}�b�v�\��
	for (int y = 0; y < usedMapSize_.y; y++)
	{
		for (int x = 0; x < usedMapSize_.x; x++)
		{

			// ���E��
			int chipNo = StageMap_[y][x];

			int imgHandle = imgMapChips_[chipNo];

			DrawGraph(x * CHIP_SIZE_X, y * CHIP_SIZE_Y, imgHandle, true);

			// �I�u�W�F�N�g
			chipNo = ObjectMap_[y][x];
			imgHandle = imgMapChips_[chipNo];

			DrawGraph(x * CHIP_SIZE_X, y * CHIP_SIZE_Y, imgHandle, true);

		}
	}

}

void Stage::Release(void)
{

	// �ǂݍ��񂾉摜�̊J��
	for (int i = 0; i < NUM_MAP_CHIPS; i++)
	{
		DeleteGraph(imgMapChips_[i]);
	}

}

void Stage::LoadCsvStageData(void)
{

	std::ifstream ifs = std::ifstream("Data/Image/Stage/stage_�n�ʁE�C.csv");
	if (!ifs)
	{
		// �G���[������
		return;
	}

	// �n��f�[�^�̏�����
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			StageMap_[y][x] = -1;
		}
	}

	// �t�@�C����1�s���ǂݍ���ŁAline�Ɋi�[����
	std::string line;					// �P�s�̕�������
	std::vector < std::string> split;	// �P�s�̕�������
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// �t�@�C�����P�s���ǂݍ���
	while (getline(ifs, line))
	{

		// 1�s���̕�������J���}��؂�ŕ���
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string�^����int�^�ɕϊ�
			chipNo = stoi(split[x]);

			// �Q�����z��Ƀ}�b�v�`�b�v�ԍ����i�[
			StageMap_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage::LoadCsvObjectData(void)
{

	std::ifstream ifs = std::ifstream("Data/Image/Stage/stage_��.csv");
	if (!ifs)
	{
		// �G���[������
		return;
	}

	// �n��f�[�^�̏�����
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			ObjectMap_[y][x] = -1;
		}
	}

	// �t�@�C����1�s���ǂݍ���ŁAline�Ɋi�[����
	std::string line;					// �P�s�̕�������
	std::vector < std::string> split;	// �P�s�̕�������
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// �t�@�C�����P�s���ǂݍ���
	while (getline(ifs, line))
	{

		// 1�s���̕�������J���}��؂�ŕ���
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string�^����int�^�ɕϊ�
			chipNo = stoi(split[x]);

			// �Q�����z��Ƀ}�b�v�`�b�v�ԍ����i�[
			ObjectMap_[y][x] = chipNo;

		}
		y++;
	}

}

void Stage::LoadCsvCollisionStageData(void)
{

	std::ifstream ifs = std::ifstream("Data/Image/Stage/stage_�Փ˔���.csv");
	if (!ifs)
	{
		// �G���[������
		return;
	}

	// �n��f�[�^�̏�����
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			CollisionStageMap_[y][x] = -1;
		}
	}

	// �t�@�C����1�s���ǂݍ���ŁAline�Ɋi�[����
	std::string line;					// �P�s�̕�������
	std::vector < std::string> split;	// �P�s�̕�������
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// �t�@�C�����P�s���ǂݍ���
	while (getline(ifs, line))
	{
		// 1�s���̕�������J���}��؂�ŕ���
		split = AsoUtility::Split(line, ',');
		for (int x = 0; x < split.size(); x++)
		{

			// string�^����int�^�ɕϊ�
			chipNo = stoi(split[x]);

			// �Q�����z��Ƀ}�b�v�`�b�v�ԍ����i�[
			CollisionStageMap_[y][x] = chipNo;

		}
		y++;
	}

}

int Stage::GetCollisionStageNo(Vector2 mapPos)
{

	int ret = CollisionStageMap_[mapPos.y][mapPos.x];

	return ret;

}
