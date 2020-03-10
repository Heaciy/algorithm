cmake_minimum_required(VERSION 3.15)
project(TakeBus)

set(CMAKE_CXX_STANDARD 11)

INCLUDE_DIRECTORIES(include)

AUX_SOURCE_DIRECTORY(source SRC)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fexec-charset=GBK")

ADD_EXECUTABLE(main ${SRC} include/model.h include/map.h include/menu.h source/map.cpp source/menu.cpp include/search.h source/search.cpp)