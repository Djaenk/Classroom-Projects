cmake_minimum_required(VERSION 3.10)
project(20S-3353-PA01)
set (EXE_NAME MemoryManager)
set(CMAKE_CXX_FLAGS "-Wall")

##########################################
# Students, edit the items below.  In the quotes,
# put the names of the input files as they should appear
# in the argv param to main.
# Example:
#   set (input01 "train_data.csv")
#   set (input02 "train_target.csv")
# etc....

set (input01 "train_data.csv")
set (input05 "train_target.csv")
set (input09 "test_data.csv")
set (input10 "test_target.csv")

#
##########################################

# Copy data files to build dir
foreach(file IN LISTS input01 input02 input03 input04 input01 input02 input03 input04 input05 input06 input07 input08 input09 input10 input11 input12)
    configure_file(${file} ${file} COPYONLY)
endforeach()

set(CMAKE_CXX_STANDARD 14)
add_executable(${EXE_NAME} main.cpp manager.h)
