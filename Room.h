//
// Created by Caleb Moore on 3/27/21.
//

#ifndef PA04_AMAZING_ROOM_H
#define PA04_AMAZING_ROOM_H
#include <iostream>
#include <cmath>
#include "DSVector.h"

class Room{
private:
    //private variables to manipulate useful things for each room
    int life_cost{1};
    int x{0};
    int y{0};
    int num;
    bool is_end{false};
    bool is_start{false};

public:
    //make public functions to be used in the manipulation of the room objects
    Room();
    Room(int x, int y, int num);
    Room(const Room&);
    Room& operator= (const Room&);
    bool operator== (const Room&) const;
    bool is_same(const int&, const int&) const;
    friend std::ostream& operator<< (std::ostream& output, const Room& r);
    bool is_next_to(const Room&);
    bool get_start();
    bool get_end();
    void set_start();
    void set_end();
    void set_cost(const int&);
    int& get_room_num();
    int& get_cost();
    ~Room();
};

#endif //PA04_AMAZING_ROOM_H
