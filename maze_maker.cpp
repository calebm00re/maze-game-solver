//
// Created by Caleb Moore on 3/27/21.
//

#include "maze_maker.h"
//construct the maze in a form the computer will be able to understand and navigate more simply
void maze_maker::construct(DSString maze_file) {
    std::ifstream input;

    //open the input file
    input.open(maze_file.c_str());
    if (!input.is_open()) {
        std::cout << "maze input failed to open" << std::endl;
    }

    //get first line into DSString
    char *temp = new char[10];
    input.getline(temp, 10, '\n');
    DSString dimensions(temp);
    delete[] temp;

    //get first and second number for file
    int temp_space;
    for (int i = 0; i < dimensions.getLength(); i++) {
        if (dimensions[i] == ' ') {
            temp_space = i;
        }
    }

    //put dimensions in their variables
    int row_dimension = dimensions.substring(0, temp_space).to_digit();
    int col_dimension = dimensions.substring(temp_space + 1, dimensions.getLength() - temp_space - 1).to_digit();

    int curr_room_num = 0;
    //get the remaining rows in the maze
    for (int i = 0; i < row_dimension; i++) {
        char *temp_row = new char[col_dimension + 1];
        input.getline(temp_row, col_dimension + 1, '\n');
        DSString entire_row(temp_row);
        delete[] temp_row;

        DSString curr_room;
        for (int j = 0; j < col_dimension; j++) {
            curr_room = entire_row.substring(j, 1);
            if (curr_room == "0") {
                room_vec.push_back(Room(i + 1, j + 1, curr_room_num++));
            }
        }
    }
    //determine the num of portals
    char *temp_portal_num = new char[5];
    input.getline(temp_portal_num, 5, '\n');
    DSString portals_temp(temp_portal_num);
    delete[] temp_portal_num;
    num_portals = portals_temp.to_digit();

    //get the portal info
    for (int i = 0; i < num_portals; i++) {
        //get the whole line
        char *temp_portal = new char[15];
        input.getline(temp_portal, 15, '\n');
        DSString portal_line(temp_portal);
        delete[] temp_portal;

        //do more portal understanding
        int duration = 0;
        int curr_spot = 0;
        int start = 0;

        //store the portal in a useful manner -- as rooms ******* the rest of this function is meticulously getting each element of the portals until the start and finish aspects
        while(portal_line[curr_spot] != ' '){
            curr_spot++;
            duration++;
        }

        int temp_portal_r = portal_line.substring(start, duration).to_digit();
        //std::cout << "temp_portal_r:" << temp_portal_r << std::endl;

        start = curr_spot + 1;
        duration = 0;
        curr_spot++;

        while(portal_line[curr_spot] != ' '){
            duration++;
            curr_spot++;
        }

        int temp_portal_c = portal_line.substring(start, duration).to_digit();
        //std::cout << "temp_portal_c:" << temp_portal_c << std::endl;
        portal_from.push_back(std::make_pair(temp_portal_r, temp_portal_c));

        start = curr_spot + 1;
        duration = 0;
        curr_spot++;

        while(portal_line[curr_spot] != ' '){
            curr_spot++;
            duration++;
        }

        temp_portal_r = portal_line.substring(start, duration).to_digit();
        //std::cout << "temp_portal_r:" << temp_portal_r << std::endl;

        start = curr_spot + 1;
        duration = 0;
        curr_spot++;

        while(portal_line[curr_spot] != ' '){
            duration++;
            curr_spot++;
        }

        temp_portal_c = portal_line.substring(start, duration).to_digit();
        //std::cout << "temp_portal_c:" << temp_portal_c << std::endl;
        portal_to.push_back(std::make_pair(temp_portal_r, temp_portal_c));

        start = curr_spot + 1;

        portal_cost.push_back(portal_line.substring(start, (portal_line.getLength() - start)).to_digit());
    }
    //DONE with portals HERE

    //get start and end pieces***
    int temp_r_start;
    int curr_spot = 0;
    char *start_char = new char[10];
    input.getline(start_char, 10, '\n');
    DSString start_line(start_char);
    delete[] start_char;
    for (int i = 2; i < start_line.getLength(); i++) {
        if (start_line[i] == ' ') {
            curr_spot = i;
            temp_r_start = start_line.substring(2, i - 1).to_digit();
            break;
        }
    }
    int temp_c_start = start_line.substring(curr_spot + 1, start_line.getLength() - curr_spot - 1).to_digit();


    //find the start/end room
    char *end_char = new char[10];
    input.getline(end_char, 10, '\n');
    DSString end_line(end_char);
    delete[] end_char;
    int temp_r_end = 0;
    for (int i = 2; i < end_line.getLength(); i++) {
        if (end_line[i] == ' ') {
            curr_spot = i;
            temp_r_end = end_line.substring(2, i - 1).to_digit();
            break;
        }
    }
    int temp_c_end = end_line.substring(curr_spot + 1, end_line.getLength() - curr_spot - 1).to_digit();

    //set the start and end rooms boolean values so they can be checked later in case they are start or end
    for (int i = 0; i < room_vec.get_size(); i++) {
        if (room_vec[i].is_same(temp_r_start, temp_c_start)) {
            room_vec[i].set_start();
            curr_room = room_vec[i];
        }
        if(room_vec[i].is_same(temp_r_end, temp_c_end)){
            room_vec[i].set_end();
        }
    }
    input.close(); //close the input file
}

//function used in debugging to view rooms and solutions and
void maze_maker::print_rooms() {
    //print out the rooms
    for (int i = 0; i < room_vec.get_size(); i++) {
        std::cout << room_vec[i] << std::endl;
    }

    //print out the adjlist of rooms
    std::cout << "------------------------------------------------------------" << std::endl;
    myList.print_list();

    //print portals
    std::cout << "------------------------------------------------------------" << std::endl;
    for (int i = 0; i < portal_from.get_size(); i++) {
        std::cout << portal_from[i].first << " and " << portal_from[i].second << std::endl;
    }
    std::cout << "------------------------------------------------------------" << std::endl;
    //print num of solutions
    std::cout << "total solutions found >" << solutions.get_size() << std::endl;

}

//build the adj list
void maze_maker::find_adj() {
    //go through every room in respect to every room to check if they are adjacent in the maze
    for(int i = 0; i < room_vec.get_size(); i++){
        //if room offset by one && not equal it is adjacent
        for(int j = 0; j < room_vec.get_size(); j++){
            if(room_vec[i].is_next_to(room_vec[j])) {
                //std::cout << "match at " << room_vec[i] << std::endl;
                myList.add_edge(room_vec[i].get_room_num(), room_vec[j]);
            }
        }
    }

    //do portals
    //check to find the rooms the portals are adjacent to
    for(int i = 0; i < portal_from.get_size(); i++){
        for(int j = 0; j < room_vec.get_size(); j++){
            if(room_vec[j].is_same(portal_from[i].first, portal_from[i].second)){
                for(int t = 0; t < room_vec.get_size(); t++){
                    if(room_vec[t].is_same(portal_to[i].first, portal_to[i].second)){
                        room_vec[t].set_cost(portal_cost[i]);
                        myList.add_edge(room_vec[j].get_room_num(), room_vec[t]);
                    }
                }
            }
        }
    }
}

//function to actully solve the maze
void maze_maker::solve_fast() {
    //create lots of useful variables
    std::set<int> visited;
    std::set<int>::iterator visitedIter;
    room_stack.push(curr_room);
    visited.insert(curr_room.get_room_num());
    DSVector<Room>* temp_vec;
    int max_cost_curr = 0;
    bool found_new = false;
    int curr_cost = 0;
    int tot_rooms = 0; //start in start room per DR. F so doesnt count in count

    //stay in the stack until it has been backtracked to the point of being empty
    while(!room_stack.is_empty()){
        found_new = false;
        curr_room = room_stack.top();
        temp_vec = &myList.get_adjacent(curr_room.get_room_num());

        //check to see if a path to the exit has been found
        if(curr_room.get_end()){
            solutions.push_back(room_stack);
            costs.push_back(curr_cost);
            total_rooms.push_back(tot_rooms);
        }

        //check to see if a new room is being discovered adjacently
        for(int i = temp_vec->getItIndex(); i < temp_vec->get_size(); i++, temp_vec->move_it_next()){
            if(visited.find(temp_vec->get_it().get_room_num()) == visited.end()){
                found_new = true;
                curr_room = temp_vec->get_it();
                room_stack.push(curr_room);
                curr_cost += curr_room.get_cost();
                tot_rooms++;
                visited.insert(curr_room.get_room_num());
                temp_vec->move_it_next();
                break;
            }
        }

        //if no new room was found go back a step in the backtracking
        if(!found_new){
            (myList.get_adjacent(curr_room.get_room_num())).reset_it();
            visited.erase(curr_room.get_room_num());
            tot_rooms--;
            curr_cost -= curr_room.get_cost();
            room_stack.pop();
        }
    }
}

//function to print out the final outputs and DR. F said to ignore handout and only give life points for max file
void maze_maker::evaluate_and_output(DSString min_name, DSString max_name) {
    std::ofstream output;

    //make variables so the min and max can be found amongst the solutions
    int min;
    DSStack<Room> room_order;

    //check to see if a solution was found
    if(costs.get_size() > 0) {
        min = 0;


        //find the mins and maxes of the costs
        for (int i = 1; i < costs.get_size(); i++) {
            if (costs[i] < costs[min]) {
                min = i;
            }
        }

        //following space for min file*** to output the necessary info
        output.open(min_name.c_str());

        if (!output.is_open()) {
            std::cout << "output min file failed to open" << std::endl;
        }
        else {
            output << costs[min] << std::endl;
            output << total_rooms[min] << std::endl;

            DSStack<Room> temp_stack = solutions[min];

            //reverse order so rooms are from start to end
            while (!temp_stack.is_empty()) {
                room_order.push(temp_stack.top());
                temp_stack.pop();
            }

            room_order.pop(); //get rid of the top room because we start in the first one and dont need to list it
            output << "Start" << std::endl;
            while (!room_order.is_empty()) {
                output << room_order.top() << std::endl;
                room_order.pop();
            }
        }
        output.close();
        //END MIN FILE SPACE***


        //following space for max file*** to output the necessary info
        //output worst choices so all reachable rooms would be exploring all rooms and using all portals to get into
        //rooms since it costs more than moving there from a room next to it
        output.open(max_name.c_str());

        if (!output.is_open()) {
            std::cout << "output max file failed to open" << std::endl;
        }
        else {
            long_life_cost += myList.get_size();
            long_life_cost -= portal_cost.get_size();
            for(int i = 0; i < portal_cost.get_size(); i++){
                long_life_cost += portal_cost[i];
            }
            output << long_life_cost << std::endl;
        }
        output.close();
        //END MAX FILE SPACE***
    }
    else{
        //do output for in case there is no solution?
        output.open(min_name.c_str());
        if (!output.is_open()) {
            std::cout << "output min file failed to open" << std::endl;
        }
        else{
            output << "no solution was found" << std::endl;
        }
        output.close();

        //do the same for max output if no solution
        output.open(max_name.c_str());
        if (!output.is_open()) {
            std::cout << "output max file failed to open" << std::endl;
        }
        else{
            output << "no solution was found" << std::endl;
        }
        output.close();
    }
}