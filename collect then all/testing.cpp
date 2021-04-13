#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
enum Direction {up, down, left,right};
    
int main(){
vector<int> a{1,2,3};
vector<int> b{4,5,6};
a=b;
for(auto i :a){
    cout<<i<<endl;
}
    return 0;
}
g++ -Wall -Werror -g -std=c++11 main.cpp item.cpp map_segment.cpp curses_controller.cpp print_controller.cpp curses_view.cpp print_view.cpp game.cpp view.cpp building.cpp -o main -lcurses