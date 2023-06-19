#include <SFML/Graphics.hpp>
#include <vector>
#include <sstream>

#include "Utils.h"
#include "MovingBgObj.h"
#include "InputMgr.h"
#include "Branch.h"
#include "Tree.h"

#include "Player.h"

int main()
{
    bool isPause = true; //일시정지
    int score = 0;

    int screenWidth = 1920;
    int screenHeight = 1080;

    /*폰트를 를 활용해서 화면에 글씨를 적어보기*/
    /*----시작 메시지 설정----*/
    sf::Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");  //"~"경로에서 폰트 파일 가져오기
    sf::Text textMassage;
    textMassage.setFont(font);
    textMassage.setString("PRESS ENTER TO START"); //문자열 지정
    textMassage.setCharacterSize(75); //크기 지정
    textMassage.setFillColor(sf::Color::White); //텍스트의 색상
    Utils::SetOrigin(textMassage, Origins::MC);
    textMassage.setPosition(screenWidth * 0.5f, screenHeight * 0.5f); //위치 지정


    /*----점수 표기 메세지 설정----*/
    sf::Text textScore;
    textScore.setFont(font);
    textScore.setString("SCORE: ???");
    textScore.setCharacterSize(100);
    textScore.setFillColor(sf::Color::Cyan);
    Utils::SetOrigin(textScore, Origins::TL);
    textScore.setPosition(20.f, 20.f);

    /*-----타이머 UI 설정-----*/
    /*시간이 흐를 수록 줄어드는 게이지
    width를 시간만큼 크기를 줄여가면서 사이즈 할당*/
    float uiTimerWidth = 400.f;
    float uiTimerHeight = 80.f;
    
    float duration = 3.f; //제한시간 3초
    float timer = duration; //dt를 빼가면서 측정

    sf::RectangleShape uiTimer;
    uiTimer.setSize(sf::Vector2f(uiTimerWidth, uiTimerHeight)); //size 설정
    Utils::SetOrigin(uiTimer, Origins::BC);
    uiTimer.setPosition(screenWidth * 0.5f, screenHeight - 50.f);//50픽셀 위로 올리기
    uiTimer.setFillColor(sf::Color::Red);


    /*------texture 설정-----*/
    sf::Texture texBackground;
    texBackground.loadFromFile("graphics/background.png");
    sf::Texture texTree;
    texTree.loadFromFile("graphics/tree.png");
    sf::Texture texCloud;
    texCloud.loadFromFile("graphics/cloud.png");
    sf::Texture texBee;
    texBee.loadFromFile("graphics/bee.png");
    sf::Texture texBranch;
    texBranch.loadFromFile("graphics/branch.png");
    sf::Texture texPlayer;
    texPlayer.loadFromFile("graphics/player.png");

    // 1. Init
    std::vector<GameObject*> gameObjects;
    gameObjects.push_back(new SpriteGo(texBackground, sf::Vector2f(1.f, 0.f), "BG", {0, 0}));
    
    for (int i = 0; i < 3; i++)//구름 3개 그리기, 배경 위 나무 아래
    {
        /*----구름생성----*/
        MovingBgObj* newGo = new MovingBgObj(texCloud, sf::Vector2f(-1.f, 0.f), "Cloud");
        newGo->SetSpeedRange(sf::Vector2f(300.f, 600.f));
        newGo->SetLRPos(sf::Vector2f(-200.f, 1080.f / 2.f), //시작 위치 고정
            sf::Vector2f(1920.f + 200.f, 1080.f / 2.f));

        newGo->SetPosXRange(0, 0);
        newGo->SetPosYRange(-300, 300);

        gameObjects.push_back(newGo);
    }
    /*----나무 생성----*/
    Tree* tree = new Tree(texTree, sf::Vector2f(1.f, 0.f), "Tree");
    tree->SetOrigin(Origins::TC);
    tree->SetPosition(sf::Vector2f(screenWidth * 0.5f, 0.f));
    gameObjects.push_back(tree);


    /*-----플레이어 생성-----*/
    Player* player = new Player(texPlayer, sf::Vector2f(-1.f, -1.f), "Player", sf::Vector2f(0.f, 900.f));
    player->SetTree(tree);
    gameObjects.push_back(player);

    /*----벌 생성----*/
    MovingBgObj* newGo = new MovingBgObj(texBee, sf::Vector2f(-1.f, -1.f), "Bee");
    newGo->SetSpeedRange(sf::Vector2f(100.f, 200.f));
    newGo->SetLRPos(sf::Vector2f(-200.f, 1080.f / 2.f), //시작 위치 고정
        sf::Vector2f(1920.f + 200.f, 1080.f / 2.f));
    newGo->SetPosXRange(0, 0);
    newGo->SetPosYRange(0, 300);
    newGo->SetMoveY(5.f, 50.f);
    gameObjects.push_back(newGo);
    
    /*-----초기화-----*/
    for (auto obj : gameObjects)
    {
        obj->Init();
    }

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Timber!", sf::Style::Default);

    sf::Clock clock;
    while (window.isOpen())
    {
        InputMgr::Clear();

        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            InputMgr::Update(event);

            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            }          
        }
        if (!isPause)
        {
            /*----타이머----*/
            timer -= dt;
        
            if (timer < 0.f)
            {
                player->PlayTimeOutSound();
                textMassage.setFillColor(sf::Color::Red);
                textMassage.setString("TimeOut");
                Utils::SetOrigin(textMassage, Origins::MC);
                player->Die();
                isPause = true; //제한 시간이 종료되면 정지
            }
            else
            {
                float normTime = timer / duration;
                float timeSizeX = uiTimerWidth * normTime;
                uiTimer.setSize(sf::Vector2f(timeSizeX, uiTimerHeight));

                for (auto obj : gameObjects)
                {
                    if(obj->GetActive())//활성화된 경우에만 업데이트
                    {
                        obj->Update(dt); //구름, 벌 등의 변화 진행
                    }
                }

                score = player->GetScore();//점수 받아오기

                /*----score 출력----*/
                std::stringstream ss;
                ss << "SCORE: " << score;
                textScore.setString(ss.str());
                
                /*----나뭇가지 맞아서 죽음----*/
                if (player->isCrashed())
                {
                    player->Die();
                    player->PlayDeathSound();
                    textMassage.setFillColor(sf::Color::Blue);
                    textMassage.setString("Game Over!!");
                    Utils::SetOrigin(textMassage, Origins::MC);
                    isPause = true;
                }
                //나무 벨 때 시간 0.3초 증가
                else if (InputMgr::GetKeyDown(sf::Keyboard::Left) || InputMgr::GetKeyDown(sf::Keyboard::Right))
                {
                    if (timer + 0.3f > duration)
                    {
                        timer = duration;
                    }
                    else
                        timer += 0.3f;
                }
            }
        }
        /*-----엔터키 입력으로 시작-----*/
        else
        {
            //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            if(InputMgr::GetKeyDown(sf::Keyboard::Return))
            {
                isPause = false;
                timer = duration; //타이머 다시 채우기
                score = 0; //점수 초기화
                for (auto obj : gameObjects)
                {
                    if(obj->GetActive())
                    {
                        obj->Init();
                    }
                }
            }
        }
       
        window.clear();
        // 3. Draw

        for (auto obj : gameObjects)
        {
            obj->Draw(window);
        }
        
        window.draw(textScore);
        window.draw(uiTimer);
        if(isPause) //일시정지 중일 때만 press enter 띄우기
        {
            window.draw(textMassage);
        }
        window.display();
    }

    for (auto obj : gameObjects)
    {
        obj->Release();
        delete obj;
    }

    return 0;
}