#ifndef MAP_SEGMENT_HPP
#define MAP_SEGMENT_HPP

#include <string>
#include <vector>

#include "building.hpp"
#include "item.hpp"


// #include "building.cpp"
// #include "item.cpp"
using namespace std;
/**
 * This is probably the class that will have the second biggest portion of
 * your code for this assignment. (The biggest would likely be held
 * by the Game class.)
 *
 * Some things I did that you don't have to do:
 * - Define an enum class for portal directions.
 * - Method for connecting two map segments' portals.
 * - Methods for adding buildings or items to a map segment.
 */

class MapSegment
{
public:

    MapSegment(int height, int width,int ID, vector<vector<int>> BuildingInfo, vector<vector<int>> targetInfo, vector<int> portalID, vector<string> portalDirection,vector<vector<int>> map_SegInfo);

    int getHeight() const { return mHeight; }
    int getWidth() const { return mWidth; }
    int getPortalX() const { return mPortalX; }
    int getPortalY() const { return mPortalY; }
    vector<vector<int>> gettarget() const { return targetInfomation; }
    vector<pair<vector<int>, vector<int>>> getlocalPortal() const { return localPortal; }
    bool getHasTarget() const { return hasTarget; }
    bool personInMap(int X, int Y);
    bool NotHitBuilding(int X, int Y);
    void eraseTarget(int i, int y, int x);
    vector<int> getDestXY(string direction, int destID);
    /**
     * Returns representation of this map segment as a vector of strings,
     * including any contained items and buildings.
     */
    std::vector<std::string> getAsLines() const {return lineMap;}
    
    int numPortal;

private:
    static char VERTICAL_BORDER_CHAR;
    static char HORIZONTAL_BORDER_CHAR;
    static char PORTAL_CHAR;    
    bool No_building;
    bool hasTarget;
    vector<vector<int>> localMaptarget;
    
    
    std::vector<std::string> lineMap;
    vector<pair<vector<int>, vector<int>>> localPortal;
    /**
     * As always, you don't need to have these member variables if you don't
     * think they would be useful to you.
     */
    int mHeight;
    int mWidth;
    int ID;
    vector<int> BuildingData;
    vector<vector<int>> Mymap_SegInfo;
    vector<vector<int>> targetInfomation;
    /**
     * For helping position the portals.
     * See how they are initialized in the constructor.
     */
    int mPortalY;
    int mPortalX;
};

#endif // MAP_SEGMENT_HPP
