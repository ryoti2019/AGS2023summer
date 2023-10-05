#pragma once
#include <vector>
#include "../Manager/InputManager.h"
#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"
#include "RockChild.h"

class GameScene3;

class Rock
{

public:

	// 岩を壊す数
	static constexpr int ROCK_NUM = 100;

	// 岩のサイズ
	static constexpr int SIZE_X = 64;
	static constexpr int SIZE_Y = 64;

	// コンストラクタ
	Rock(int img);

	// デストラクタ
	~Rock(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	// 座標の取得
	Vector2 GetPos(void);

	// 座標の設定
	void SetPos(Vector2 pos);

	// 生存フラグの取得
	bool IsAlive(void);

	// 生存フラグの設定
	void SetAlive(bool isAlive);

	// Shotの取得
	std::vector<RockChild*> GetRockChild(void);

	// 岩を壊したら足す
	void AddCnt(int i);

	// 岩を壊した数の取得
	int GetRockCount(void);

private:

	// 隕石の子
	std::vector<RockChild*> children_;

	// 座標
	Vector2 pos_;

	// 岩の画像
	int image_;

	// 生存フラグ
	bool isAlive_;

	int cnt_;

	// 岩を壊した数
	int rockConter_;

};

