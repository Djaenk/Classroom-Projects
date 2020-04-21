# Custom Memory Manager

*CS 3353 - Spring 2020 - Project 01*

Project Write Up is --> [here](https://github.com/smu-cs-3353/project_docs/blob/master/proj01.md) <-- 

Some notes/reminders:

- Update the CMakeLists.txt file and build.yaml files with program parameters
- Add cmd line args in CLion or your dev enviro of choice.
- In addition to any file input and output, you can use cmd line flags if you would like.

## Usage

The memory manager itself is contained in the manager.h header file. To use this memory manager, simply `#include "manager.h"` in your c++ project and build accordingly.

To set an allocation algorithm, call the `AllocatorSingleton::setFit(char)` function and pass `'f'` for first fit, `'b'` for best fit, or `'c'` for worst fit. If a fit is not selected in this manner, the program will upon attempting a dynamic allocation.

## Building This Project

### Linux Requirements

- g++ 7.4 or later
- CMake 3.10 or later

Clone this repository to a directory and navigate to that directory via the command line interface of your choice. To build, run:
```
# cmake build
# cmake --build build
```
The executable now resides in the build directory, and can be run with `build/MemoryManager`