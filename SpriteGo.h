#pragma once
#include "GameObject.h"

//움직이지 않는 오브젝트 객체를 만드는 클래스

class SpriteGo : public GameObject
{
protected:
	sf::Sprite sprite;
	sf::Vector2f sptriteDir; //원본 이미지가 보고 있는 방향 정보

public:
	SpriteGo(sf::Texture& tex, 
		sf::Vector2f spriteDir = sf::Vector2f(-1, -1), //이거는 get, set 함수를 사용하는 것이 더 편할지도?
		const std::string& n = "",
		const sf::Vector2f p = { 0, 0 });
	virtual ~SpriteGo() override;

	virtual void SetPosition(const sf::Vector2f& p) override;
	virtual void SetPosition(float x, float y) override;
	virtual void SetOrigin(Origins origin) override;
	virtual void SetOrigin(float x, float y) override;

	sf::Vector2f GetSize() const;

	void SetTexture(sf::Texture& tex, sf::Vector2f sptriteDir = sf::Vector2f(-1, -1));
	//방향은 오른쪽이 기본값

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetFlipX(bool flip); //텍스쳐의 방향 변경, 인자가 true이면 원래 방향
	void SetFlipY(bool flip); //텍스쳐의 방향 변경
};

