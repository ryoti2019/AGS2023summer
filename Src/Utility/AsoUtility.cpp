#include <DxLib.h>
#include <sstream>
#include "AsoUtility.h"

std::vector<std::string> AsoUtility::Split(std::string& line, char delimiter)
{

    // ���I�z��̕Ԃ�l������
    std::vector<std::string> result;

    // �����񑀍�p�̃N���X�ɒu��������
    std::istringstream stream(line);

    std::string field;

    // stream�����ɓǂݍ��݁A
    // ��R�����Ŏw�肳�ꂽ�����܂ł��Q�����ɕԂ�
    while (getline(stream, field, delimiter)) {
        // ���I�z��ɒǉ�
        result.push_back(field);
    }

    // ��F"aaa,bbb,ccc"
    // �@�@��result[0] = aaa
    // �@�@�@result[1] = bbb
    // �@�@�@result[2] = ccc

    return result;

}

int AsoUtility::Round(float value)
{
    return static_cast<int>(round(value));
}

Vector2 AsoUtility::Round(Vector2F value)
{
    Vector2 ret;
    ret.x = static_cast<int>(round(value.x));
    ret.y = static_cast<int>(round(value.y));
    return ret;
}

Vector2 AsoUtility::Round(float x, float y)
{
    Vector2 ret;
    ret.x = static_cast<int>(round(x));
    ret.y = static_cast<int>(round(y));
    return ret;
}

Vector2F AsoUtility::Normalize(AsoUtility::DIR dir)
{

    Vector2F ret;

    switch (dir)
    {
    case AsoUtility::DIR::UP:
        ret.x = 0.0f;
        ret.y = -1.0f;
        break;
    case AsoUtility::DIR::RIGHT:
        ret.x = 1.0f;
        ret.y = 0.0f;
        break;
    case AsoUtility::DIR::DOWN:
        ret.x = 0.0f;
        ret.y = 1.0f;
        break;
    case AsoUtility::DIR::LEFT:
        ret.x = -1.0f;
        ret.y = 0.0f;
        break;
    }

    return ret;
}

double AsoUtility::Rad2DegD(double rad)
{
    return rad * (180.0 / DX_PI);
}

float AsoUtility::Rad2DegF(float rad)
{
    return rad * (180.0f / DX_PI_F);
}

int AsoUtility::Rad2DegI(int rad)
{
    return rad * Round(180.0f / DX_PI_F);
}

double AsoUtility::Deg2RadD(double deg)
{
    return deg * (DX_PI / 180.0);
}

float AsoUtility::Deg2RadF(float deg)
{
    return deg * (DX_PI_F / 180.0f);
}

int AsoUtility::Deg2RadI(int deg)
{
    return deg * Round(DX_PI_F / 180.0f);
}
