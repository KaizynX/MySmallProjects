project(astar)
set(SOURCES main.cpp process.cpp)
# set(CMAKE_MAKE_PROGRAM  "C:/MinGW/bin/mingw32-make.exe")
# set(CMAKE_C_COMPILER  "C:/MinGW/bin/gcc.exe")
# set(CMAKE_CXX_COMPILER  "C:/MinGW/bin/g++.exe")
set(CMAKE_CXX_FLAGS "-std=c++11 -lpthread -pthread")

add_executable(astar ${SOURCES})
