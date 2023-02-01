//
// Created by Caleb Moore on 3/27/21.
//

#ifndef PA04_AMAZING_ADJLIST_H
#define PA04_AMAZING_ADJLIST_H
#include <map>
#include "Room.h"
#include "DSVector.h"

class AdjList {
private:
    //map of room numbers as key with DSVector of adjacent rooms
    std::map<int, DSVector<Room>> my_map;
public:
    //functions to be used in manipulation of the adj list
    void add_edge(int, const Room&);
    void print_list();
    DSVector<Room>& get_adjacent(int);
    int get_size();
};

#endif //PA04_AMAZING_ADJLIST_H
