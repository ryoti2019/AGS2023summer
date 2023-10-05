#pragma once
#include "../Utility/AsoUtility.h"
#include "../Common/Vector2.h"
#include "../Manager/InputManager.h"
#include "../Scene/GameScene5.h"

class Player5
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

	// 選んだ方向
	enum class DIR
	{
		UP = 1,
		RIGHT = 2,
		DOWN = 3,
		LEFT = 4
	};

	// コンストラクタ
	Player5();

	// デストラクタ
	~Player5(void);

	void Init(GameScene5* scene, InputManager::JOYPAD_NO playerNo);
	void Update(void);
	void Draw(void);
	void Release(void);

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

	// 方向の取得
	std::vector<int> GetDir(void);

	// 入力しないといけない数
	int GetPushMax(void);

	// HPの取得
	int GetHP(void);

	// HPの設定
	void SetHP(int hp);

	// 入力したかの
	bool GetinputAlive(void);

	// 最大値分描画ができたか
	int GetArrowCnt(void);

	// 最大値分の描画を0にする
	void SetArrowCnt(int cnt);

	// ダメージを食らった時
	bool GetDamage(void);

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
	GameScene5* gameScene_;

	// プレイヤーの画像
	int playerImg_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM];

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

	// 体力最大値
	float hpMax_;

	// 生存フラグ
	bool isAlive_;

	// 1個前の生存フラグ
	bool oldAlive_;

	// スピード
	float speed_;

	// デバッグ描画
	void DrawDebug(void);

	// HPを1減らすためのフラグ
	bool subtract_;

	// 入力したものを格納する配列
	std::vector<int> direction_;

	// 入力した数
	int pushCnt_;

	// 入力しないといけない数
	int pushMax_;

	// 入力がすべて終わったかどうかのフラグ
	bool inputAlive_;

	// 入力した時の画像
	int inputImage_;

	// まだ入力されていない時の画像
	int notInputImage_;

	// 答え合わせの時の矢印の画像
	int arrowImage_;

	// 答えを順番に表示させるためのカウンタ
	int answerCnt_;

	// 矢印が最大値分描画させるためのカウンタ
	int arrowCnt_;

	// ダメージを食らった時
	bool damage_;

	// 〇画像
	int maruImage_;

	// ×画像
	int batuImage_;

	// 入力したときの音
	int inputSE_;

	// 決定音
	int decideSE_;

	// プレイヤーがOKボタンを押したときの音
	int playerDecideSE_;

	// プレイヤーごとに入力したか
	bool inputPlayer_;

	// スタート時の入力状態
	bool inputStart_;

	// 死んだときの音
	int deathSE_;

	// 死んだときの音のフラグ
	bool death_;

	// １個前の生存フラグを保持しておく時間
	int aliveCnt_;

	// 復活した後の入力
	bool inputRevival_;

	// ランダムで出た数
	int randNumber_;

};

