#pragma once
#include "SpriteGo.h"
class EffectGo :public SpriteGo
{
protected:
	/*포물선 움직임을 위해서 필요한 데이터
	1. 시작할 위치, setpostion함수 또는 생성자 사용
	- 속도*시간: 이동한 거리
	- 중력 가속도: 가속도*시간, y에 적용된다.
	설정한 시간*/

	sf::Vector2f velocity; //현재 속도 의미
	sf::Vector2f gravity; //중력가속도

	float duration; //오브젝트가 존재할 시간
	float timer; //시간 측정에 사용
public:
	EffectGo(sf::Texture& tex,
		sf::Vector2f sptriteDir = sf::Vector2f(-1, -1),
		const std::string& n = "",
		const sf::Vector2f p = { 0, 0 });
	~EffectGo();
	void Fire(sf::Vector2f velo); //오브젝트를 날리는 동작

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

