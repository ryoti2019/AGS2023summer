#pragma once
#include "SceneBase.h"
#include "../Common/Vector2F.h"
#include "../Utility/AsoUtility.h"

class SceneManager;
class Player;
class Meteor;
class MeteorChild;
class StartMes;
class ResultScene;

class GameScene : public SceneBase
{

public:

	// 隕石の最大アニメーション
	static constexpr int METEOR_MAX_NUM_ANIM = 3;

	// 隕石のサイズ
	static const int METEOR_SIZE_X = 64; // 横サイズ
	static const int METEOR_SIZE_Y = 64; // 縦サイズ

	// 弾発射後の硬直時間
	static constexpr float SHOT_DELAY = 1.0f;

	// Bボタンの最大アニメーション
	static constexpr int BOTTON_MAX_NUM_ANIM = 4;

	// Bボタンのサイズ
	static constexpr int BOTTON_SIZE_X = 32;
	static constexpr int BOTTON_SIZE_Y = 32;

	// ボタンの縦横の分割数
	static constexpr int BOTTON_NUM_X = 4;
	static constexpr int BOTTON_NUM_Y = 1;

	// エフェクトの最大アニメーション
	static constexpr int EFFECT_MAX_NUM_ANIM = 60;

	// エフェクトのサイズ
	static constexpr int EFECT_SIZE_X = 108;
	static constexpr int EFECT_SIZE_Y = 116;

	// エフェクトの分割数
	static constexpr int EFFECT_NUM_X = 10;
	static constexpr int EFFECT_NUM_Y = 8;

	// コンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

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

	bool GetRevival(void);

private:

	// シーンの管理
	SceneManager* sceneManager_;

	// プレイヤー
	std::vector<Player*> players_;
	
	// 隕石
	std::vector<Meteor*> meteors_;

	// リザルト
	ResultScene* resultScene_;

	// 隕石の画像
	int meteorImage_[METEOR_MAX_NUM_ANIM];

	// スタートメッセージ
	StartMes* startMes_;

	// 背景画像
	int bgImage_;

	// 衝突判定
	void Collision(void);

	// 衝突判定
	bool IsCollisionRect(Vector2 stPos1, Vector2 edPos1, Vector2 stPos2, Vector2 edPos2);

	// 衝突判定
	bool IsCollisionRectCenter(Vector2 centerPos1, Vector2 size1, Vector2 centerPos2, Vector2 size2);

	// ゲーム説明用の画像
	int expImage_;

	// ゲーム説明をスキップするためのフラグ
	bool skip_;

	// ダメージを食らった時の音
	int damageSE_;

	// 決定音
	int decideSE_;

	// BGM
	int bgm_;

	// 生き残れの画像
	int ikinokore_;

	// Bボタンの画像
	int BbottonImage_[BOTTON_MAX_NUM_ANIM];

	// アニメーションのカウンタ
	int cntAnim_;

	// 当たった時のエフェクト
	int hitEffectImage_[EFFECT_MAX_NUM_ANIM];

	// アニメーションスピード
	float speedAnim_;

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