#pragma once
class Vector2;

class Vector2F
{

public:

	float x;
	float y;

	// デフォルトコンストラクタ
	Vector2F(void);

	// コンストラクタ
	Vector2F(float vX, float vY);


	// コンストラクタ
	Vector2F(Vector2 value);

	// Vector2に変換したい
	Vector2 ToVector2F(void);

};