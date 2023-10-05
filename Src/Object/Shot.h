#pragma once
#include <vector>
#include "../Scene/GameScene.h"
#include "../Utility/AsoUtility.h"
#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"

class Shot
{
public:

	// 弾の生存時間
	static constexpr float SHOT_ALIVE = 3.0f;

	// 弾のサイズ
	static constexpr int SIZE_X = 64;
	static constexpr int SIZE_Y = 64;

	// エフェクトの最大アニメーション
	static constexpr int EFFECT_MAX_NUM_ANIM = 27;

	// エフェクトのサイズ
	static constexpr int EFECT_SIZE_X = 516;
	static constexpr int EFECT_SIZE_Y = 528;

	// エフェクトの分割数
	static constexpr int EFFECT_NUM_X = 9;
	static constexpr int EFFECT_NUM_Y = 3;

	// 弾の状態
	enum class STATE
	{
		NONE,
		SHOT,
		BLAST,
		END
	};

	// コンストラクタ
	Shot(int* imgs, int imgNum);

	// デストラクタ
	~Shot(void);

	// 隕石の生成(隕石の進行方向、表示開始座標)
	void CreateShot(Vector2 pos, Vector2F dir);

	void Init(void);

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
	Vector2 GetPos(void);

	// 生存判定の設定
	void SetAlive(bool alive);

	// 弾を爆発させる
	void ShotBlast(void);

	// 爆発開始
	void Blast(Vector2F pos);

private:

	// プレイヤー
	Player* player_;

	// 弾の状態
	STATE state_;

	// 方向
	Vector2F dir_;

	// アニメーションの方向
	AsoUtility::DIR dir2_;

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

	// アニメーションのデータ
	int animData_[5];

	// 生存判定
	bool isAlive_;

	// 隕石の移動速度
	float speed_;

	// 弾の生存時間計算用
	float stepAlive_;

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

