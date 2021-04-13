#include "game.hpp"
#include "interface_type.hpp"
#include "view.hpp"

#include "curses_view.hpp"
#include "curses_controller.hpp"

// #include "print_view.cpp"
// #include "view.cpp"
// #include "print_controller.cpp"
// #include "map_segment.cpp"

#include "map_segment.hpp"
#include "print_view.hpp"
#include "print_controller.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
// These should not have been here in the first place...
// #define INVALID_GAME_FILE_MSG "Invalid game input file"
// #define INVALID_LEVEL_FILE_MSG "Invalid level input file"
// #define INVALID_VIEW_TYPE_MSG "Invalid view type"

const int Game::MIN_VIEW_HEIGHT = 15;
const int Game::MIN_VIEW_WIDTH = 15;
const char Game::HERO_ICON_LEFT = '<';
const char Game::HERO_ICON_RIGHT = '>';
const char Game::HERO_ICON_UP = '^';
const char Game::HERO_ICON_DOWN = 'v';

Game::Game(const std::string &filename, InterfaceType interfaceType)
    : mView{nullptr}, mController{nullptr}, mInterfaceType{interfaceType}
{
    int i = 0;
    currentLV = 1;
    ifstream gameInfo;
    gameInfo.open(filename);
    if (gameInfo.is_open())
    {

        while (!gameInfo.eof())
        {
            if (i == 0)
            {
                gameInfo >> viewLenght >> viewWidth;
            }
            else if (i == 1)
            {
                gameInfo >> MaxLevel;
            }
            else
            {
                string mapLine;
                gameInfo >> mapLine;
                mapInfo.push_back(mapLine);
            }
            i++;
        }
        mapInfo.pop_back();
    }
    else
    {
        cout << "invalid file name" << endl;
    }

    //set up controller and view type
    if (mInterfaceType == InterfaceType ::Print)
    {

        mView = new PrintView{viewLenght, viewWidth};
        mController = new PrintController;
    }
    else
    {
        mView = new CursesView{viewLenght, viewWidth};
        mController = new CursesController;
    }
}
Game::~Game()
{
    delete mView;
    delete mController;
}

void Game::draw()
{
    if (InterfaceType::Curses == mInterfaceType)
    {
        
        cout << "Level: " << currentLV << '\r' << endl;
        cout << "Items remaining: " << numItem << '\r' << endl;
        cout << "Moves remaining: " << steps << '\r' << endl;
    }
    else
    {
        cout << "Level: " << currentLV << endl;
        cout << "Items remaining: " << numItem << endl;
        cout << "Moves remaining: " << steps << endl;
    }
}
void Game::loadLevel()
{

    numItem = 0;
    int i = 0;
    char Item;
    string fileName = "Example Game Files/";
    fileName = fileName + mapInfo[currentLV - 1];
    ifstream levelInfo;
    levelInfo.open(fileName);
    if (levelInfo.is_open())
    {

        while (!levelInfo.eof())
        {

            if (i == 0)
            {
                // start with map with ID
                levelInfo >> ID;
            }
            else if (i == 1)
            {
                // person coordinate
                levelInfo >> personY >> personX;
            }
            else if (i == 2)
            {
                // person facing direction
                levelInfo >> IniDirection;
                for (unsigned i = 0; i < Direction.size(); i++)
                {
                    if (!Direction[i].compare(IniDirection))
                    {
                        heroFacing = i;
                    }
                }
            }
            else
            {
                levelInfo >> Item;
                switch (Item)
                {
                case 'M':
                {
                    vector<int> intHolder;
                    int buf;
                    for (int i = 0; i < 2; i++)
                    {
                        levelInfo >> buf;
                        intHolder.push_back(buf);
                    }
                    map_SegInfo.push_back(intHolder);
                    break;
                }

                case 'B':
                {
                    vector<int> intHolder;
                    int buf;
                    for (int i = 0; i < 3; i++)
                    {
                        levelInfo >> buf;
                        intHolder.push_back(buf);
                    }
                    BuildingInfo.push_back(intHolder);
                    break;
                }
                case 'I':
                {
                    vector<int> intHolder;
                    int buf;
                    for (int i = 0; i < 3; i++)
                    {
                        levelInfo >> buf;
                        intHolder.push_back(buf);
                    }
                    targetInfo.push_back(intHolder);
                    numItem++;
                    break;
                }
                case 'P':
                {
                    int PID;
                    string PDire;
                    levelInfo >> PID;
                    levelInfo >> PDire;
                    portalID.push_back(PID);
                    portalDirection.push_back(PDire);
                    levelInfo >> PID;
                    levelInfo >> PDire;
                    portalID.push_back(PID);
                    portalDirection.push_back(PDire);
                    break;
                }
                case 'N':
                    levelInfo >> steps;
                    break;
                }
            }
            i++;
        }
    }

    else
    {
        cout << "not open" << endl;
    }
}

void Game::drawVectorStr(const std::vector<std::string> &lines)
{
    for (auto i : lines)
    {
        std::cout << i << std::endl;
    }
}
void Game::doGameLoop()
{
}

void Game::processFinal_screen(const vector<string> map, const vector<string> view)
{
    int centerX, centerY, initX, initY, map_coordinateX, map_coordinateY, replaceLen, startOfSub, endY, startOfY;
    Final_Screen = view;
    centerX = (viewWidth + 1) / 2;
    centerY = (viewLenght + 1) / 2;
    initX = centerX - personX;
    initY = centerY - personY;

    initX < 0 ? map_coordinateX = 0 : map_coordinateX = initX;
    initY < 0 ? map_coordinateY = 0 : map_coordinateY = initY;
    // for index of substring, starts at 0
    if (initX > 0)
    {
        initX = 0;
    }
    if (initY > 0)
    {
        initY = 0;
    }
    startOfSub = abs(initX);
    startOfY = abs(initY);
    // calculate the length of the X string need to be replace
    int X = viewWidth - map_coordinateX - map[0].length() - initX;
    int Y = viewLenght + 2 - map_coordinateY - map.size() - initY;
    X >= 0 ? replaceLen = initX + map[0].length() : replaceLen = viewWidth - map_coordinateX + 1;
    // calculate the length of the Y string need to be replace
    // cout<<X<<endl;
    Y >= 0 ? endY = initY + map.size() + map_coordinateY : endY = viewLenght + 2;
    for (int i = map_coordinateY; i < endY; i++)
    {
        Final_Screen[i].replace(map_coordinateX, replaceLen, map[startOfY].substr(startOfSub, replaceLen));
        startOfY++;
    }
    vector<int> holder{map_coordinateX, map_coordinateX + replaceLen - 1, map_coordinateY, endY - 1};
    mapCoordinate = holder;
    holder.clear();
    //modify the direction of arrow
    Final_Screen[centerY][centerX] = DirecSymbol[heroFacing];

    Final_Screen[0] = view[0];
    Final_Screen[Final_Screen.size() - 1] = view[0];

    for (unsigned i = 0; i < Final_Screen.size(); i++)
    {
        Final_Screen[i][0] = '*';
        Final_Screen[i][Final_Screen[0].size() - 1] = '*';
    }
    if (InterfaceType::Curses == mInterfaceType)
    {
        for (unsigned i = 0; i < Final_Screen.size(); i++)
        {

            Final_Screen[i].push_back('\r');
        }
    }
}

void Game::update()
{
    Command command;

start_over:
    command = mController->getInput();

    switch (command)
    {
    case Command::Forward:
    {
        // move right, personx +1; move up,personY -1

        // still need to check collisions

        switch (heroFacing)
        {
        // up
        case 0:
        {
            // for(auto i: mapCoordinate){
            //     cout<< i <<endl;
            // }
            // auto a = mMap->personInMap(personX, personY - 1);
            // auto b = mMap->NotHitBuilding(personX, personY - 1);
            // cout << "personInMap:" << a << endl;
            // cout << "NotHitBuilding:" << b << endl;
            if (mMap->personInMap(personX, personY - 1) && mMap->NotHitBuilding(personX, personY - 1))
            {
                // cout << "In" << endl;
                personY -= 1;
                steps -= 1;
            }
            checkIfCrossPortal(personX, personY - 1);
            break;
        }
        // right
        case 1:
        {
            // auto a = mMap->personInMap(personX + 1, personY);
            // auto b = mMap->NotHitBuilding(personX + 1, personY);
            // cout << "personInMap:" << a << endl;
            // cout << "NotHitBuilding:" << b << endl;
            if (mMap->personInMap(personX + 1, personY) && mMap->NotHitBuilding(personX + 1, personY))
            {
                personX += 1;
                steps -= 1;
            }
            checkIfCrossPortal(personX + 1, personY);
            break;
        }
        // down
        case 2:
        {
            // auto a = mMap->personInMap(personX, personY + 1);
            // auto b = mMap->NotHitBuilding(personX, personY + 1);
            // cout << "personInMap:" << a << endl;
            // cout << "NotHitBuilding:" << b << endl;
            if (mMap->personInMap(personX, personY + 1) && mMap->NotHitBuilding(personX, personY + 1))
            {
                personY += 1;
                steps -= 1;
            }
            checkIfCrossPortal(personX, personY + 1);
            break;
        }
        // left
        case 3:
        {
            // auto a = mMap->personInMap(personX - 1, personY);
            // auto b = mMap->NotHitBuilding(personX - 1, personY);
            // cout << "personInMap:" << a << endl;
            // cout << "NotHitBuilding:" << b << endl;
            if (mMap->personInMap(personX - 1, personY) && mMap->NotHitBuilding(personX - 1, personY))
            {
                personX -= 1;
                steps -= 1;
            }
            checkIfCrossPortal(personX - 1, personY);
            break;
        }
        }
        break;
    }
    case Command::Left:
    {
        if (heroFacing - 1 == -1)
        {
            heroFacing = 3;
        }
        else
        {
            heroFacing -= 1;
        }
        break;
    }
    case Command::Right:
    {
        if (heroFacing + 1 == 4)
        {
            heroFacing = 0;
        }
        else
        {
            heroFacing += 1;
        }
        break;
    }
    case Command::Quit:
    {
        quit = true;
        if (InterfaceType::Curses == mInterfaceType)
        {
            cout << "You quit the game." << '\r' << endl;
        }
        else
        {
            cout << "You quit the game." << endl;
        }

        break;
    }
    case Command::Invalid:
    {
        // cout << "Invalid Move" << endl;
        goto start_over;
        break;
    }
    }
}
void Game::checkIfCrossPortal(int y, int x)
{
    // cout<<"Y:"<<y<<" X:"<<x<<endl;

    for (unsigned i = 0; i < localMapPortal.size(); i++)
    {
        // cout<<"Sour y:"<<localMapPortal[i].first[1]<<" sour x:"<<localMapPortal[i].first[2]<<endl;
        // cout<<"dest ID"<<localMapPortal[i].second[0] <<"  dest__Py:"<<localMapPortal[i].second[1]<<" dest__Px:"<<localMapPortal[i].second[2]<<endl;
        if (localMapPortal[i].first[0] == ID && localMapPortal[i].first[2] == y && localMapPortal[i].first[1] == x)
        {
            // update the map info
            ID = localMapPortal[i].second[0];
            personY = localMapPortal[i].second[1];
            personX = localMapPortal[i].second[2];
        }
    }
}
void Game::run()
{
    //initialize all the game values
    win = false;
    lose = false;
    quit = false;
    nextLV = false;
    currentLV = 1;
    //load level when win the current level
        if (InterfaceType::Curses == mInterfaceType)
        {
            // cout<<"hereeeeeeeeeeeeeeeee-----------------"<<endl;
            initscr();
            // newterm(NULL, stdin, stdout);
            
            // printw("clear m,e!!!!!!!!!!!!!!!");
            // refresh();
        }
    loadLevel();
    

    //load another map when going into a portal or win anothor level.
    // cout<<"loadLV done!"<<endl;
    while (!lose && !win && !quit)
    {
        if (nextLV)
        {
            map_SegInfo.clear();
            BuildingInfo.clear();
            portalDirection.clear();
            portalID.clear();
            loadLevel();
            nextLV = false;
        }
        MapSegment map{map_SegInfo[ID][0], map_SegInfo[ID][1], ID, BuildingInfo, targetInfo, portalID, portalDirection, map_SegInfo};
        mMap = &map;
        localMapPortal = mMap->getlocalPortal();
        if (InterfaceType::Curses == mInterfaceType)
        {
        refresh();
        }
        // cout << "ID:" << ID << endl;
        // cout << "number of portal : " << mMap->numPortal << endl;
        // cout << "map H : " << mMap->getHeight() << "  map W : " << mMap->getWidth() << endl;


        draw();
        // drawVectorStr(map.getAsLines());
        processFinal_screen(mMap->getAsLines(), mView->getView());
        drawVectorStr(Final_Screen);
        // move(20,20);
        // refresh();
        update();
        
        // refresh();
        // check target
        if (mMap->getHasTarget())
        {
            auto tempTar = mMap->gettarget();
            for (auto T : tempTar)
            {
                if (T[0] == ID && T[1] == personY && T[2] == personX)
                {
                    // find and erase the target
                    for (unsigned i = 0; i < targetInfo.size(); i++)
                    {
                        if (targetInfo[i][0] == ID && T[1] == targetInfo[i][1] && T[2] == targetInfo[i][2])
                        {
                            targetInfo.erase(targetInfo.begin() + i);
                            mMap->eraseTarget(i, T[1], T[2]);
                        }
                    }
                    // update map so it does not think it still has target

                    numItem -= 1;
                }
            }
        }
        checkWin_Lose();
        // cout<<"current lv"<<currentLV<<endl;
        // cout<<"next lv"<<nextLV<<endl;
    }
    if (InterfaceType::Curses == mInterfaceType)
    {
        endwin();
    }
}
void Game::checkWin_Lose()
{
    if (numItem == 0)
    {
        // need to load next level
        currentLV += 1;
        nextLV = true;
    }
    if (numItem == 0 && currentLV == MaxLevel + 1)
    {
        win = true;
        // cout << "You won the game." << endl;
        if (InterfaceType::Curses == mInterfaceType)
        {
            cout << "You won the game." << '\r' << endl;
            
            
        }
        else
        {
            cout << "You won the game." << endl;
        }
    }

    if (steps == 0 && !win)
    {
        lose = true;
        if (InterfaceType::Curses == mInterfaceType)
        {
            cout << "You lost the game." << '\r' << endl;
        }
        else
        {
            cout << "You lost the game." << endl;
        }
    }
}
// int main()
// {
//     InterfaceType it = InterfaceType::Print;

//     Game g{"Example Game Files/game1.txt", it};
//     g.run();
//     return 0;
// }