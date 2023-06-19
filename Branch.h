#pragma once
#include "SpriteGo.h"
#include "Defines.h"

//enum class Sides
//{
//	Left,
//	Right,
//	None
//};
class Branch :public SpriteGo
{
protected:
	SpriteGo* tree;
	Sides side; //방향, 오른쪽 가지? 왼쪽 가지?

public:
	Branch(sf::Texture& tex,
		sf::Vector2f spriteDir = sf::Vector2f(-1, -1), 
		const std::string& n = "",
		const sf::Vector2f p = { 0, 0 });

	~Branch() override;

	virtual void Init();

	void SetTree(SpriteGo* tree);
	void SetSide(Sides side);
	Sides GetSide() const;

};

