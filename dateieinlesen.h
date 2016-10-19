//
// Created by max on 19.10.16.
//

#ifndef SPANNINGTREE_DATEIEINLESEN_H
#define SPANNINGTREE_DATEIEINLESEN_H
#endif //SPANNINGTREE_DATEIEINLESEN_H
#ifndef SPANNINGTREE_DATASTRUCTURE_H
#include "datastructure.h"
#endif //SPANNINGTREE_DATASTRUCTURE_H

////////////////////////////////
// pre define Functions
////////////////////////////////
int fileReadable(char *filename);
FILE* openFile(char *filename);
int closeFile(FILE *p_file);
int dateieinlesen(char* filepath, p_node *nodelist);
p_node addNewNode(p_node node, p_node *nodelist);
p_node addNewLink(p_node start, p_node ziel, int kosten, p_node *nodelist);