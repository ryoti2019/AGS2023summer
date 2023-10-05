#pragma once
#include <string>
#include <vector>
#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"

class AsoUtility
{

public:

	// �ړ�����
	enum class DIR
	{
		DOWN,
		LEFT,
		RIGHT,
		UP,
		MAX
	};

	// ������̕���
	static std::vector<std::string> Split(std::string& line, char delimiter);

	// �l�̌ܓ�
	static int Round(float value);

	// �l�̌ܓ�
	static Vector2 Round(Vector2F value);

	// �l�̌ܓ�
	static Vector2 Round(float x, float y);

	// �P�ʃx�N�g���ɕϊ�
	static Vector2F Normalize(AsoUtility::DIR dir);

	// ���W�A��(rad)����x(deg)
	static double Rad2DegD(double rad);
	static float Rad2DegF(float rad);
	static int Rad2DegI(int rad);

	// �x(deg)���烉�W�A��(rad)
	static double Deg2RadD(double deg);
	static float Deg2RadF(float deg);
	static int Deg2RadI(int deg);

};

