#include "MovingBgObj.h"
#include "Utils.h"

MovingBgObj::MovingBgObj(
	sf::Texture& tex,
	sf::Vector2f sptriteDir,
	const std::string& n,
	const sf::Vector2f p)
	:SpriteGo(tex, sptriteDir, n, p), 
	accumTime(0.f), widthY(0.f), heightY(0.f)
{
}

MovingBgObj::~MovingBgObj()
{
}

void MovingBgObj::Init()
{
	SpriteGo::Init();

	accumTime = 0.f;

	speed = Utils::RandomRange(speedRange.x, speedRange.y);
	sf::Vector2f randomPos(
		Utils::RandomRange(posXRange.x, posXRange.y),
		Utils::RandomRange(posYRange.x, posYRange.y));
	
	int rnd = Utils::RandomRange(0, 2); //0: left, 1: right	
	if(rnd == 0)
	{
		originalPos = leftPos + randomPos;
		SetPosition(originalPos);
		direction = sf::Vector2f(1.f, 0.f);
		SetFlipX(sptriteDir.x > 0);
	}
	else
	{
		originalPos = rightPos + randomPos;
		SetPosition(originalPos);
		direction = sf::Vector2f(-1.f, 0.f);
		SetFlipX(sptriteDir.x < 0);
	}
}

void MovingBgObj::Release()
{
	SpriteGo::Release();
}

void MovingBgObj::Update(float dt)
{
	SpriteGo::Update(dt);

	accumTime += dt;

	//움직여야될 만큼의 변이
	sf::Vector2f pos = GetPosition(); //기존의 포지션 가져오기
	pos += direction * speed * dt; //새로운 포지션 구하기
	
	pos.y = originalPos.y + sin(accumTime * widthY)* heightY;


	SetPosition(pos); //새로운 포지션으로 변경하기

	//범위가 벗어났을 때 재초기화
	if (pos.x < leftPos.x || pos.x > rightPos.x)
	{
		Init();
	}
}

void MovingBgObj::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void MovingBgObj::SetSpeedRange(sf::Vector2f sRange)
{
	speedRange = sRange;
}

void MovingBgObj::SetLRPos(sf::Vector2f left, sf::Vector2f right)
{
	leftPos = left;
	rightPos = right;
}

void MovingBgObj::SetPosXRange(float min, float max)
{
	posXRange.x = min;
	posXRange.y = max;
}

void MovingBgObj::SetPosYRange(float min, float max)
{
	posYRange.x = min;
	posYRange.y = max;
}

void MovingBgObj::SetMoveY(float w, float h)
{
	widthY = w;
	heightY = h;
}
