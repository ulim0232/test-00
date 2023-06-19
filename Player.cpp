#include "Player.h"
#include "Tree.h"
#include "InputMgr.h"
#include "EffectGo.h"

#include <iostream>
using namespace std;

Player::Player(sf::Texture& tex, sf::Vector2f sptriteDir, const std::string& n, const sf::Vector2f p)
	:SpriteGo(tex, sptriteDir, n, p), offsetX(100.f), isChopping(false),
	texPlayer(tex), score(0)
{
	texAxe.loadFromFile("graphics/axe.png"); //axe의 이미지 로딩
	axe = new SpriteGo(texAxe); //axe할당

	SetOrigin(Origins::BC);
	for (auto& position : playerPositions)
	{
		position = p;
	}
	//처음에 생성된 y의 위치는 변경하지 않으면서 좌우만 바꾸기

	texRip.loadFromFile("graphics/rip.png");//비석 텍스쳐 로딩

	soundBufferChop.loadFromFile("sound/chop.wav"); //chop 사운드 로딩
	soundBufferDeath.loadFromFile("sound/death.wav"); //death 사운드 로딩
	soundBufferTimeOut.loadFromFile("sound/out_of_time.wav");

	soundChop.setBuffer(soundBufferChop);
	soundDeath.setBuffer(soundBufferDeath);
	soundTimeOut.setBuffer(soundBufferTimeOut);

}

Player::~Player()
{
}

void Player::SetTree(Tree* tree)
{
	this->tree = tree;
}

void Player::SetSide(Sides side)
{
	this->side = side;
	SetPosition(playerPositions[(int)this->side]);
	SetFlipX(this->side == Sides::Right);

	axe->SetPosition(GetPosition()); //axe의 위치를 플레이어의 위치와 일치시키기
	axe->SetFlipX(this->side == Sides::Right);
}

Sides Player::GetSide() const
{
	return side;
}

void Player::Chop(Sides side)
{
	SetSide(side);
	isChopping = true;
}

void Player::Die()
{
	isAlive = false;
	isChopping = false; //도끼질을 하는 도중에 죽엇을 경우 대비
	SetTexture(texRip); //texture를 묘비로 변경
	SetOrigin(Origins::BC); //settexture를 하면 항상 오리진도 세팅
	SetFlipX(true); //왼쪽에서 죽었을 경우 이미지 반전하면 x
}

void Player::SetPosition(const sf::Vector2f& p)
{
	SpriteGo::SetPosition(p);
}

void Player::SetPosition(float x, float y)
{
	SpriteGo::SetPosition(x, y);
}

void Player::Init()
{
	score = 0;
	isAlive = true;
	SetTexture(texPlayer);
	SetOrigin(Origins::BC);

	isChopping = false;

	SpriteGo::Init();

	sf::Vector2f playerSize = GetSize();

	float treeHalfWidth = tree->GetSize().x * 0.5f;
	float playerHalfWidth = playerSize.x * 0.5f;
	float delta = treeHalfWidth + playerHalfWidth + offsetX;

	//각 방향(왼오)로 가야할 때의 x값을 미리 계산
	playerPositions[(int)Sides::Left].x = tree->GetPosition().x - delta;
	playerPositions[(int)Sides::Right].x = tree->GetPosition().x + delta;

	//마지막 나뭇가지와 반대편으로 위치 지정, 가지가 side와 반대로 그려지기 때문에 같게 해줌
	if (tree->GetBranchSide() == Sides::Right)
	{
		SetSide(Sides::Left);
	}
	else if (tree->GetBranchSide() == Sides::Left)
	{
		SetSide(Sides::Right);
	}
	else
	{
		SetSide(Sides::Right);
		cout << "Something wrong" << endl;
	}

	/*--axe의 피봇을 플레이어의 가운데+절반의 길이로 설정--*/
	sf::Vector2f axeSize = axe->GetSize();
	axe->SetOrigin(axeSize.x + playerHalfWidth, GetSize().y * 0.45f);

	axe->Init(); 
	axe->SetPosition(GetPosition());
}

void Player::Release()
{
	delete axe;
	axe = nullptr;
	SpriteGo::Release();
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);
	if (!isAlive)
		return;

	if(!isChopping)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Left))
		{
			Chop(Sides::Left);
			soundChop.play();
			if (!isCrashed()) //부딪히지 않았을 경우에 점수증가
			{
				score++;
			}
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Right))
		{
			Chop(Sides::Right);
			soundChop.play();
			if (!isCrashed())
			{
				score++;
			}
		}
	}
	else
	{
		if (GetSide() == Sides::Left && InputMgr::GetKeyUp(sf::Keyboard::Left))
		{
			isChopping = false;
		}
		if (GetSide() == Sides::Right && InputMgr::GetKeyUp(sf::Keyboard::Right))
		{
			isChopping = false;
		}
	}
	axe->Update(dt);
}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);

	if (isChopping)
	{
		axe->Draw(window);
	}
}

bool Player::isCrashed() //나뭇가지와 부딪혔는지
{
	Sides branchSide = tree->GetBranchSide();
	return (this->side == branchSide);
	//if (this->side != branchSide) //나뭇가지 방향은 side값과 반대임
	//{
	//	return true;
	//}
	//return false;
}

int Player::GetScore()
{
	return score;
}

void Player::PlayDeathSound()
{
	soundDeath.play();
}

void Player::PlayTimeOutSound()
{
	soundTimeOut.play();
}
