#include "print_controller.hpp"

#include <iostream>
using namespace std;
PrintController::~PrintController()
{
}

Command PrintController::getInput()
{
    // TODO: Implement.
    char command;
    
    cout<<"Enter input: ";
    cin>>command;
    switch(command){
        case 'w': 
        return Command::Forward;
        break;
        case 'a': return Command::Left;
        case 'd': return Command::Right;
        case 'q': return Command::Quit;
        default: return Command::Invalid;
    }
    
    


    // To prevent a compiler error in the starter files...
    // return Command::Invalid;
}
