#pragma once
#include "SceneBase.h"
#include "../Common/Vector2F.h"
#include "../Utility/AsoUtility.h"

class SceneManager;
class Player5;
class Stage;
class Shot;
class StartMes;
class ResultScene;

class GameScene5 : public SceneBase
{

public:

	// プレイヤーの最大アニメーション
	static constexpr int PLAYER_MAX_NUM_ANIM = 12;

	// プレイヤーのサイズ
	static constexpr int PLAYER_SIZE_X = 100;
	static constexpr int PLAYER_SIZE_Y = 100;

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

	// Lスティックの最大アニメーション
	static constexpr int STICK_MAX_NUM_ANIM = 8;

	// Lスティックのサイズ
	static constexpr int STICK_SIZE_X = 32;
	static constexpr int STICK_SIZE_Y = 32;

	// Lスティックの縦横の分割数
	static constexpr int STICK_NUM_X = 8;
	static constexpr int STICK_NUM_Y = 1;

	enum class DIR
	{
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

	// コンストラクタ
	GameScene5(void);

	// デストラクタ
	~GameScene5(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	// 全員の入力が終わったらtrueになる
	bool GetInputEnd(void);

	void SetInputEnd(bool inputEnd);

	// 方向の取得
	std::vector<int> GetDir(void);

	// 後ろに要素数を足す
	void SetPushBack(bool pushback);

	// 画像の表示時間
	int GetImageTime(void);

	// 生きているプレイヤーにフラグを合わせる
	bool GetPlayerInput(void);

	// 答えを表示させる時間
	int GetAnswerTime(void);

	// 答えを表示する時間が終わったか
	bool GetIsAnswer(void);

	// リザルトの取得
	bool GetResult(void);

	// スキップの取得
	bool GetSkip(void);

	// スタートの状態
	bool IsStart(void);

	void SetInputNum(int input);

	void SetStartNum(int start);

	bool GetRevival(void);

private:

	// プレイヤー
	std::vector<Player5*> players_;

	// スタートメッセージ
	StartMes* startMes_;

	// リザルト
	ResultScene* resultScene_;

	// ステージ
	Stage* stage_;

	// プレイヤーの画像
	int playerImg_[PLAYER_MAX_NUM_ANIM];

	// 方向
	Vector2 dir_;

	// 向き
	std::vector<int> direction_;

	// 入力しないといけない数
	int pushMax_;

	// 入力した数
	int pushCnt_;

	// 方向を決める前のフラグ
	bool dirAlive_;

	// デバッグ描画
	void DrawDebug(void);

	// 全員の入力が終わったらtrueになる
	bool inputEnd_;

	// 後ろに要素数を足す
	bool pushBack_;

	// 背景画像
	int bgImage_;

	// 黒板画像
	int kokubanImage_;

	// 矢印の画像
	int arrowImage_;

	// 画像が出る時間
	int imageTime_;

	int cnt_;

	// 生きてるプレイヤーにフラグを合わせる
	bool playerInput_;

	// ゲーム説明用の画像
	int expImage_;

	// ゲーム説明をスキップするためのフラグ
	bool skip_;

	// 決定音
	int decideSE_;

	// Bボタンの画像
	int BbottonImage_[BOTTON_MAX_NUM_ANIM];

	// Lスティックの画像
	int LstickIMage_[STICK_MAX_NUM_ANIM];

	// アニメーションのカウンタ
	int cntAnim_;

	// BGM
	int bgm_;

	// ダメージを食らった時の音
	int damageSE_;

	// 入力しろの画像
	int nyuuryokusiro_;

	// 答え合わせのカウンタ
	int answerCnt_;

	// 答えを表示させる時間
	int answerTime_;

	// 答えを表示させ終わった
	bool isAnswer_;

	// ダメージを食らい終わった
	bool damage_;

	// 問題が出されたときの音
	int questionSE_;

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

	// 復活したときのフラグ
	bool revival_;

	// 復活したときのHPを増やすフラグ
	bool revivalHP_;

	// ランダムに数字を1回選ぶ
	bool isRand1_;
	bool isRand2_;
	bool isRand3_;
	bool isRand4_;

	// ランダムに決まった数の総数
	int inputRandNum_;

	// ランダム
	void Rand(void);

	// 全部のサイコロの画像
	int allDice_[6];

	// 1つずつのサイコロの画像
	int dice1_;
	int dice2_;
	int dice3_;
	int dice4_;
	int dice5_;
	int dice6_;

	// サイコロを振れ
	int saikoro_;

	// 勝ったとき数字を足す
	bool win_;

};

