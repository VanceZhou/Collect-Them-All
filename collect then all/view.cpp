#include "view.hpp"
#include <iostream>
//this function set up the contents inside the view - string vector.
View::View(int height, int width)
    : mHeight(height), mWidth(width)
{
    std::string Viewline;
    // std::vector<std::string> wholeView;

    for (int i = 0; i < mHeight + 2; i++)
    {
        for (int j = 0; j < mWidth + 2; j++)
        {
            if (i == 0 || i == (mHeight + 1))
            {
                Viewline.push_back('*');
            }
            else
            {
                Viewline.push_back('~');
            }
        }

        Viewline[0] = '*';
        Viewline[mWidth + 1] = '*';

        wholeView.push_back(Viewline);
        Viewline.clear();
    }
}
void View::draw(const std::vector<std::string>& lines){
        

}
