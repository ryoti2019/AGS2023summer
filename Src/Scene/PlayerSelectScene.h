#pragma once
#include "SceneBase.h"
#include "../Manager/InputManager.h"
#include "../Utility/AsoUtility.h"
class SceneManager;
class Grid;

class PlayerSelectScene : public SceneBase
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
	PlayerSelectScene(void);

	// デストラクタ
	~PlayerSelectScene(void);

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

	// プレイヤーのUI画像
	int p1Image_;
	int p2Image_;
	int p3Image_;
	int p4Image_;

	// プレイヤーのUI座標
	Vector2 p1Pos_;
	Vector2 p2Pos_;
	Vector2 p3Pos_;
	Vector2 p4Pos_;

	// アニメーションのデータ
	int animData_[4];

	// アニメーションのカウント
	int cntAnim_;

	// 方向
	AsoUtility::DIR dir_;

	// プレイヤーの人数
	int playerNum_;
	int oldPlayerNum_;

	// プレイヤーの人数選択
	void PlayerSelect(void);

	// Lスティックが倒されたか
	bool stickL_;

	// ゲームパッドの番号
	InputManager::JOYPAD_NO padNo_;

	// BGM
	int bgm_;

	// 決定音
	int decideSE_;

	// プレイヤーがOKボタンを押したときの音
	int playerDecideSE_;

	// 選択音
	int selectSE_;

	// タイトルロゴ
	int logoImage_;

	// 背景
	int bgImage_;

	// 背景の座標
	Vector2 bgImagePos01_;
	Vector2 bgImagePos02_;

	// 「人数を選択してください」の画像
	int selectImage_;

	// 入力された総数
	int inputNum_;

	// プレイヤーごとに入力したか
	bool inputPlayer1;
	bool inputPlayer2;
	bool inputPlayer3;
	bool inputPlayer4;

	// プレイヤーのOK画像の読み込み
	int OKImage1_;
	int OKImage2_;
	int OKImage3_;
	int OKImage4_;

	// 戻るボタン
	int backImage_;
	int bootonAImage_;

};


