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

	// ゲームシーンの機能をいつでも使えるようにメンバ変数に格納
	gameScene_ = scene;

	// 分割された画像を読み込む
	LoadDivGraph("Data/Image/Stage/FD_Dungeon_Free.png",
		NUM_MAP_CHIPS,
		NUM_MAP_CHIPS_X,
		NUM_MAP_CHIPS_Y,
		CHIP_SIZE_X,
		CHIP_SIZE_Y,
		&imgMapChips_[0]
	);

	// マップのサイズを設定する
	usedMapSize_.x = MAP_MAX_SIZE_X;
	usedMapSize_.y = MAP_MAX_SIZE_Y;

	// 外部ファイルから床・壁ステージデータを読み込む
	LoadCsvStageData();

	// 外部ファイルからトゲ穴のステージデータを読み込む
	LoadCsvSpinaHoleData();

	// 外部ファイルからトゲ左のステージデータを読み込む
	LoadCsvSpinaLeftData();

	// 外部ファイルからトゲ右のステージデータを読み込む
	LoadCsvSpinaRightData();

	// 外部ファイルから衝突ステージデータを読み込む
	LoadCsvCollisionStageData();

}

void Stage2::Update(void)
{
}

void Stage2::Draw(void)
{

	// マップ表示
	for (int y = 0; y < usedMapSize_.y; y++)
	{
		for (int x = 0; x < usedMapSize_.x; x++)
		{

			// 床・壁
			int chipNo = StageMap_[y][x];
			int imgHandle = imgMapChips_[chipNo];
			DrawGraph(x * CHIP_SIZE_X, y * CHIP_SIZE_Y, imgHandle, true);

			// トゲ穴
			chipNo = SpinaHoleMap_[y][x];
			imgHandle = imgMapChips_[chipNo];
			DrawGraph(x * CHIP_SIZE_X, y * CHIP_SIZE_Y, imgHandle, true);

			// トゲ左
			if (gameScene_->GetCnt() >= 300 && gameScene_->GetCnt() <= 360 && gameScene_->GetL())
			{
				chipNo = SpinaLeftMap_[y][x];
				imgHandle = imgMapChips_[chipNo];
				DrawGraph(x * CHIP_SIZE_X, y * CHIP_SIZE_Y, imgHandle, true);
			}


			// トゲ右
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

	// 読み込んだ画像の開放
	for (int i = 0; i < NUM_MAP_CHIPS; i++)
	{
		DeleteGraph(imgMapChips_[i]);
	}

}

void Stage2::LoadCsvStageData(void)
{

	std::ifstream ifs = std::ifstream("Data/Image/Stage/stage2_床・壁.csv");
	if (!ifs)
	{
		// エラーが発生
		return;
	}

	// 地上データの初期化
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			StageMap_[y][x] = -1;
		}
	}

	// ファイルを1行ずつ読み込んで、lineに格納する
	std::string line;					// １行の文字列情報
	std::vector < std::string> split;	// １行の文字列情報
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// ファイルを１行ずつ読み込む
	while (getline(ifs, line))
	{

		// 1行分の文字列をカンマ区切りで分割
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string型からint型に変換
			chipNo = stoi(split[x]);

			// ２次元配列にマップチップ番号を格納
			StageMap_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage2::LoadCsvSpinaHoleData(void)
{

	std::ifstream ifs = std::ifstream("Data/Image/Stage/stage2_トゲ穴.csv");
	if (!ifs)
	{
		// エラーが発生
		return;
	}

	// 地上データの初期化
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			SpinaHoleMap_[y][x] = -1;
		}
	}

	// ファイルを1行ずつ読み込んで、lineに格納する
	std::string line;					// １行の文字列情報
	std::vector < std::string> split;	// １行の文字列情報
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// ファイルを１行ずつ読み込む
	while (getline(ifs, line))
	{

		// 1行分の文字列をカンマ区切りで分割
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string型からint型に変換
			chipNo = stoi(split[x]);

			// ２次元配列にマップチップ番号を格納
			SpinaHoleMap_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage2::LoadCsvSpinaLeftData(void)
{

	std::ifstream ifs = std::ifstream("Data/Image/Stage/stage2_トゲ左.csv");
	if (!ifs)
	{
		// エラーが発生
		return;
	}

	// 地上データの初期化
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			SpinaLeftMap_[y][x] = -1;
		}
	}

	// ファイルを1行ずつ読み込んで、lineに格納する
	std::string line;					// １行の文字列情報
	std::vector < std::string> split;	// １行の文字列情報
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// ファイルを１行ずつ読み込む
	while (getline(ifs, line))
	{

		// 1行分の文字列をカンマ区切りで分割
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string型からint型に変換
			chipNo = stoi(split[x]);

			// ２次元配列にマップチップ番号を格納
			SpinaLeftMap_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage2::LoadCsvSpinaRightData(void)
{

	std::ifstream ifs = std::ifstream("Data/Image/Stage/stage2_トゲ右.csv");
	if (!ifs)
	{
		// エラーが発生
		return;
	}

	// 地上データの初期化
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			SpinaRightMap_[y][x] = -1;
		}
	}

	// ファイルを1行ずつ読み込んで、lineに格納する
	std::string line;					// １行の文字列情報
	std::vector < std::string> split;	// １行の文字列情報
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// ファイルを１行ずつ読み込む
	while (getline(ifs, line))
	{

		// 1行分の文字列をカンマ区切りで分割
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string型からint型に変換
			chipNo = stoi(split[x]);

			// ２次元配列にマップチップ番号を格納
			SpinaRightMap_[y][x] = chipNo;

		}

		y++;
	}

}

void Stage2::LoadCsvCollisionStageData(void)
{

	std::ifstream ifs = std::ifstream("Data/Image/Stage/stage2_衝突判定.csv");
	if (!ifs)
	{
		// エラーが発生
		return;
	}

	// 地上データの初期化
	for (int y = 0; y < MAP_MAX_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_MAX_SIZE_X; x++)
		{
			CollisionStageMap_[y][x] = -1;
		}
	}

	// ファイルを1行ずつ読み込んで、lineに格納する
	std::string line;					// １行の文字列情報
	std::vector < std::string> split;	// １行の文字列情報
	int x = 0;
	int y = 0;
	int chipNo = 0;

	// ファイルを１行ずつ読み込む
	while (getline(ifs, line))
	{

		// 1行分の文字列をカンマ区切りで分割
		split = AsoUtility::Split(line, ',');

		for (int x = 0; x < split.size(); x++)
		{

			// string型からint型に変換
			chipNo = stoi(split[x]);

			// ２次元配列にマップチップ番号を格納
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
