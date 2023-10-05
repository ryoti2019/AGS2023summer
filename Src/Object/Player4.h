#pragma once
#include "../Utility/AsoUtility.h"
#include "../Common/Vector2.h"
#include "../Manager/InputManager.h"
#include "../Scene/GameScene4.h"

class SceneManager;

class Player4
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

	// コンストラクタ
	Player4();

	// デストラクタ
	~Player4(void);

	void Init(GameScene4* scene, InputManager::JOYPAD_NO playerNo);
	void Update(void);
	void Draw(void);
	void Release(void);

	// 座標の取得
	Vector2 GetPos(void);

	// 座標のセッター
	void SetPos(Vector2 pos);

	// 方向の設定
	void SetDir(AsoUtility::DIR dir);

	// 右の取得
	bool GetR(void);

	// 右の設定
	void SetR(bool r);

	// 右の取得
	bool GetL(void);

	// 右の設定
	void SetL(bool l);

	// HPを1減らすためのフラグの設定
	void SetSubTract(bool subtract);

	// 生存判定の取得
	bool IsAlive(void);

	// 生存判定の設定
	void SetAlive(bool alive);

	// １個前の生存判定の取得
	bool OldAlive(void);

	// スタート時の入力状態
	bool GetInputStart(void);

	// 次へ進むときの入力状態
	bool GetInputPlayer(void);

	// HPの設定
	void SetHP(int hp);

	// HPの取得
	int GetHP(void);

	// ランダムの数字を取得
	int GetRandNumber(void);

	// ランダムの数字を設定する
	void SetRandNumber(int rand);

	// 復活後ボタンを押したかの判定
	bool GetInputRevival(void);

private:

	// ゲームシーンのポインタ変数
	GameScene4* gameScene_;

	// シーンの管理
	SceneManager* sceneManager_;

	// プレイヤーの画像
	int playerImg_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM];

	// プレイヤーのUI
	int playerUIImage_;

	// プレイヤーの座標
	Vector2 pos_;

	// 中心座標
	Vector2 centerPos_;

	// 方向
	AsoUtility::DIR dir_;

	// アニメーションのデータ
	int animData_[4];

	// アニメーションのカウント
	int cntAnim_;

	// アニメーションスピード
	float speedAnim_;

	// ゲームパッドの番号
	InputManager::JOYPAD_NO padNo_;

	// 体力
	int hp_;

	// 生存フラグ
	bool isAlive_;

	// 1個前の生存フラグ
	bool oldAlive_;

	// スピード
	float speed_;

	// デバッグ描画
	void DrawDebug(void);

	// 左のフラグ
	bool left_;

	// 右のフラグ
	bool right_;

	// HPを1減らすためのフラグ
	bool subtract_;

	// ハート画像
	int heartImage_;

	// プレイヤー間の距離
	int pSpace_;

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

