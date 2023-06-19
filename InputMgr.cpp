#include "InputMgr.h"
#include <algorithm>

std::list<sf::Keyboard::Key> InputMgr::downList; //������ ����
std::list<sf::Keyboard::Key> InputMgr::upList; //���� ����
std::list<sf::Keyboard::Key> InputMgr::ingList; //������ �ִ� ����

void InputMgr::Clear()
{
	downList.clear();
	upList.clear(); //����Ʈ ��ü ���� ����
}

void InputMgr::Update(const sf::Event& ev)
{
	switch (ev.type)
	{
	case sf::Event::KeyPressed: //Ű�� �����ִ� ���
		if (std::find(ingList.begin(), ingList.end(), ev.key.code) == ingList.end())
		{
			downList.push_back(ev.key.code);
			ingList.push_back(ev.key.code);
		}
		break;
	case sf::Event::KeyReleased:
		ingList.remove(ev.key.code); //���ڿ� �ش��ϴ� ���� ����Ʈ���� ��� ����
		upList.push_back(ev.key.code);
		break;
	}
}

bool InputMgr::GetKeyDown(sf::Keyboard::Key key)
{
	return std::find(downList.begin(), downList.end(), key) != downList.end();
}

bool InputMgr::GetKey(sf::Keyboard::Key key)
{
    return std::find(ingList.begin(), ingList.end(), key) != ingList.end();
}

bool InputMgr::GetKeyUp(sf::Keyboard::Key key)
{
    return std::find(upList.begin(), upList.end(), key) != upList.end();
}
