#pragma once
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include "Defines.h"

//enum class Origins //������(�Ǻ�)�� ǥ���� ������
//{
//		TL,
//		TC,
//		TR,
//		ML,
//		MC,
//		MR,
//		BL,
//		BC,
//		BR
//}; //�����⸦ ���� TMB, �������� ���� LCR ���ϱ�

class Utils
{
private:
	static std::random_device rd;
	static std::mt19937 gen;

public:
	static int RandomRange(int min, int maxExclude);
	static float RandomRange(float min, float max);

	//sprite �� ������ ����
	static void SetOrigin(sf::Sprite& sprite, Origins origin);
	//text�� ������ ����
	static void SetOrigin(sf::Text& text, Origins origin);
	//rectangleshape�� ������ ����
	static void SetOrigin(sf::Shape& shape, Origins origin);
	static void SetOrigin(sf::Transformable& obj, Origins origin, const sf::FloatRect& rect);
	//Rect(left, top, width, height);
};

