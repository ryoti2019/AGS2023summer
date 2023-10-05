#pragma once
class Application
{

public:

	// スクリーンサイズ
	static constexpr int SCREEN_SIZE_X = 1024;
	static constexpr int SCREEN_SIZE_Y = 640;

	// コンストラクタ
	Application(void);

	// デストラクタ
	~Application(void);

	// 初期化
	void Init(void);

	// ゲームループの開始
	void Run(void);

	// リソースの解放
	void Release(void);

	// エラー判定
	bool IsError(void);

private:

	// エラー判定
	bool isError_;

};

