//
// Created by max on 10.09.16.
//
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <time.h>
#ifndef SPANNINGTREE_MYTOOLS_H
#define SPANNINGTREE_MYTOOLS_H
#endif //SPANNINGTREE_MYTOOLS_H
//Define Console Colors
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[00m"


////////////////////////////////
// pre define Functions
////////////////////////////////
void writeDebug(char* string);
void* xmalloc(size_t size);
void* xrealloc(void *pointer, size_t size);
char* xitoa(int integer);
char* ptoa(void *pointer);
void xfree(void *pointer);
int stringlength(char *string);
int numcount(int integer);