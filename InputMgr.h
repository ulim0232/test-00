#pragma once
#include<SFML/Graphics.hpp>
#include<list>

//키 입력을 관리하는 클래스
class InputMgr
{
private:
	//템플릿으로 구현되어있는 리스트, 저장할 데이터형을 지정
	static std::list<sf::Keyboard::Key> downList; //누르는 순간
	static std::list<sf::Keyboard::Key> upList; //떼는 순간
	static std::list<sf::Keyboard::Key> ingList; //누르고 있는 동안
public:
	static void Clear(); //프레임마다 다운,업 리스트 갱신
	static void Update(const sf::Event& ev);

	static bool GetKeyDown(sf::Keyboard::Key key); //누르는 한 순간
	static bool GetKey(sf::Keyboard::Key key); //눌려져있으면 참
	static bool GetKeyUp(sf::Keyboard::Key key); //떨어지는 한순간
};

