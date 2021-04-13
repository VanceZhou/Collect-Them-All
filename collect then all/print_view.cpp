#include "print_view.hpp"

#include <iostream>

/**
 * The constructor and destructor shouldn't need anything added.
 */

PrintView::PrintView(int height, int width)
    : View(height, width)
{

}

PrintView::~PrintView()
{
}

void PrintView::draw(const std::vector<std::string> &lines)
{
    // TODO: Implement.
    for (auto i : lines)
    {
        std::cout << i << std::endl;
    }
}
