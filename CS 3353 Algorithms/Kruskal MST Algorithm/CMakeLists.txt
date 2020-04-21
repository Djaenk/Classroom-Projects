cmake_minimum_required(VERSION 3.10)
project(20S-3353-PA02)
set (EXE_NAME Kruskal)
set(CMAKE_CXX_FLAGS "-Wall")

##########################################
# Students, edit the items below.  In the quotes,
# put the names of the input files as they should appear
# in the argv param to main.
# Example:
#   set (input01 "train_data.csv")
#   set (input02 "train_target.csv")
# etc....

set (input01 "graph0.txt")
set (input02 "graph1.txt")
set (input03 "graph2.txt")
set (input04 "graph3.txt")
set (input05 "graph4.txt")
set (input06 "graph5.txt")
set (input07 "graph6.txt")
set (input08 "graph7.txt")
set (input09 "graph8.txt")
set (input10 "graph9.txt")
set (input11 "graph10.txt")
set (input12 "graph11.txt")
set (input13 "graph12.txt")
set (input14 "graph13.txt")
set (input15 "graph14.txt")

#
##########################################

# Copy data files to build dir
foreach(file IN LISTS input01 input02 input03 input04 input05 input06 input07
                        input08 input09 input10 input11 input12 input13 input14
                        input15)
    configure_file(${file} ${file} COPYONLY)
endforeach()

set(CMAKE_CXX_STANDARD 14)
include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/utils)
add_executable(${EXE_NAME} main.cpp disjoint_set.hpp simple_graph.hpp weighted_graph.hpp timer.hpp)