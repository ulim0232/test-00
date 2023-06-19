#pragma once
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include "Defines.h"

//enum class Origins //오리진(피봇)을 표현할 열거형
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
//}; //나누기를 통해 TMB, 나머지를 통해 LCR 구하기

class Utils
{
private:
	static std::random_device rd;
	static std::mt19937 gen;

public:
	static int RandomRange(int min, int maxExclude);
	static float RandomRange(float min, float max);

	//sprite 의 오리진 설정
	static void SetOrigin(sf::Sprite& sprite, Origins origin);
	//text의 오리진 설정
	static void SetOrigin(sf::Text& text, Origins origin);
	//rectangleshape의 오리진 설정
	static void SetOrigin(sf::Shape& shape, Origins origin);
	static void SetOrigin(sf::Transformable& obj, Origins origin, const sf::FloatRect& rect);
	//Rect(left, top, width, height);
};

