//
// Created by max on 02.10.16.
//

#ifndef SPANNINGTREE_SPANNINGTREE_H
#define SPANNINGTREE_SPANNINGTREE_H
#endif //SPANNINGTREE_SPANNINGTREE_H

#ifndef SPANNINGTREE_DATASTRUCTURE_H
#include "datastructure.h"
#endif //SPANNINGTREE_DATASTRUCTURE_H
//Hinzufügen von neuen Informationen
p_node nodeAdd(p_node node, p_node *nodelist);
p_node linkAdd(p_link link, p_node *nodelist);
//Aktualisieren der Vorhandenen Informationen
p_node updateAllLinklists(p_node node, p_node *nodelist);
