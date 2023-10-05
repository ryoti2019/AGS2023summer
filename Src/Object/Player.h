#pragma once
#include "../Utility/AsoUtility.h"
#include "../Common/Vector2.h"
#include "../Manager/InputManager.h"

class GameScene;
class Meteor;

class Player
{

public:

	// プレイヤーの最大アニメーション
	static constexpr int PLAYER_MAX_NUM_ANIM = 3;

	// プレイヤーのサイズ
	static constexpr int PLAYER_SIZE_X = 100;
	static constexpr int PLAYER_SIZE_Y = 100;

	// プレイヤーの縦横の分割数
	static constexpr int NUM_X = 3;
	static constexpr int NUM_Y = 4;

	// バリアのサイズ
	static constexpr int SIZE_X = 100;
	static constexpr int SIZE_Y = 100;

	// コンストラクタ
	Player();

	// デストラクタ
	~Player(void);

	void Init(GameScene* scene, InputManager::JOYPAD_NO playerNo);
	void Update(void);
	void Draw(void);
	void Release(void);

	// HPのゲッター
	int GetHP(void);

	// HPのゲッター
	void SetHP(int hp);

	// 座標の取得
	Vector2 GetPos(void);

	// 座標のセッター
	void SetPos(Vector2 pos);

	// 生存判定の取得
	bool IsAlive(void);

	// 生存判定の設定
	void SetAlive(bool alive);

	// １個前の生存判定の取得
	bool OldAlive(void);

	// 下ボタンの押下判定
	bool GetButton(void);

	// スタート時の入力状態
	bool GetInputStart(void);

	// 次へ進むときの入力状態
	bool GetInputPlayer(void);

	// ランダムの数字を取得
	int GetRandNumber(void);

	// ランダムの数字を設定する
	void SetRandNumber(int rand);

	// 復活後ボタンを押したかの判定
	bool GetInputRevival(void);

private:

	// ゲームシーンのポインタ変数
	GameScene* gameScene_;

	// プレイヤー
	std::vector<Player*> players_;

	// プレイヤーの画像
	int playerImage_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM];

	// プレイヤーの死亡画像
	int playerDeathImage;

	// プレイヤーのUI
	int playerUIImage_;

	// バリアの画像
	int barrierImage_;

	// プレイヤーの座標
	Vector2 pos_;

	// 方向
	AsoUtility::DIR dir_;

	// アニメーションのデータ
	int animData_[4];

	// アニメーションのカウント
	int cntAnim_;

	// アニメーションスピード
	float speedAnim_;

	// 生存判定
	bool isAlive_;
	
	// 1個前の生存フラグ
	bool oldAlive_;

	// 点滅判定
	bool isBlink_;

	// ボタンの押下判定
	bool button_;

	// 体力
	float hp_;

	// 体力最大値
	float hpMax_;

	// ゲームパッドの番号
	InputManager::JOYPAD_NO padNo_;

	// デバッグ描画
	void DrawDebug(void);

	// バリアの展開音
	int barrierSE_;

	// プレイヤーごとに入力したか
	bool inputPlayer_;

	// プレイヤーがOKボタンを押したときの音
	int playerDecideSE_;

	// 死んだときの音
	int deathSE_;

	// 決定音
	int decideSE_;

	// 死んだときの音のフラグ
	bool death_;

	// スタート時の入力状態
	bool inputStart_;

	// １個前の生存フラグを保持しておく時間
	int aliveCnt_;

	// 復活した後の入力
	bool inputRevival_;

	// ランダムで出た数
	int randNumber_;

};


