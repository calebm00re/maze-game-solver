cmake_minimum_required(VERSION 3.15)
project(PA04_amazing)
set(CMAKE_CXX_STANDARD 14)

##########################################
# Students, edit the items below.  In the quotes,
# put the names of the input files as they should appear
# in the argv param to main.x
# Example:
#   set (input01 "train_data.csv")
#   set (input02 "train_target.csv")
# etc....
# if you need more, add them here and in the foreach stmt below.
set (input01 "maze.txt")
set (input02 "")
set (input03 "")

#
##########################################

# Copy data files to build dir
foreach(file IN LISTS input01 input02 input03)
    configure_file(${file} ${file} COPYONLY)
endforeach()


# Create the executable for sorting
add_executable(PA04_amazing main.cpp DSString.h DSString.cpp catch.cpp catch.hpp DSVector.h DSList.h DSStack.h AdjList.h Room.cpp Room.h maze_maker.cpp maze_maker.h AdjList.cpp)








