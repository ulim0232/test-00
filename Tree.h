#pragma once
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>
#include "SpriteGo.h"
#include "Branch.h"
#include "EffectGo.h"

class Tree : public SpriteGo
{
protected:
	int countOfBranches;
	std::vector<Branch*> branches;
	std::vector<sf::Vector2f> branchPositions;
	int currentBranch;
	sf::Texture texBranch;

	sf::Texture texLog; //�볪�� �ؽ���

	std::list<EffectGo*> logPool; //��Ȱ��ȭ�� texLog ����
	std::list<EffectGo*> logEffects; //�볪�� ���ư��� ���, Ȱ��ȭ�� texLog ����
	/*������ logPool�� �������� texLog�� ����� ����� ������
	�ϳ��� ������ Ȱ��ȭ��Ű�� logEffects�� �����ϰ� ����� ������ ��Ȱ*/

	Sides branchSide;

public:
	Tree(sf::Texture& tex,
		sf::Vector2f spriteDir = sf::Vector2f(-1, -1),
		const std::string& n = "",
		const sf::Vector2f p = { 0, 0 });
	~Tree() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void UpdateBranches();
	void ShowEffectLog(Sides side, sf::Vector2f position); //����Ʈ�� �ٱ����� ȣ�����ִ� �Լ�

	Sides GetBranchSide();
};

