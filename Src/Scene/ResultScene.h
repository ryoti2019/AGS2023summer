#pragma once
#include "SceneBase.h"
#include "../Utility/AsoUtility.h"

class SceneManager;

class ResultScene : public SceneBase

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
	ResultScene(void);

	// デストラクタ
	~ResultScene(void);

	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

private:

	// 方向
	AsoUtility::DIR dir_;

	// アニメーションのデータ
	int animData_[4];

	// アニメーションのカウント
	int cntAnim_;

	// プレイヤーが勝った数
	int win1_;
	int win2_;
	int win3_;
	int win4_;

	// 誰が優勝しているか
	bool isWin1_;
	bool isWin2_;
	bool isWin3_;
	bool isWin4_;

	// プレイヤーの画像
	int p1Image_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM];;
	int p2Image_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM];;
	int p3Image_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM];;
	int p4Image_[static_cast<int>(AsoUtility::DIR::MAX)][PLAYER_MAX_NUM_ANIM];;

	int youWin_;

	// 入力された総数
	int inputNum_;

	// プレイヤーの人数
	int playerNum_;

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

	// プレイヤーがOKボタンを押したときの音
	int playerDecideSE_;

	// BGM
	int bgm_;

	// 決定音
	int decideSE_;

};

