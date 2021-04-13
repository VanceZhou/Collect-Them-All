#ifndef GAME_HPP
#define GAME_HPP

#include "controller.hpp"
#include "view.hpp"
#include "interface_type.hpp"
#include "map_segment.hpp"
#include <vector>
#include <string>
#include <utility>
using namespace std;
class Game
{
public:  // public methods
    /**
     * DO NOT change the prototype of this function.
     * The autograder WILL call this function.
     */
    Game(const std::string& filename, InterfaceType interfaceType);

    ~Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    
    /**
     * DO NOT change the prototype of this function.
     * The autograder WILL call this function.
     */
    void run();

private:  // private methods
    /**
     * You DO NOT need to have any of the private methods below.
     * I just left some commented out declarations in case it
     * helps guide your thinking, but you don't need to use them.
     */

    /**
     * Set up the 1D vector of strings that is then given to the draw()
     * method of an instance of a subclass of View.
     */
    void draw();
    void processFinal_screen( const vector<string> map, const vector<string> View);
    /**
     * Loop until the game is over. On each iteration, use the controller
     * to get input from the user.
     */
    void doGameLoop();
    void checkWin_Lose();
    /**
     * Update matters related to game logic, e.g. collisions, level completion.
     */
    void update();
    void drawVectorStr(const std::vector<std::string> &lines);
    /**
     * Load information related to new level into member variables,
     * being careful to not leave traces of information from previous levels. 
     */
    void loadLevel();
    void checkIfCrossPortal(int y, int x);
private:
    string DirecSymbol = "^>v<";
    vector<string> Direction {"up", "right","down", "left"};
    // 4 int, X_start,X_end, Y_start,Y_end, used to check if hero inside map.
    vector<int> mapCoordinate;
    int heroFacing;
    int viewWidth;
    int viewLenght;
    int MaxLevel;
    int currentLV, numItem, steps;
    vector<string> Final_Screen;
    bool win;
    bool lose;
    bool quit;
    bool nextLV;
    string IniDirection;
    int ID, personX, personY;
    vector<vector<int>> BuildingInfo, targetInfo,map_SegInfo;
    // index 0 is source, index1 is destination
    vector<int> portalID;
    vector<string> portalDirection;
    // pair.first is source ID+(x,y), pair.second is desti ID+(x,y)
    vector<pair<vector<int>, vector<int>>> localMapPortal;
    std::vector<std::string> mapInfo;
    static const int MIN_VIEW_HEIGHT;
    static const int MIN_VIEW_WIDTH;
    static const char HERO_ICON_LEFT;
    static const char HERO_ICON_RIGHT;
    static const char HERO_ICON_UP;
    static const char HERO_ICON_DOWN;

    /**
     * Because one of the constructor parameters must be checked in order
     * to determine the subclass types for the below members, they can't
     * be references, because there's no default constructors for them.
     * (Recall that each member in a class must either be initialized by an
     * initializer list in the constructor OR have a default constructor.)
     */
    View* mView;
    Controller* mController;
    MapSegment* mMap;
    InterfaceType mInterfaceType;
};

#endif // GAME_HPP
