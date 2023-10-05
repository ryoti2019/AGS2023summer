#pragma once
#include <vector>
#include "../Utility/AsoUtility.h"
#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"
#include "MeteorChild.h"

class Player;
class GameScene;

class Meteor
{

public:

	// 弾の生存時間
	static constexpr float SHOT_ALIVE = 3.0f;

	// メテオのサイズ
	static constexpr int SIZE_X = 64;
	static constexpr int SIZE_Y = 64;

	// 爆発のアニメーション数
	static constexpr int BLAST_ANIM_NUM = 4;

	// コンストラクタ
	Meteor(int* imgs, int imgNum);

	// デストラクタ
	~Meteor(void);

	void Init(GameScene* scene);

	void Update(void);

	void Draw(void);

	void Release(void);

	// 座標の取得
	Vector2 GetPos(void);

	// 座標の設定
	void SetPos(Vector2 pos);

	// 隕石の取得
	std::vector<Meteor*> GetMeteors(void);

	// 隕石の子取得
	std::vector<MeteorChild*> GetMeteorChildlen(void);

private:

	// ゲームシーンのポインタ変数
	GameScene* gameScene_;

	// 隕石
	std::vector<Meteor*> meteors_;

	// 隕石の子
	std::vector<MeteorChild*> children_;

	// 隕石の生成
	MeteorChild* GetValidMeteor(void);

	// 座標
	Vector2 pos_;

	int step_;

	int nextStep_;

	// 画像
	int* imgs_;
	int imgNum_;

	// アニメーションのデータ
	int animData_[4];

	// アニメーションのカウント
	int cntAnim_;


};

