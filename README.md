# SpanningTreeSimulation

C Project for Simulating the spanning tree protocol between nodes.
(Dieses Projekt ist für den Kurs "Grundlagen Rechnernetze" der DHBW Stuttgart. Die Aufgabe kann von berechtigten Personen unter [DHBW Link Shibboleth](http://wwwlehre.dhbw-stuttgart.de/~sto/ba-intern/kt/kt1/lab/SpanTree.pdf))

|   Table of Content    |
|-----------------------|
|[Project Structure](#projStruc)|
|&nbsp;&nbsp;&nbsp;[Main File](#mainFile)|
|&nbsp;&nbsp;&nbsp;[My tools](#myTools)|
|&nbsp;&nbsp;&nbsp;[File IO Tools](#fileIO)|
|&nbsp;&nbsp;&nbsp;[Project Datastructure operations](#datastructure)|
|&nbsp;&nbsp;&nbsp;[Other Files](#otherFiles)|
|[Build](#build)|
|[Run](#run)|

## <a name="projStruc"></a> Project Structure

### <a name="mainFile"></a> Main File

main.c

>   main.c contains the main function and makes use of all the other wonderful functions. 
>   It checks the parameters and defines the count of iterations and if Debug Mode is active.
>   The real magic happens when it pics a random node and puts it in the function that analyses its position in the structure.
>   This is what in Reality every node would do. Due to the fact that a node is only as intelligent as it neighbours you can
>   see, that with a small amount of iterations the nodes may have the wrong root id.
    
main.h

>   main.h contains all global definitions like maximum values for the input data and symbol definitions.
    
### <a name="myTools"></a> My tools

mytools.c

>   mytools.c conatins a variety of general functions (malloc, debug writing) with build in error handling.

mytools.h

>   mytools.h includes all nesacary standard libraries and contains the definitions of the color codes for printf.

### <a name="fileIO"></a> File IO Tools

dateieinlesen.c
>   dateieinlesen.c contains all functions that are nessacary to read the topology file. 
>   It also checks for integrity problems with the node definitions like wrong naming.
>   Also the general filehandling functions like open and close are implemented here.
    
dateieinlesen.h
    
>   dateieinlesen.h only contains the function definitions. 

### <a name="datastructure"></a> Project Datastructure operations

datastructure.c

>   datastructure.c contains all important functions for working with the datastructure for this project. 
>   This includes the operations for the double connected linear list (insert, extract, find, ...).
>   Also the functions that do the simulation are placed here.

datastructure.h 
    
>   datastructure.h contain all the struct definitions for the datastructure.

### <a name="otherFiles"></a> Other Files

topologie.txt

>   topologie.txt contain the definition of the nodes and links.

CMakeLists.txt

>   CMakeLists.txt contains all cmake options to build this project.

## <a name="build"></a> Build

This project is developed with CLion from JetBrains, so it uses cmake to compile.
Because of the used IDE the following tools are needed to build the program:

  * cmake
  * make
  * gcc

To build manual its recommend to follow these steps:

```Shell
cd /path/to/ProjectDir  #change into project dir
mkdir build             #create build directory
cd build                #change into the build dir
cmake ../               #run cmake on the project files
make                    #run make on the makefile created by the cmake command above
```
## <a name="run"></a> Run

To run this program you need to take care of the syntax:
```Shell
#spt <ToPo File> [Count of Iterations] [DEBUG]
#Example: 
./spt ./topologie.txt 100 DEBUG
#NOTE: the program checks for the string DEBUG, if you write DBUG=0 it will activate DEBUG too.
```
