#pragma once
#include "../Common/Vector2.h"

class GameScene4;

class Stage2
{

public:

	// ステージ画像の横の分割数
	static constexpr int NUM_MAP_CHIPS_X = 32;

	// ステージ画像の縦の分割数
	static constexpr int NUM_MAP_CHIPS_Y = 24;

	// ステージ画像の分割総数
	static constexpr int
		NUM_MAP_CHIPS = NUM_MAP_CHIPS_X * NUM_MAP_CHIPS_Y;

	// マップチップサイズ
	static constexpr int CHIP_SIZE_X = 32;
	static constexpr int CHIP_SIZE_Y = 32;

	// マップの最大サイズ
	static constexpr int MAP_MAX_SIZE_X = 32;
	static constexpr int MAP_MAX_SIZE_Y = 20;

	// コンストラクタ
	Stage2(void);

	// デストラクタ
	~Stage2(void);

	void Init(GameScene4* scene);
	void Update(void);
	void Draw(void);
	void Release(void);

	// 外部ファイルから床・壁のステージデータを読み込む
	void LoadCsvStageData(void);

	// 外部ファイルから床・壁の衝突のステージデータを読み込む
	void LoadCsvCollisionStageData(void);

	// 外部ファイルからトゲ穴のステージデータを読み込む
	void LoadCsvSpinaHoleData(void);

	// 外部ファイルからトゲ左のステージデータを読み込む
	void LoadCsvSpinaLeftData(void);

	// 外部ファイルからトゲ右のステージデータを読み込む
	void LoadCsvSpinaRightData(void);

	// ステージの衝突用のチップ番号を取得する
	int GetCollisionStageNo(Vector2 mapPos);

private:

	// ゲームシーンのポインタ変数
	GameScene4* gameScene_;

	// マップ画像
	int imgMapChips_[NUM_MAP_CHIPS];

	// 使用しているマップのサイズ
	Vector2 usedMapSize_;

	// 床・壁のマップ
	int StageMap_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// 床・壁の衝突のマップ
	int CollisionStageMap_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// トゲのマップ
	int SpinaHoleMap_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// トゲ穴のマップ
	int SpinaLeftMap_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

	// トゲ穴のマップ
	int SpinaRightMap_[MAP_MAX_SIZE_Y][MAP_MAX_SIZE_X];

};

