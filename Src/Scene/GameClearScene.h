#pragma once
#include "SceneBase.h"

class GameClearScene : public SceneBase

{
public:

	// コンストラクタ
	GameClearScene(void);

	// デストラクタ
	~GameClearScene(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	// ゲームオーバー画像
	int imgGameClear_;

};

