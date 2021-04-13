all: main
main: main.o game.o map_segment.o curses_controller.o print_controller.o curses_view.o print_view.o view.o building.o item.o
	g++ -Wall -Werror -g main.o game.o map_segment.o curses_controller.o print_controller.o curses_view.o print_view.o view.o building.o item.o -o main -lcurses

main.o: main.cpp
	g++ -Wall -Werror -c -std=c++11 main.cpp

game.o: game.cpp game.hpp 
	g++ -Wall -Werror -c -std=c++11 game.cpp 

map_segment.o: map_segment.cpp map_segment.hpp
	g++ -Wall -Werror -c -std=c++11 map_segment.cpp

curses_controller.o: curses_controller.cpp curses_controller.hpp
	g++ -Wall -Werror -c -std=c++11 curses_controller.cpp

print_controller.o: print_controller.cpp print_controller.hpp
	g++ -Wall -Werror -c -std=c++11 print_controller.cpp

curses_view.o: curses_view.cpp curses_view.hpp
	g++ -Wall -Werror -c -std=c++11 curses_view.cpp

print_view.o: print_view.cpp print_view.hpp
	g++ -Wall -Werror -c -std=c++11 print_view.cpp

view.o: view.cpp view.hpp
	g++ -Wall -Werror -c -std=c++11 view.cpp

building.o: building.cpp building.hpp
	g++ -Wall -Werror -c -std=c++11 building.cpp

item.o: item.cpp item.hpp
	g++ -Wall -Werror -c -std=c++11 item.cpp

# Marking a target as .PHONY causes make to treat it as always outdated.
.PHONY: clean
clean:
	rm -f *.o

