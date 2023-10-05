#pragma once
#include "SceneBase.h"
#include "../Manager/InputManager.h"
#include "../Utility/AsoUtility.h"
class SceneManager;
class Grid;

class TitleScene : public SceneBase
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

	// スクロール速度
	static constexpr int SCROLL_POW = 2;

	// 背景のサイズ
	static constexpr int BG_SIZE_X = 2048;
	static constexpr int BG_SIZE_Y = 640;

	// プレイヤー
	enum class PLAYER_NUM
	{
		PLAYER_2 = 2,
		PLAYER_3 = 3,
		PLAYER_4 = 4,
		MAX
	};



	// コンストラクタ
	TitleScene(void);

	// デストラクタ
	~TitleScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	// プレイヤーの画像
	int img1_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM];
	int img2_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM];
	int img3_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM];
	int img4_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM];

	// プレイヤー座標
	Vector2 pos1_;
	Vector2 pos2_;
	Vector2 pos3_;
	Vector2 pos4_;

	// プレイヤーの状態
	bool p1_;
	bool p2_;
	bool p3_;
	bool p4_;

	// プレイヤーの方向
	AsoUtility::DIR dir_;

	// プレイヤーの移動スピード
	float p1speed_;
	float p2speed_;
	float p3speed_;
	float p4speed_;

	// アニメーションのデータ
	int animData_[4];

	// アニメーションのカウント
	int cntAnim_;

	// ゲームパッドの番号
	InputManager::JOYPAD_NO padNo_;

	// BGM
	int bgm_;

	// 決定音
	int decideSE_;

	// 選択音
	int selectSE_;

	// 背景
	int bgImage_;

	// タイトルロゴ
	int logoImage_;

	// 背景の座標
	Vector2 bgImagePos01_;
	Vector2 bgImagePos02_;

	int step1_;
	int step2_;
	int step3_;
	int step4_;
	int nextStep1_;
	int nextStep2_;
	int nextStep3_;
	int nextStep4_;

	// スタートの画像
	int startImage_;

	// 明滅用カウンター
	int blinkCnt_;

};

