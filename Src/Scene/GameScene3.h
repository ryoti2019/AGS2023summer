#pragma once
#include "SceneBase.h"
#include "../Common/Vector2F.h"
#include "../Utility/AsoUtility.h"

class Player3;
class Stage;
class Shot;
class Rock;
class RockChild;
class StartMes;

class GameScene3 : public SceneBase
{

public:

	// プレイヤーの最大アニメーション
	static constexpr int PLAYER_MAX_NUM_ANIM = 12;

	// プレイヤーのサイズ
	static constexpr int PLAYER_SIZE_X = 32;
	static constexpr int PLAYER_SIZE_Y = 32;

	// プレイヤーの縦横の分割数
	static constexpr int PLAYER_NUM_X = 3;
	static constexpr int PLAYER_NUM_Y = 4;

	// Bボタンの最大アニメーション
	static constexpr int BOTTON_MAX_NUM_ANIM = 4;

	// Bボタンのサイズ
	static constexpr int BOTTON_SIZE_X = 32;
	static constexpr int BOTTON_SIZE_Y = 32;

	// ボタンの縦横の分割数
	static constexpr int BOTTON_NUM_X = 4;
	static constexpr int BOTTON_NUM_Y = 1;

	// コンストラクタ
	GameScene3(void);

	// デストラクタ
	~GameScene3(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	// リザルトの取得
	bool GetResult(void);

	// スキップの取得
	bool GetSkip(void);

	// スタートの状態
	bool IsStart(void);

	void SetInputNum(int input);

	void SetStartNum(int start);

private:

	// プレイヤー
	std::vector<Player3*> players_;

	// 岩
	std::vector<Rock*> rocks_;

	// スタートメッセージ
	StartMes* startMes_;

	// ステージ
	Stage* stage_;

	// プレイヤーの画像
	int playerImg_[PLAYER_MAX_NUM_ANIM];

	// 岩の画像
	int rockImg_;

	// 方向
	Vector2 dir_;

	// 衝突判定
	void Collision(void);

	// 衝突判定
	bool IsCollisionRect(Vector2 stPos1, Vector2 edPos1, Vector2 stPos2, Vector2 edPos2);

	// 衝突判定
	bool IsCollisionRectCenter(Vector2 centerPos1, Vector2 size1, Vector2 centerPos2, Vector2 size2);

	// 背景画像
	int bgImage_;

	// ゲーム説明用の画像
	int expImage_;

	// ゲーム説明をスキップするためのフラグ
	bool skip_;

	// 決定音
	int decideSE_;

	// Bボタンの画像
	int BbottonImage_[BOTTON_MAX_NUM_ANIM];

	// アニメーションのカウンタ
	int cntAnim_;

	// BGM
	int bgm_;

	// 爆発音
	int explosionSE_;

	// 連打しろ
	int renndasiroImage_;

	// リザルト
	void Result(void);

	// リザルトのフラグ
	bool result_;

	// 勝利画像
	int winImage1_;
	int winImage2_;
	int winImage3_;
	int winImage4_;

	// 入力された総数
	int inputNum_;

	// プレイヤーごとに入力したか
	bool inputPlayer1_;
	bool inputPlayer2_;
	bool inputPlayer3_;
	bool inputPlayer4_;

	// スタートの画像
	int startImage_;

	// スタートするための入力
	int startNum_;

	bool isStart_;

	// プレイヤーのOK画像の読み込み
	int OKImage1_;
	int OKImage2_;
	int OKImage3_;
	int OKImage4_;

	// 勝ったとき数字を足す
	bool win_;
};


