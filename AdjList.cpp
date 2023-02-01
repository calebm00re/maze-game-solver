//
// Created by Caleb Moore on 3/28/21.
//

#include "AdjList.h"

//adds an edge to the adj list
void AdjList::add_edge(int room_num, const Room& curr_room) {
    my_map[room_num].push_back(curr_room);
}

//prints out the entirety of the adj list
void AdjList::print_list() {
    for(auto& p : my_map){
        std::cout << "room " << p.first << " is next to:";
        for(int i = 0; i < p.second.get_size(); i++){
            std::cout << " " << p.second[i];
        }
        std::cout << std::endl;
    }
}

//returns a reference to the vector of nearby rooms
DSVector<Room> &AdjList::get_adjacent(int num) {
    return my_map[num];
}

int AdjList::get_size() {
    return my_map.size();
}

