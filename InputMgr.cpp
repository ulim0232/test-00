#include "InputMgr.h"
#include <algorithm>

std::list<sf::Keyboard::Key> InputMgr::downList; //누르는 순간
std::list<sf::Keyboard::Key> InputMgr::upList; //떼는 순간
std::list<sf::Keyboard::Key> InputMgr::ingList; //누르고 있는 동안

void InputMgr::Clear()
{
	downList.clear();
	upList.clear(); //리스트 전체 내용 삭제
}

void InputMgr::Update(const sf::Event& ev)
{
	switch (ev.type)
	{
	case sf::Event::KeyPressed: //키가 눌려있는 경우
		if (std::find(ingList.begin(), ingList.end(), ev.key.code) == ingList.end())
		{
			downList.push_back(ev.key.code);
			ingList.push_back(ev.key.code);
		}
		break;
	case sf::Event::KeyReleased:
		ingList.remove(ev.key.code); //인자에 해당하는 값을 리스트에서 모두 삭제
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
