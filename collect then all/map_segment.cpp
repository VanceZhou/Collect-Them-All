#include "map_segment.hpp"

using namespace std;
char MapSegment::VERTICAL_BORDER_CHAR = '|';
char MapSegment::HORIZONTAL_BORDER_CHAR = '=';
char MapSegment::PORTAL_CHAR = '@';

MapSegment::MapSegment(int height, int width, int ID, vector<vector<int>> BuildingInfo, vector<vector<int>> targetInfo, vector<int> portalID, vector<string> portalDirection,vector<vector<int>>map_SegInfo)
    : mHeight(height), mWidth(width),ID(ID), Mymap_SegInfo(map_SegInfo),targetInfomation(targetInfo), mPortalY{(mHeight - 1) / 2}, mPortalX{(mWidth - 1) / 2}
{
    string line;
    for (int i = 0; i < mHeight; i++)
    {
        for (int j = 0; j < mWidth; j++)
        {
            if (i == 0 || i == mHeight - 1)
            {
                line.push_back(HORIZONTAL_BORDER_CHAR);
            }
            else
            {
                line.push_back(' ');
            }
        }
        if ((i != 0) && (i != mHeight - 1))
        {
            line[0] = VERTICAL_BORDER_CHAR;
            line[mWidth - 1] = VERTICAL_BORDER_CHAR;
        }

        lineMap.push_back(line);
        // lineMap = lineMap_h;
        line.clear();
    }

    // print building
    No_building = true;
    for (auto buil : BuildingInfo)
    {
        if (buil[0] == ID)
        {
            int j = 0;
            Building B{buil[1], buil[2]};
            for (int i = buil[1]; i < buil[1] + B.getH(); i++)
            {
                lineMap[i].replace(buil[2], B.getW(), B.getBuilding()[j]);
                j++;
            }
            No_building = false;
            vector<int> holder = {buil[2], buil[1], buil[2] + B.getW()-1, buil[1] + B.getH()-1};
            BuildingData = holder;
            holder.clear();
        }
    }
    // print target
    hasTarget = false;
    //find all the targets that has the same ID as the current map
    for (auto targ : targetInfomation)
    {
        if (targ[0] == ID)
        {
            Item I{targ[1], targ[2]};
            lineMap[targ[1]][targ[2]] = I.ICON;
            vector<int> targetHolder{targ[1],targ[2]};
            localMaptarget.push_back(targetHolder);
            targetHolder.clear();
            hasTarget = true;
        }
    }
    //print portal, find all the portals that has the same map ID and print it one by one!
    int desINd;
    numPortal=0;
    localPortal.clear();
    for(unsigned i =0; i<portalID.size();i++){
        if(i%2 == 0){
            desINd = i+1;
        }
        else if(i%2 == 1){
            desINd = i-1;
        }

        if(portalID[i]==ID){
            if(!portalDirection[i].compare("up") ){
                lineMap[0][mPortalX] = PORTAL_CHAR;
                vector<int> source = {ID, 0 ,mPortalX};
                vector<int> xyHolder = getDestXY(portalDirection[desINd],portalID[desINd] );
                vector<int> destination {portalID[desINd],xyHolder[0],xyHolder[1]};
                pair<vector<int>,vector<int>> SourDest (source,destination);
                localPortal.push_back(SourDest);
            }
            else if(!portalDirection[i].compare("down")){

                lineMap[mHeight][mPortalX] = PORTAL_CHAR;
                vector<int> source = {ID, mHeight ,mPortalX};
                vector<int> xyHolder = getDestXY(portalDirection[desINd],portalID[desINd] );
                vector<int> destination {portalID[desINd],xyHolder[0],xyHolder[1]};
                pair<vector<int>,vector<int>> SourDest (source,destination);
                localPortal.push_back(SourDest);
            }
            else if(!portalDirection[i].compare("left")){
                // cout<<"in left"<<endl;
                lineMap[mPortalY][0] = PORTAL_CHAR;
                vector<int> source = {ID, mPortalY ,0};
                vector<int> xyHolder = getDestXY(portalDirection[desINd],portalID[desINd] );
                vector<int> destination {portalID[desINd],xyHolder[0],xyHolder[1]};
                pair<vector<int>,vector<int>> SourDest (source,destination);
                localPortal.push_back(SourDest);
            }
            else if(!portalDirection[i].compare("right")){
                // cout<<"in right"<<endl;
                lineMap[mPortalY][mWidth-1] = PORTAL_CHAR;
                vector<int> source = {ID, mPortalY ,mWidth-1};


                
                // cout<<"course XXX :::  "<<source[2]<<endl;
                vector<int> xyHolder = getDestXY(portalDirection[desINd],portalID[desINd] );
                vector<int> destination {portalID[desINd],xyHolder[0],xyHolder[1]};
                pair<vector<int>,vector<int>> SourDest (source,destination);
                localPortal.push_back(SourDest);
            }
        numPortal++;    
        }
    }

}
vector<int> MapSegment::getDestXY(string direction, int destID){

    vector<int> yx;
    yx.clear();
    int mX = (Mymap_SegInfo[destID][1] - 1) / 2;
    int mY = (Mymap_SegInfo[destID][0] - 1) / 2;
            if(!direction.compare("up") ){
                yx.push_back(1);
                yx.push_back(mX);
            }
            else if(!direction.compare("down")){
                yx.push_back(Mymap_SegInfo[destID][0]-1);
                yx.push_back(mX);
                
            }
            else if(!direction.compare("left")){
                yx.push_back(mY);
                yx.push_back(1);
               
            }
            else if(!direction.compare("right")){
                yx.push_back(mY);
                yx.push_back(Mymap_SegInfo[destID][1]-2);
                
            }
            return yx;
}
bool MapSegment::personInMap(int X, int Y)
{
    // cout<<"X: "<<X<<"Y: "<<Y<<endl;
    // cout<<"width: "<<mWidth<<" height: "<<mHeight<<endl;
    if (X > 0 && X < mWidth - 1 && Y > 0 && Y < mHeight - 1)
    {
        return true;
    }
    return false;
}
bool MapSegment::NotHitBuilding(int X, int Y)
{
    
    // cout << "X: " << X << "  Y: " << Y << endl;
    // cout << "X_start: " << BuildingData[0] << " X_end: " << BuildingData[2] << "Y_start: " << BuildingData[1] << " Y_end: " << BuildingData[3] << endl;
    if (!No_building)
    {
        if ((X < BuildingData[0] || X > BuildingData[2]) && (Y < BuildingData[1] || Y > BuildingData[3]))
        {
            return true;
        }

        else if (X >= BuildingData[0] && X <= BuildingData[2] && (Y < BuildingData[1] || Y > BuildingData[3]))
        {
            return true;
        }
        else if ((X < BuildingData[0] || X > BuildingData[2]) && Y >= BuildingData[1] && Y <= BuildingData[3])
        {
            return true;
        }
        else{
            return false;
        }
    }
    return true;
}
void MapSegment::eraseTarget(int i, int y, int x){
    targetInfomation.erase(targetInfomation.begin()+i);
    lineMap[y][x] = ' ';
}