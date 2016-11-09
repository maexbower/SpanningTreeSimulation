//
// Created by max on 19.10.16.
//
#ifndef SPANNINGTREE_MAIN_H
#include "main.h"
#endif //SPANNINGTREE_MAIN_H
#ifndef SPANNINGTREE_MYTOOLS_H
#include "mytools.h"
#endif //SPANNINGTREE_MYTOOLS_H

////////////////////////////////
// Functions
////////////////////////////////
void writeDebug(char* string)
{
    if(debugmode == 1)
    {
        fprintf(stdout, "DEBUG: %s\n",string);
        fflush(stdout);
    }
}
void* xmalloc(size_t size)
{
    void *pointer;
    pointer = malloc(size);
    if (pointer == 0){
        writeDebug("Fehler beim Allocieren von Speicherplatz.");
    }
    return pointer;
}
void* xrealloc(void *pointer, size_t size)
{
    void *newpointer;
    newpointer = realloc(pointer, size);
    if (pointer == 0){
        writeDebug("Fehler beim Erweitern von Speicherplatz.");
    }
    return newpointer;
}
void xfree(void *pointer)
{
    free(pointer);
    if(errno)
    {
        writeDebug("Fehler beim freigeben des Speichers. Der Fehlercode ist:");
        writeDebug(strerror(errno));
    }
}
char* xitoa(int integer)
{
    char *string;
    string = xmalloc(sizeof(integer) * sizeof(char) / sizeof(int));
    sprintf(string, "%d", integer);
    return string;
}
char* ptoa(void *pointer)
{
    char *string;
    string = xmalloc(sizeof(long)*sizeof(char));
    sprintf(string, "%p", pointer);
    return string;
}
int stringlength(char *string)
{
    int count = 0;
    char tmpChar;
    tmpChar = string[0];
    while(tmpChar != 0)
    {
        count++;
        tmpChar = string[count];
    }
    return count;

}
int numcount(int integer)
{
    if(integer == 0) {
        return 1;
    }
    if(integer < 0)
    {
        integer=integer*-1;
    }
    int count = (int)floor(log10(integer)) + 1;
    return count;
}
