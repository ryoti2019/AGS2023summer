#pragma once
#include "SceneBase.h"
#include "../Common/Vector2F.h"
#include "../Utility/AsoUtility.h"

class Player4;
class Stage2;
class StartMes;
class ResultScene;

class GameScene4 : public SceneBase
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

	// コンストラクタ
	GameScene4(void);

	// デストラクタ
	~GameScene4(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	// ワールド(スクリーン)座標をマップ座標に変換する
	Vector2 World2MapPos(Vector2 worldPos);

	// マップチップを使用した衝突判定
	bool IsCollisionStage(Vector2 worldPos);

	// ステージの取得
	Stage2* GetStage(void);

	// 左の取得
	bool GetL(void);

	// 左の設定
	void SetL(bool left);

	// 右の取得
	bool GetR(void);

	// 左の設定
	void SetR(bool right);

	// カウンタの取得
	int GetCnt(void);

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
	std::vector<Player4*> players_;

	// スタートメッセージ
	StartMes* startMes_;

	// リザルト
	ResultScene* resultScene_;

	// ステージ
	Stage2* stage_;

	// プレイヤーの画像
	int playerImg_[PLAYER_MAX_NUM_ANIM];

	// 方向
	Vector2 dir_;

	// 左のフラグ
	bool left_;

	// 右のフラグ
	bool right_;

	int lr_[2];

	// 左右の判定を始める用
	bool start_;

	// 左右の判定を始める用のカウンタ
	int startCnt_;

	// カウントダウンのカウンタが足されていいかのフラグ
	bool startCntStart_;

	// カウントダウンの画像
	int count1_;
	int count2_;
	int count3_;
	int count4_;
	int count5_;

	// カウントダウンのカウンタ
	int downCnt_;

	// カウントダウンのカウンタが足されていいかのフラグ
	bool downCntStart_;

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

	// トゲの音
	int spinaSE_;

	// カウントダウンの音
	int countDownSE_;

	// 選べの画像
	int erabe_;

	// 攻撃を受けるときにプレイヤーの動きを止める時間
	int notOperationTime_;

	// ランダムに決めた数字
	int random_;

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

	bool win_;

};

