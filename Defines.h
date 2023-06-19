#pragma once

enum class Sides
{
	Left,
	Right,
	None
};

enum class Origins //오리진(피봇)을 표현할 열거형
{
	TL,
	TC,
	TR,
	ML,
	MC,
	MR,
	BL,
	BC,
	BR
}; //나누기를 통해 TMB, 나머지를 통해 LCR 구하기
