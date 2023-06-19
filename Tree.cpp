#include "Tree.h"
#include "Utils.h"
#include "InputMgr.h"
#include <iostream>

Tree::Tree(sf::Texture& tex, sf::Vector2f spriteDir, const std::string& n, const sf::Vector2f p)
	: SpriteGo(tex, spriteDir, n, p), countOfBranches(6), branches(countOfBranches), branchPositions(countOfBranches), currentBranch(0)
{
	texBranch.loadFromFile("graphics/branch.png");
	texLog.loadFromFile("graphics/Log.png");

	for (auto& branch : branches)
	{
		branch = new Branch(texBranch, { -1.f, -1.f}, "Branch");
		branch->SetTree(this);
	}

	for (int i = 0; i < 100; i++) //effectlog를 임시로 100개 생성
	{
		EffectGo* newGo = new EffectGo(texLog);
		newGo->SetActive(false);
		logPool.push_back(newGo);
	}
}

Tree::~Tree()
{

}

void Tree::Init()
{
	SpriteGo::Init();

	currentBranch = 0;

	float x = GetPosition().x;
	float y = 800.f;
	float offset = branches[0]->GetSize().y + 100;
	branchSide = Sides::None;

	for (int i = 0; i < branchPositions.size(); ++i)
	{
		branchPositions[i].x = x;
		branchPositions[i].y = y;
		y -= offset;
	}

	for (int i = 0; i < branchPositions.size(); ++i)
	{
		branches[i]->Init();
		branches[i]->SetPosition(branchPositions[i]);
		Sides side = (Sides)Utils::RandomRange(0, 1); //(0,2)에서 변경
		branches[i]->SetSide(side);

		if (i == 0) //(초기)가장 아래 가지의 좌표
		{
			branchSide = side;
		}
	}
}

void Tree::Release()
{
	SpriteGo::Release();

	for (auto& branch : branches)
	{
		delete branch;
		branch = nullptr;
	}
	branches.clear();

	for (auto& effect : logPool)
	{
		delete effect;
		effect = nullptr;
	}
	logPool.clear();

	for (auto& effect : logEffects)
	{
		delete effect;
		effect = nullptr;
	}
	logEffects.clear();
}

void Tree::Update(float dt)
{
	SpriteGo::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Left))
	{
		UpdateBranches();
		sf::Vector2f pos = GetPosition();
		pos.y = GetSize().y;
		ShowEffectLog(Sides::Right, pos);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		UpdateBranches();
		sf::Vector2f pos = GetPosition();
		pos.y = GetSize().y;
		ShowEffectLog(Sides::Left, pos);
	}
	auto it = logEffects.begin();
	while (it != logEffects.end())
	{
		if ((*it)->GetActive())
		{
			(*it)->Update(dt);
			++it;
		}
		else
		{
			logPool.push_back(*it);
			it = logEffects.erase(it);
		}
		
	}
}

void Tree::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	for (auto branch : branches)
	{
		branch->Draw(window);
	}
	for (auto effect : logEffects)
	{
		effect->Draw(window);
	}
}

void Tree::UpdateBranches()
{
	currentBranch = (currentBranch + 1) % branches.size();
	// 1, 2, 3, 4, 5, 0 순서로 값이 돌아감
	int index;
	for (int i = 0; i < branches.size(); ++i)
	{
		index = (currentBranch + i) % branches.size();
		branches[index]->SetPosition(branchPositions[i]);
		if (i == branches.size() - 1)
		{
			Sides side = (Sides)Utils::RandomRange(0, 1);
			branches[index]->SetSide(side);
		}
		if (i == 0)
		{
			branchSide = branches[index]->GetSide();
			//업데이트 후 가장 아래 가지의 side
		}
	}
}

void Tree::ShowEffectLog(Sides side, sf::Vector2f position)
{
	//logpool에서 가져와 초기화하고 활성화한 다음에 날리기

	if (logPool.empty())//pool이 비어있는 경우 체크
	{
		std::cout << "Log Pool Empty" << std::endl;
		return;
	}

	EffectGo* log = logPool.front(); //가장 앞의 래퍼런스 리턴
	logPool.pop_front(); //가장 앞의 값을 뺀다
	logEffects.push_back(log);

	log->SetActive(true);
	log->Init();
	log->SetPosition(position);
	log->Fire(sf::Vector2f(side == Sides::Right ? 1000.f : -1000.f, -1000.f));
	
}

Sides Tree::GetBranchSide() //가장 아래 가지의 side 리턴
{
	return branchSide;
}
