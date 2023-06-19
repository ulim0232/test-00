#pragma once
#include "SpriteGo.h"
#include "Defines.h"
#include <SFML/Audio.hpp> //사운드 출력을 위해 추가한 헤더
class Tree;
class Player :public SpriteGo
{
protected:
	Tree* tree;
	Sides side; //플레이어가 왼쪽에 있는지 오른쪽에 있는지
	
	float offsetX;
	sf::Vector2f playerPositions[2];

	sf::Texture texAxe; //도끼의 텍스쳐
	SpriteGo* axe;

	bool isChopping; //ture일 때 도끼가 나타남
	bool isAlive; //살아있으면 true

	sf::Texture texRip; //비석 텍스쳐
	sf::Texture& texPlayer;

	int score;

	sf::SoundBuffer soundBufferChop; //chop 소리에 사용할 사운드 버퍼
	sf::SoundBuffer soundBufferDeath;
	sf::SoundBuffer soundBufferTimeOut;

	sf::Sound soundChop;
	sf::Sound soundDeath;
	sf::Sound soundTimeOut;
public:
	Player(sf::Texture& tex,
		sf::Vector2f sptriteDir = sf::Vector2f(-1, -1),
		const std::string& n = "",
		const sf::Vector2f p = { 0, 0 });
	~Player() override;

	void SetTree(Tree* tree);
	void SetSide(Sides side);
	Sides GetSide() const; 

	void Chop(Sides side); //도끼를 치는 액션
	void Die(); //플레이어가 죽을 때

	virtual void SetPosition(const sf::Vector2f& p) override;
	virtual void SetPosition(float x, float y) override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	bool isCrashed();
	int GetScore();

	void PlayDeathSound();
	void PlayTimeOutSound();
};

