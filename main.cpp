#define CATCH_CONFIG_RUNNER
#include <iostream>
#include "catch.hpp"
#include "maze_maker.h"

int main(int argc, char** data) {
    //if no command line args run catch
    if (argc == 1){
        Catch::Session().run();
    }
    //if given right num of command line args run program for maze
    else if (argc == 4){
        maze_maker maze;
        maze.construct(data[1]);
        maze.find_adj();
        maze.solve_fast();
        maze.evaluate_and_output(data[2], data[3]);
        //maze.print_rooms();
    }
    //otherwise prompt for acceptable number of command line args
    else{
        std::cout << "give the correct command number of line arguments" << std::endl;
    }
    return 0;
}
