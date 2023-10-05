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

	// ゲームシーンの機能をいつでも使えるようにメンバ変数に格納
	gameScene_ = scene;

	// 分割された画像を読み込む
	LoadDivGraph("Data/Image/Stage/stage.png",
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

	// 外部ファイルからオブジェクトステージデータを読み込む
	LoadCsvObjectData();

	// 外部ファイルから衝突ステージデータを読み込む
	LoadCsvCollisionStageData();

}

void Stage::Update(void)
{
}

void Stage::Draw(void)
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

			// オブジェクト
			chipNo = ObjectMap_[y][x];
			imgHandle = imgMapChips_[chipNo];

			DrawGraph(x * CHIP_SIZE_X, y * CHIP_SIZE_Y, imgHandle, true);

		}
	}

}

void Stage::Release(void)
{

	// 読み込んだ画像の開放
	for (int i = 0; i < NUM_MAP_CHIPS; i++)
	{
		DeleteGraph(imgMapChips_[i]);
	}

}

void Stage::LoadCsvStageData(void)
{

	std::ifstream ifs = std::ifstream("Data/Image/Stage/stage_地面・海.csv");
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

void Stage::LoadCsvObjectData(void)
{

	std::ifstream ifs = std::ifstream("Data/Image/Stage/stage_柵.csv");
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
			ObjectMap_[y][x] = -1;
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
			ObjectMap_[y][x] = chipNo;

		}
		y++;
	}

}

void Stage::LoadCsvCollisionStageData(void)
{

	std::ifstream ifs = std::ifstream("Data/Image/Stage/stage_衝突判定.csv");
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

int Stage::GetCollisionStageNo(Vector2 mapPos)
{

	int ret = CollisionStageMap_[mapPos.y][mapPos.x];

	return ret;

}
