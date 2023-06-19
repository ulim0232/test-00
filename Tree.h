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

	sf::Texture texLog; //통나무 텍스쳐

	std::list<EffectGo*> logPool; //비활성화된 texLog 저장
	std::list<EffectGo*> logEffects; //통나무 날아가는 모션, 활성화된 texLog 저장
	/*사전에 logPool에 여러개의 texLog를 만들고 사용할 때마다
	하나씩 가져와 활성화시키고 logEffects에 저장하고 사용이 끝나면 비활*/

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
	void ShowEffectLog(Sides side, sf::Vector2f position); //이펙트를 바깥에서 호출해주는 함수

	Sides GetBranchSide();
};

