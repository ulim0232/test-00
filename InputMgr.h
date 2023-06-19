#pragma once
#include<SFML/Graphics.hpp>
#include<list>

//Ű �Է��� �����ϴ� Ŭ����
class InputMgr
{
private:
	//���ø����� �����Ǿ��ִ� ����Ʈ, ������ ���������� ����
	static std::list<sf::Keyboard::Key> downList; //������ ����
	static std::list<sf::Keyboard::Key> upList; //���� ����
	static std::list<sf::Keyboard::Key> ingList; //������ �ִ� ����
public:
	static void Clear(); //�����Ӹ��� �ٿ�,�� ����Ʈ ����
	static void Update(const sf::Event& ev);

	static bool GetKeyDown(sf::Keyboard::Key key); //������ �� ����
	static bool GetKey(sf::Keyboard::Key key); //������������ ��
	static bool GetKeyUp(sf::Keyboard::Key key); //�������� �Ѽ���
};

