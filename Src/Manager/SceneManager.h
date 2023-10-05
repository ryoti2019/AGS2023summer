#pragma once
#include <chrono>
class SceneBase;
class Fader;
class Camera;

class SceneManager
{

public:

	static constexpr float DEFAULT_FPS = 60.0f;

	// シーン管理用
	enum class SCENE_ID
	{
		NONE,
		TITLE,
		PLAYERSELECT,
		SELECT,
		GAMESELECT,
		GAME,
		GAME2,
		GAME3,
		GAME4,
		GAME5,
		RESULT
	};

	// インスタンスの生成
	static void CreateInstance(void);

	// インスタンスの取得
	static SceneManager& GetInstance(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	// 状態遷移
	void ChangeScene(SCENE_ID nextId);

	// シーンIDの取得
	SCENE_ID GetSceneID(void);

	// デルタタイムの取得
	float GetDeltaTime(void) const;
	
	// プレイヤーの人数の取得
	int GetPlayerNum(void);

	// プレイヤーの人数の取得
	void SetPlayerNum(int num);

	// バトルモードの取得
	bool GetBattleMode(void);

	// バトルモードの設定
	void SetBattleMode(bool battleMode);

	// 勝った数の設定
	void SetWin1(int win);
	void SetWin2(int win);
	void SetWin3(int win);
	void SetWin4(int win);

	int GetWin1(void);
	int GetWin2(void);
	int GetWin3(void);
	int GetWin4(void);

private:

	// 静的インスタンス
	static SceneManager* instance_;

	SCENE_ID sceneId_;
	SCENE_ID waitSceneId_;

	// フェード
	Fader* fader_;

	// 各種シーン
	SceneBase* scene_;

	// カメラ
	Camera* camera_;

	// シーン遷移中判定
	bool isSceneChanging_;

	// デルタタイム
	std::chrono::system_clock::time_point preTime_;
	float deltaTime_;

	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	SceneManager(void);
	// コピーコンストラクタも同様
	SceneManager(const SceneManager&);
	// デストラクタも同様
	~SceneManager(void);

	// デルタタイムをリセットする
	void ResetDeltaTime(void);

	// シーン遷移
	void DoChangeScene(SCENE_ID sceneId);

	// フェード
	void Fade(void);

	// プレイヤーの人数
	int playerNum_;

	// プレイヤーのモード
	bool battleMode_;

	// プレイヤーが勝った数
	int win1_;
	int win2_;
	int win3_;
	int win4_;

};

