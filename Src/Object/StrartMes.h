#pragma once
#include "../Scene/GameScene.h"

class StartMes
{

public:

	static constexpr int SIZE_X = 300;
	static constexpr int SIZE_Y = 200;


	StartMes();
	~StartMes();

	void Init();
	void Update(void);
	void Release(void);
	void Draw(void);

	enum class Mes {
		No3,
		No2,
		No1,
		GO,
		Max
	};

	// スタートメッセージのカウンタ
	int GetCnt(void);

private:

	// ゲームシーンのポインタ変数
	GameScene* gameScene_;

	int count_;
	int imageHdl_[static_cast<int>(Mes::Max)];

	// カウントダウンの音
	int cntDown_;

	// カウントダウンのスタート
	int start_;

};

