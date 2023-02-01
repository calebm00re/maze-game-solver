//
// Created by Caleb Moore on 3/27/21.
//

#include "Room.h"

//default constructor
Room::Room() = default;

//constructor to set some useful aspects of a room up
Room::Room(int x, int y, int num) {
    this->x = x;
    this->y = y;
    this->num = num;
}

//copy constructor
Room::Room(const Room & rhs) {
    x = rhs.x;
    y = rhs.y;
    num = rhs.num;
    is_end = rhs.is_end;
    life_cost = rhs.life_cost;
}

//assignment operator overloading
Room &Room::operator=(const Room & rhs) {
    x = rhs.x;
    y = rhs.y;
    num = rhs.num;
    is_end = rhs.is_end;
    life_cost = rhs.life_cost;
    return *this;
}

//default destructor? no memory dynamically allocated here?
Room::~Room() = default;

//check to see if a room is equal by overloading and comparing x/y coordinates
bool Room::operator==(const Room & rhs) const {
    if(x == rhs.x && y == rhs.y && life_cost == rhs.life_cost){
        return true;
    }
    return false;
}

//overloading the output operator for ease of outputting and displaying rooms
std::ostream &operator<<(std::ostream & output, const Room & r) {
    output << r.x << ", " << r.y << "   " << r.life_cost;
    return output;
}

//check to see if a room is next to another one in the map *does not work for portals*
bool Room::is_next_to(const Room & rhs) {
    if ((std::abs(rhs.x - x) == 1 && rhs.y - y == 0) || (std::abs(rhs.y - y) == 1 && rhs.x - x == 0)){
        return true;
    }
    return false;
}

//returns the room number
int &Room::get_room_num() {
    return num;
}

//checks to see if a room is the same * this is how to check for a portal location
bool Room::is_same(const int & nx, const int & ny) const {
    if(x == nx && y == ny){
        return true;
    }
    return false;
}

//set the start value of a room
void Room::set_start() {
    is_start = true;
}

//set the end value of a room
void Room::set_end() {
    is_end = true;
}

//return true if room is start
bool Room::get_start() {
    return is_start;
}

//return true if room is end
bool Room::get_end() {
    return is_end;
}

//set a room cost... this is use if a portal is used with a non standard (1) cost
void Room::set_cost(const int& t) {
    life_cost = t;
}

//returns the cost to get into this room
int &Room::get_cost() {
    return life_cost;
}
