#pragma once
#include "SceneBase.h"
#include "../Manager/InputManager.h"
class SceneManager;

class SelectScene : public SceneBase
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
		BATTLE = 1,
		GAME = 2,
		MAX = 3
	};

	// コンストラクタ
	SelectScene(void);

	// デストラクタ
	~SelectScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	SceneManager* sceneManager_;

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

	// 背景
	int bgImage_;

	// 背景の座標
	Vector2 bgImagePos01_;
	Vector2 bgImagePos02_;

	// 連戦モードの画像
	int rennsennImage_;

	// ミニゲームモードの画像
	int miniGameImage_;

	// 連戦モードのフラグ
	bool isRennsennMode_;

	// ミニゲームモードの画像
	bool isMiniGameMode_;

	// 遊びたいモードを選んでねの画像
	int asobitaiImage_;

	// BGM
	int bgm_;

	// 決定音
	int decideSE_;

	// 選択音
	int selectSE_;

	// 戻るボタン
	int backImage_;
	int bottonAImage_;

	// 決定ボタン
	int nextImage_;
	int bottonBImage_;

	// 入力された総数
	int inputNum_;

};

