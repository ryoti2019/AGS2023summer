#pragma once
#include <string>
#include <vector>
#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"

class AsoUtility
{

public:

	// 移動方向
	enum class DIR
	{
		DOWN,
		LEFT,
		RIGHT,
		UP,
		MAX
	};

	// 文字列の分割
	static std::vector<std::string> Split(std::string& line, char delimiter);

	// 四捨五入
	static int Round(float value);

	// 四捨五入
	static Vector2 Round(Vector2F value);

	// 四捨五入
	static Vector2 Round(float x, float y);

	// 単位ベクトルに変換
	static Vector2F Normalize(AsoUtility::DIR dir);

	// ラジアン(rad)から度(deg)
	static double Rad2DegD(double rad);
	static float Rad2DegF(float rad);
	static int Rad2DegI(int rad);

	// 度(deg)からラジアン(rad)
	static double Deg2RadD(double deg);
	static float Deg2RadF(float deg);
	static int Deg2RadI(int deg);

};

