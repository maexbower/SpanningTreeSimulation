//
// Created by max on 10.09.16.
//
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
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
void xfree(void *pointer);