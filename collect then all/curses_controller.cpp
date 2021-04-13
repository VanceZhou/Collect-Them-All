#include "curses_controller.hpp"
#include <iostream> 

#include <curses.h>

CursesController::~CursesController()
{
}

Command CursesController::getInput()
{
    // TODO: Implement.
    // Don't forget about the arrow keys.
    
    
    char command = getch();
    clear();
    switch (command)
    {
    case 'w':
        return Command::Forward;
        break;
    case 'a':
        return Command::Left;
    case 'd':
        return Command::Right;
    case 'q':
        return Command::Quit;
    default:
        return Command::Invalid;
        // To prevent a compiler error in the starter files...
    }
    // endwin();
}
