#pragma once
#include "../Utility/AsoUtility.h"
#include "../Common/Vector2.h"
#include "../Manager/InputManager.h"
#include "../Scene/GameScene2.h"

class Shot;

class Player2
{

public:


	// プレイヤーの最大アニメーション
	static constexpr int PLAYER_MAX_NUM_ANIM = 3;

	// プレイヤーのサイズ
	static constexpr int PLAYER_SIZE_X = 32;
	static constexpr int PLAYER_SIZE_Y = 32;

	// プレイヤーの縦横の分割数
	static constexpr int NUM_X = 3;
	static constexpr int NUM_Y = 4;


	// 弾の最大アニメーション
	static constexpr int SHOT_MAX_NUM_ANIM = 16;

	// 弾のサイズ
	static constexpr int SHOT_SIZE_X = 48;
	static constexpr int SHOT_SIZE_Y = 48;

	// 弾の縦横の分割数
	static constexpr int SHOT_NUM_X = 4;
	static constexpr int SHOT_NUM_Y = 4;

	// 弾発射後の硬直時間
	static constexpr float SHOT_DELAY = 1.0f;

	// コンストラクタ
	Player2();

	// デストラクタ
	~Player2(void);

	void Init(GameScene2* scene, InputManager::JOYPAD_NO playerNo);
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

	// Shotの取得
	std::vector<Shot*> GetShots(void);

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
	GameScene2* gameScene_;

	// 弾
	std::vector<Shot*> shots_;

	// プレイヤーの画像
	int playerImg_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM];

	// プレイヤーの死亡画像
	int playerDeathImage;

	// 弾画像
	int shotImgs_[SHOT_MAX_NUM_ANIM];

	// プレイヤーの座標
	Vector2 pos_;

	// 中心座標
	Vector2 centerPos_;

	// プレイヤーの移動速度
	int speed_;

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

	// 弾発射後の硬直時間計算用
	float stepShotDelay_;

	// ゲームパッドの番号
	InputManager::JOYPAD_NO padNo_;

	// プレイヤーのデバッグ描画
	void DrawDebug(void);

	// 弾を発射する
	void Attack(void);

	// 弾の生成
	Shot* GetValidShot(void);

	// 攻撃の音
	int shotSE_;

	// 決定音
	int decideSE_;

	// プレイヤーごとに入力したか
	bool inputPlayer_;

	// プレイヤーがOKボタンを押したときの音
	int playerDecideSE_;

	// 死んだときの音
	int deathSE_;

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
