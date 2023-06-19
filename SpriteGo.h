#pragma once
#include "GameObject.h"

//�������� �ʴ� ������Ʈ ��ü�� ����� Ŭ����

class SpriteGo : public GameObject
{
protected:
	sf::Sprite sprite;
	sf::Vector2f sptriteDir; //���� �̹����� ���� �ִ� ���� ����

public:
	SpriteGo(sf::Texture& tex, 
		sf::Vector2f spriteDir = sf::Vector2f(-1, -1), //�̰Ŵ� get, set �Լ��� ����ϴ� ���� �� ��������?
		const std::string& n = "",
		const sf::Vector2f p = { 0, 0 });
	virtual ~SpriteGo() override;

	virtual void SetPosition(const sf::Vector2f& p) override;
	virtual void SetPosition(float x, float y) override;
	virtual void SetOrigin(Origins origin) override;
	virtual void SetOrigin(float x, float y) override;

	sf::Vector2f GetSize() const;

	void SetTexture(sf::Texture& tex, sf::Vector2f sptriteDir = sf::Vector2f(-1, -1));
	//������ �������� �⺻��

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetFlipX(bool flip); //�ؽ����� ���� ����, ���ڰ� true�̸� ���� ����
	void SetFlipY(bool flip); //�ؽ����� ���� ����
};

