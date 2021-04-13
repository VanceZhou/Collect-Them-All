#include "building.hpp"
#include <iostream>
const int Building::width = 6;
const int Building::height = 4;

Building::Building(int y, int x)
    : mY(y), mX(x)
{
    std::string BuildingLine1 = "......";
    std::string BuildingLine2 = "..&&..";
    building.push_back(BuildingLine1);
    building.push_back(BuildingLine1);
    building.push_back(BuildingLine2);
    building.push_back(BuildingLine2);


}
