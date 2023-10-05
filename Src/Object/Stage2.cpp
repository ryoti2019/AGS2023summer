#include<string>
#include <fstream>
#include <sstream>
#include <DxLib.h>
#include "../Utility/AsoUtility.h"
#include "../Utility/Application.h"
#include "../Scene/GameScene4.h"
#include "Stage2.h"
#include "Player4.h"
Stage2::Stage2(void)
{
}

Stage2::~Stage2(void)
{
}

void Stage2::Init(GameScene4* scene)
{

	// �Q�[���V�[���̋@�\�����ł��g����悤�Ƀ����o�ϐ��Ɋi�[
	gameScene_ = scene;

	// �������ꂽ�摜��ǂݍ���
	LoadDivGraph("Data/Image/Stage/FD_Dungeon_Free.png",
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

	// �O���t�@�C������g�Q���̃X�e�[�W�f�[�^��ǂݍ���
	LoadCsvSpinaHoleData();

	// �O���t�@�C������g�Q���̃X�e�[�W�f�[�^��ǂݍ���
	LoadCsvSpinaLeftData();

	// �O���t�@�C������g�Q�E�̃X�e�[�W�f�[�^��ǂݍ���
	LoadCsvSpinaRightData();

	// �O���t�@�C������Փ˃X�e�[�W�f�[�^��ǂݍ���
	LoadCsvCollisionStageData();

}

void Stage2::Update(void)
{
}

void Stage2::Draw(void)
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

			// �g�Q��
			chipNo = SpinaHoleMap_[y][x];
			imgHandle = imgMapChips_[chipNo];
			DrawGraph(x * CHIP_SIZE_X, y * CHIP_SIZE_Y, imgHandle, true);

			// �g�Q��
			if (gameScene_->GetCnt() >= 300 && gameScene_->GetCnt() <= 360 && gameScene_->GetL())
			{
				chipNo = SpinaLeftMap_[y][x];
				imgHandle = imgMapChips_[chipNo];
				DrawGraph(x * CHIP_SIZE_X, y * CHIP_SIZE_Y, imgHandle, true);
			}


			// �g�Q�E
			if (gameScene_->GetCnt() >= 300 && gameScene_->GetCnt() <= 360 && gameScene_->GetR())
			{
				chipNo = SpinaRightMap_[y][x];
				imgHandle = imgMapChips_[chipNo];
				DrawGraph(x * CHIP_SIZE_X, y * CHIP_SIZE_Y, imgHandle, true);
			}
		}
	}

}

void Stage2::Release(void)
{

	// �ǂݍ��񂾉摜�̊J��
	for (int i = 0; i < NUM_MAP_CHIPS; i++)
	{
		DeleteGraph(imgMapChips_[i]);
	}

}

void Stage2::LoadCsvStageData(void)
{

	std::ifstream ifs = std::ifstream("Data/Image/Stage/stage2_���E��.csv");
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

void Stage2::LoadCsvSpinaHoleData(void)
{

	std::ifstream ifs = std::ifstream("Data/Image/Stage/stage2_�g�Q��.csv");
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
			SpinaHoleMap_[y][x] = -1;
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
			SpinaHoleMap_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage2::LoadCsvSpinaLeftData(void)
{

	std::ifstream ifs = std::ifstream("Data/Image/Stage/stage2_�g�Q��.csv");
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
			SpinaLeftMap_[y][x] = -1;
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
			SpinaLeftMap_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage2::LoadCsvSpinaRightData(void)
{

	std::ifstream ifs = std::ifstream("Data/Image/Stage/stage2_�g�Q�E.csv");
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
			SpinaRightMap_[y][x] = -1;
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
			SpinaRightMap_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage2::LoadCsvCollisionStageData(void)
{

	std::ifstream ifs = std::ifstream("Data/Image/Stage/stage2_�Փ˔���.csv");
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

int Stage2::GetCollisionStageNo(Vector2 mapPos)
{

	int ret = CollisionStageMap_[mapPos.y][mapPos.x];

	return ret;

}
