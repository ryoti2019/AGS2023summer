#pragma once
#include "../Scene/GameScene.h"
#include "../Utility/AsoUtility.h"
#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"

class RockChild
{

public:

	// 岩を壊す数
	static constexpr int ROCK_NUM = 100;

	// 岩のサイズ
	static constexpr int SIZE_X = 32;
	static constexpr int SIZE_Y = 32;

	// コンストラクタ
	RockChild(int img);

	// デストラクタ
	~RockChild(void);

	// 岩の生成
	void CreateRock(Vector2 pos);

	void Update(void);

	void Draw(void);

	void Release(void);

	// 生存判定
	bool IsAlive(void);

	// 座標の取得
	Vector2 GetPos(void);

	// 生存判定の設定
	void SetAlive(bool alive);

private:

	// 方向
	Vector2F dir_;

	// 座標
	Vector2 pos_;

	// 岩の画像
	int image_;

	// 生存判定
	bool isAlive_;



};

