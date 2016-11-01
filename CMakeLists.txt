cmake_minimum_required(VERSION 3.6)
project(SpanningTree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c11")
set(SOURCE_FILES main.c mytools.c datastructure.c dateieinlesen.c)
configure_file(topologie.txt topologie.txt COPYONLY)
add_executable(spt ${SOURCE_FILES})
target_link_libraries(spt m)
