#pragma once
#include "../Scene/GameScene.h"
#include "../Utility/AsoUtility.h"
#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"

class Player;

class MeteorChild
{

public:

	// 弾の生存時間
	static constexpr float SHOT_ALIVE = 3.0f;

	// メテオのサイズ
	static constexpr int SIZE_X = 64;
	static constexpr int SIZE_Y = 64;

	// エフェクトの最大アニメーション
	static constexpr int EFFECT_MAX_NUM_ANIM = 60;

	// エフェクトのサイズ
	static constexpr int EFECT_SIZE_X = 108;
	static constexpr int EFECT_SIZE_Y = 116;

	// エフェクトの分割数
	static constexpr int EFFECT_NUM_X = 10;
	static constexpr int EFFECT_NUM_Y = 8;

	// 弾の状態
	enum class STATE
	{
		NONE,
		SHOT,
		BLAST,
		END
	};

	// コンストラクタ
	MeteorChild(int* imgs, int imgNum);

	// デストラクタ
	~MeteorChild(void);

	// 隕石の生成(隕石の進行方向、表示開始座標)
	void CreateShot(Vector2 pos, Vector2F dir);

	void Update(void);
	void UpdateShot(void);
	void UpdateBlast(void);
	void UpdateEnd(void);

	void Draw(void);
	void DrawShot(void);
	void DrawBlast(void);
	void DrawEnd(void);

	void Release(void);

	// 生存判定
	bool IsAlive(void);

	// 座標の取得
	Vector2 GetMeteorPos(void);

	// 生存判定の設定
	void SetAlive(bool alive);

	// 爆発開始
	void Blast(Vector2F pos);

private:

	// プレイヤー
	std::vector<Player*> players_;

	// 弾の状態
	STATE state_;

	// 方向
	Vector2F dir_;

	// 座標
	Vector2 pos_;

	// 爆発座標
	Vector2F blastPos_;

	// 画像
	int* imgs_;
	int imgNum_;

	// アニメーションスピード
	float speedAnim_;

	// アニメーションのカウント
	int cntAnim_;

	// 生存判定
	bool isAlive_;

	// 隕石の移動速度
	float speed_;

	// デバッグ描画
	void DrawDebug(void);

	// 弾が消えるライン
	int deathLine_;
	
	// 爆発のアニメーションカウンタ
	int blastCntAnim_;

	// 爆発のアニメーション速度
	float blastSpeedAnim_;

	// 爆発のアニメーション番号
	int blastIdxAnim_;

	// 状態遷移
	void ChangeState(STATE state);

	// 当たった時のエフェクト
	int hitEffectImage_[EFFECT_MAX_NUM_ANIM];

};

