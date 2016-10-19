//
// Created by max on 19.10.16.
//

#ifndef SPANNINGTREE_DATASTRUCTURE_H
#define SPANNINGTREE_DATASTRUCTURE_H
#endif //SPANNINGTREE_DATASTRUCTURE_H
#ifndef SPANNINGTREE_MAIN_H
#include "main.h"
#endif //SPANNINGTREE_MAIN_H
#ifndef SPANNINGTREE_MYTOOLS_H
#include "mytools.h"
#endif //SPANNINGTREE_MYTOOLS_H

////////////////////////////////
// define Structures
////////////////////////////////
typedef struct link{
    int kosten;         //Kosten der Kante
    struct node *start; //Node am einen Ende
    struct node *ziel;  //Node am anderen Ende
    struct link *vorgaenger;
    struct link *nachfolger;
}link, *p_link;
typedef struct node{
    char name[MAX_IDENT+1]; //Knotenbezeichner
    int nodeID;             //Knoten ID
    struct link *plink;     //Liste aller Kanten zu den anderen Knoten
    struct node *nextHop;   //Link zum nächsten Knoten richtung Root
    int msgCnt;             //Anahl der Anfragen an diesen Knoten
    struct node *root;      //Root Bridge des Elements
    int costsToRoot;        //Kosten bis zur Root Bridge
    struct node *vorgaenger;
    struct node *nachfolger;
}node, *p_node;
////////////////////////////////
// pre define Functions
////////////////////////////////
//Create
p_link createLink(int new_kosten, p_node *new_start, p_node *new_ziel);
p_node createNode(char *new_name, int new_nodeID);
//Print
void printNode(p_node this_node);
void printLink(p_link this_link);
//AddToList
p_node addNodeToList(p_node node, p_node *nodelist);
p_link addLinkToLinklist(p_link link, p_link *linklist);
//RemoveFromList
p_node removeNodeFromList(p_node node, p_node *nodelist);
p_link removeLinkFromList(p_link link, p_link *linklist);
//Search in List
int isInNodeList(p_node node, p_node *nodelist);
int isInLinkList(p_link link, p_link *linklist);
p_node nodeExitsByName(char *name, p_node *nodelist);
p_node nodeExitsByID(int id, p_node *nodelist);
int linkExists(p_node start, p_node ziel, p_link *linklist);
//Delete
void deleteNode(p_node *node);
void deleteLink(p_link *link);
