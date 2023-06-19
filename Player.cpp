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
	texAxe.loadFromFile("graphics/axe.png"); //axe�� �̹��� �ε�
	axe = new SpriteGo(texAxe); //axe�Ҵ�

	SetOrigin(Origins::BC);
	for (auto& position : playerPositions)
	{
		position = p;
	}
	//ó���� ������ y�� ��ġ�� �������� �����鼭 �¿츸 �ٲٱ�

	texRip.loadFromFile("graphics/rip.png");//�� �ؽ��� �ε�

	soundBufferChop.loadFromFile("sound/chop.wav"); //chop ���� �ε�
	soundBufferDeath.loadFromFile("sound/death.wav"); //death ���� �ε�
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

	axe->SetPosition(GetPosition()); //axe�� ��ġ�� �÷��̾��� ��ġ�� ��ġ��Ű��
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
	isChopping = false; //�������� �ϴ� ���߿� �׾��� ��� ���
	SetTexture(texRip); //texture�� ����� ����
	SetOrigin(Origins::BC); //settexture�� �ϸ� �׻� �������� ����
	SetFlipX(true); //���ʿ��� �׾��� ��� �̹��� �����ϸ� x
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

	//�� ����(�޿�)�� ������ ���� x���� �̸� ���
	playerPositions[(int)Sides::Left].x = tree->GetPosition().x - delta;
	playerPositions[(int)Sides::Right].x = tree->GetPosition().x + delta;

	//������ ���������� �ݴ������� ��ġ ����, ������ side�� �ݴ�� �׷����� ������ ���� ����
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

	/*--axe�� �Ǻ��� �÷��̾��� ���+������ ���̷� ����--*/
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
			if (!isCrashed()) //�ε����� �ʾ��� ��쿡 ��������
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

bool Player::isCrashed() //���������� �ε�������
{
	Sides branchSide = tree->GetBranchSide();
	return (this->side == branchSide);
	//if (this->side != branchSide) //�������� ������ side���� �ݴ���
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
