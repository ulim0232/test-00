#pragma once
#include "SpriteGo.h"
class EffectGo :public SpriteGo
{
protected:
	/*������ �������� ���ؼ� �ʿ��� ������
	1. ������ ��ġ, setpostion�Լ� �Ǵ� ������ ���
	- �ӵ�*�ð�: �̵��� �Ÿ�
	- �߷� ���ӵ�: ���ӵ�*�ð�, y�� ����ȴ�.
	������ �ð�*/

	sf::Vector2f velocity; //���� �ӵ� �ǹ�
	sf::Vector2f gravity; //�߷°��ӵ�

	float duration; //������Ʈ�� ������ �ð�
	float timer; //�ð� ������ ���
public:
	EffectGo(sf::Texture& tex,
		sf::Vector2f sptriteDir = sf::Vector2f(-1, -1),
		const std::string& n = "",
		const sf::Vector2f p = { 0, 0 });
	~EffectGo();
	void Fire(sf::Vector2f velo); //������Ʈ�� ������ ����

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

