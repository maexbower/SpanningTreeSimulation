//
// Created by max on 10.09.16.
//
#include <errno.h>
#ifndef SPANNINGTREE_MYTOOLS_H
#define SPANNINGTREE_MYTOOLS_H
#endif //SPANNINGTREE_MYTOOLS_H

////////////////////////////////
// pre define Functions
////////////////////////////////
void writeDebug(char* string);
void* xmalloc(size_t size);
void* xrealloc(void *pointer, size_t size);
char* itoa (int integer);
char* ptoa(void *pointer);
////////////////////////////////
// Functions
////////////////////////////////
void writeDebug(char* string)
{
    fprintf(stdout, "DEBUG: %s\n",string);
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
char* itoa (int integer)
{
    char *string;
    string = xmalloc(sizeof(integer) * sizeof(char) / sizeof(int));
    sprintf(string, "%d", integer);
    return string;
}
char* ptoa(void *pointer)
{
    return itoa((int)pointer);
}