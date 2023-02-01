//
// Created by Caleb Moore on 3/27/21.
//

#ifndef PA04_AMAZING_MAZE_MAKER_H
#define PA04_AMAZING_MAZE_MAKER_H
#include "AdjList.h"
#include "Room.h"
#include "DSString.h"
#include "DSStack.h"
#include "DSVector.h"
#include <iostream>
#include <fstream>
#include <set>

class maze_maker{
private:
    //making private variables for the maze making/solving
    AdjList myList;
    int num_portals;
    Room curr_room;
    DSVector<Room> room_vec;
    DSStack<Room> room_stack;
    //make portal vectors to be associated by index
    DSVector<std::pair<int, int>> portal_from;
    DSVector<std::pair<int, int>> portal_to;
    DSVector<int> portal_cost;
    //make a vector of possible stacks
    DSVector<DSStack<Room>> solutions;
    DSVector<int> costs;
    DSVector<int> total_rooms;
    int long_life_cost = -1;

public:
    //useful/necessary functions in solving the maze
    void construct(DSString maze_file);
    void find_adj();
    void solve_fast();
    void print_rooms();
    void evaluate_and_output(DSString min_name, DSString max_name);
};

#endif //PA04_AMAZING_MAZE_MAKER_H
