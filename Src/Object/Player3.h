#pragma once
#include "../Utility/AsoUtility.h"
#include "../Common/Vector2.h"
#include "../Manager/InputManager.h"
#include "../Scene/GameScene3.h"

class Shot2;

class Player3
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
	Player3();

	// デストラクタ
	~Player3(void);

	void Init(GameScene3* scene, InputManager::JOYPAD_NO playerNo);
	void Update(void);
	void Draw(void);
	void Release(void);

	// 座標の取得
	Vector2 GetPos(void);

	// 座標のセッター
	void SetPos(Vector2 pos);

	// Shotの取得
	std::vector<Shot2*> GetShots(void);

	// スタート時の入力状態
	bool GetInputStart(void);

	// 次へ進むときの入力状態
	bool GetInputPlayer(void);

private:

	// ゲームシーンのポインタ変数
	GameScene3* gameScene_;

	// 弾
	std::vector<Shot2*> shots_;

	// プレイヤーの画像
	int playerImg_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM];

	// プレイヤーの座標
	Vector2 pos_;

	// 中心座標
	Vector2 centerPos_;

	// 方向
	AsoUtility::DIR dir_;

	// 弾画像
	int shotImgs_[SHOT_MAX_NUM_ANIM];

	// アニメーションのデータ
	int animData_[4];

	// アニメーションのカウント
	int cntAnim_;

	// アニメーションスピード
	float speedAnim_;

	// ゲームパッドの番号
	InputManager::JOYPAD_NO padNo_;

	// 弾を発射する
	void Attack(void);

	// 弾の生成
	Shot2* GetValidShot(void);

	// 攻撃の音
	int shotSE_;

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

};

