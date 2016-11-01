# SpanningTreeSimulation

C Project for Simulating the spanning tree protocoll between nodes.

## Project Structure

### Main File

main.c

    main.c conatils the main function and makes use of alle the other wonderfull functions. 
    It also contains an testfunction that has to be activated by removing a comment.
    
main.h

    main.h conatins all global definitions like maximum values for the input data.
    
### Mytools

mytools.c

    mytools.c conatins a variety of general functions (malloc, debug writing) with build in error handling.

mytools.h

    mytools.h includes all nesacary standard libraries and contains the definitions of the color codes for printf.

### File IO Tools

dateieinlesen.c

    dateieinlesen.c contains all functions that are nessacary to read the topology file. 
    Also the general filehandling functions like open and close are implemented here.
    
dateieinlesen.h
    
    dateieinlesen.h only contains the function definitions. 

### Project Datastructure operations

datastructure.c

    datastructure.c contains all important functions for working with the datastructure for this project. 
    This includes the operations for the double connected linear list (insert, extract, find, ...).
    Also the functions that do the simulation are placed here.

datastructure.h 
    
    datastructure.h contain all the struct definitions for the datastructure.

### Other Files

topologie.txt

    topologie.txt contain the definition of the nodes and links.

CMakeLists.txt

    CMakeLists.txt contains all cmake options to build this project.

## Build

This project is developed with CLion from JetBrains, so it uses cmake to compile.
To build manual its recommend to follow these steps:

    cd ProjectDir  //change into project dir
    mkdir build    //create build directory
    cd build       //change into the build dir
    cmake ../      //run cmake on the project files
    make           //run make on the makefile created by the cmake command above

## Run

To run this Programm you need to take care of the syntax:

    spt <ToPo File> [Name des Graphen]
    Example: ./spt ./topologie.txt myGraph