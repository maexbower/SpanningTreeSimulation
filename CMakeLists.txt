cmake_minimum_required(VERSION 3.6)
project(SpanningTree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c11")
set(SOURCE_FILES main.c datastructure.h fileoptions.h mytools.h)
configure_file(topologie.txt topologie.txt COPYONLY)
add_executable(spt ${SOURCE_FILES})