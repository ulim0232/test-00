#pragma once
#include "SpriteGo.h"
#include "Defines.h"
#include <SFML/Audio.hpp> //���� ����� ���� �߰��� ���
class Tree;
class Player :public SpriteGo
{
protected:
	Tree* tree;
	Sides side; //�÷��̾ ���ʿ� �ִ��� �����ʿ� �ִ���
	
	float offsetX;
	sf::Vector2f playerPositions[2];

	sf::Texture texAxe; //������ �ؽ���
	SpriteGo* axe;

	bool isChopping; //ture�� �� ������ ��Ÿ��
	bool isAlive; //��������� true

	sf::Texture texRip; //�� �ؽ���
	sf::Texture& texPlayer;

	int score;

	sf::SoundBuffer soundBufferChop; //chop �Ҹ��� ����� ���� ����
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

	void Chop(Sides side); //������ ġ�� �׼�
	void Die(); //�÷��̾ ���� ��

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

