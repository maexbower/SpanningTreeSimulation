//
// Created by max on 10.09.16.
//

#ifndef SPANNINGTREE_FILEOPTIONS_H
#define SPANNINGTREE_FILEOPTIONS_H
#endif //SPANNINGTREE_FILEOPTIONS_H
#ifndef SPANNINGTREE_MYTOOLS_H
#include "mytools.h"
#endif //SPANNINGTREE_FILEOPTIONS_H

////////////////////////////////
// pre define Functions
////////////////////////////////
int fileReadable(char *filename);
FILE* openFile(char *filename);
int closeFile(FILE *p_file);
///Functions
////////////////////////////////
int fileReadable(char *filename)
{   //Gets the Filename and return 0 when the file is readable and 1 when the file is not readable
    writeDebug("fileReadable Aufgerufen mit:");
    writeDebug(filename);
    FILE *p_file;
    p_file = openFile(filename);
    if(p_file != 0){
        return closeFile(p_file);
    }
    return 1;
}
FILE* openFile(char *filename)
{
    FILE *p_file;
    p_file = fopen(filename, "r");
    if(p_file != 0){
        writeDebug("Datei wurde erfolgreich geöffnet. Pointer ist:");
        writeDebug(itoa((int)p_file));
        return p_file;
    }
    writeDebug("Datei konnte nicht geöffnet werden. Der Fehlercode ist:");
    writeDebug(strerror(errno));
    return 0;
}
int closeFile(FILE *p_file)
{
    int result;
    result = fclose(p_file);
    if(result != 0) {
        writeDebug("Datei konnte nicht geschlossen werden. Der Fehlercode ist:");
        writeDebug(strerror(errno));
        return 1;
    }
    writeDebug("Datei wurde geschlossen. Der Returncode ist:");
    writeDebug(itoa(result));
    return 0;
}

