#pragma once
#include "SceneBase.h"
#include "../Manager/InputManager.h"
class GameSelectScene : public SceneBase

{

public:

	// スクロール速度
	static constexpr int SCROLL_POW = 2;

	// 背景のサイズ
	static constexpr int BG_SIZE_X = 2048;
	static constexpr int BG_SIZE_Y = 640;

	// ゲームの種類
	enum class GAME_TYPE
	{
		GAME = 1,
		GAME2 = 2,
		GAME3 = 3,
		GAME4 = 4,
		GAME5 = 5,
		MAX
	};

	// コンストラクタ
	GameSelectScene(void);

	// デストラクタ
	~GameSelectScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	// 画像
	int imgSelect_;

	// 座標
	Vector2 pos2_;
	Vector2 pos3_;
	Vector2 pos4_;

	// ゲームのナンバー
	int gameNo_;

	// Lスティックが倒されたか
	bool stickL_;

	// ゲームパッドの番号
	InputManager::JOYPAD_NO padNo_;

	void GameSelect(void);

	// BGM
	int bgm_;

	// 決定音
	int decideSE_;

	// 選択音
	int selectSE_;

	// 背景
	int bgImage_;

	// 背景の座標
	Vector2 bgImagePos01_;
	Vector2 bgImagePos02_;

	// ゲームの画像
	int game1Image_;
	int game2Image_;
	int game3Image_;
	int game4Image_;
	int game5Image_;

	// ゲームのタイトル画像
	int game1TitleImage_;
	int game2TitleImage_;
	int game3TitleImage_;
	int game4TitleImage_;
	int game5TitleImage_;

	// 遊びたいゲームを選んでねの画像
	int gameSelectImage_;

};

