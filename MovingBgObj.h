#pragma once
#include "SpriteGo.h"

//움직이는 객체를 저장할 클래스
//움직이는 방향,속도,범위 등을 설정
class MovingBgObj :public SpriteGo
{
protected:
	float speed; //속도
	sf::Vector2f speedRange; //랜덤 속도를 위해 추가, 스피드의 범위
	
	sf::Vector2f leftPos;
	sf::Vector2f rightPos;
	//sf::Vector2f initPos[2]; //첫번째는 왼쪽의 기준점, 두번째는 오른쪽의 기준점. left right로 분리
	
	//시작 좌표를 랜덤화하기 위해 추가
	sf::Vector2f posXRange;
	sf::Vector2f posYRange;

	sf::Vector2f direction;

	//포물선 이동을 위해 사용
	float widthY; //진동넓이
	float heightY; //진동폭
	float accumTime; //delta time을 누적할 변수
	sf::Vector2f originalPos;

public:
	MovingBgObj(sf::Texture& tex,
		sf::Vector2f sptriteDir = sf::Vector2f(-1, -1),
		const std::string& n = "",
		const sf::Vector2f p = { 0, 0 });
	~MovingBgObj() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;//정해놓은 범위 벗어나면 init함수 호출
	virtual void Draw(sf::RenderWindow& window) override;

	void SetSpeedRange(sf::Vector2f sRange);
	void SetLRPos(sf::Vector2f left, sf::Vector2f right);

	void SetPosXRange(float min, float max);
	void SetPosYRange(float min, float max);

	void SetMoveY(float w, float h);
};

