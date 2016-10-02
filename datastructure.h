//
// Created by max on 10.09.16.
//

#ifndef SPANNINGTREE_DATASTRUCTURE_H
#define SPANNINGTREE_DATASTRUCTURE_H
#endif //SPANNINGTREE_DATASTRUCTURE_H
#ifndef SPANNINGTREE_MYTOOLS_H
#include "mytools.h"                    //Binde die eigene Toolbox ein, falls dies noch nicht geschehen ist.
#endif //SPANNINGTREE_MYTOOLS_H

//lege die Laufzeitvariablen fest.
#define MAX_ITEMS 99        //maximale Anzahl an Zeilen in der Definitionsdatei
#define MAX_KOSTEN 99       //maximale Kosten pro Knoten
#define MAX_NODE_ID 99      //maximaler Wert der Node ID
#define MAX_IDENT 99         //maximale Anzahl an Stellen für den Node Identifikator

//Parameter zum Auslesen der Topologie
#define KOMMENTARSTR "//"   //String mit dem eine Kommentar beginnt
#define ZEILENENDE ";"      //Zeichen am Ende der Zeile
#define ZUWEISER ":="       //mögliche Zeichen um Zuweisungen zu machen
#define LINKCHAR '-'        //Zeichen zwischen zwei Elementen

//Standardwerte für Nodes
#define STDLINK 0
#define STDNEXTHOP 0
#define STDMSGCNT 0
#define STDCOSTSTOROOT 0
#define STDNACHFOLGER 0
#define STDVORGAENGER 0
//Alles Andere wird durch gegebene Werte oder das Element selbst ersetzt.

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

////////////////////////////////
// Functions
////////////////////////////////
//Node Methods
////////////////////////////////
//Create
p_node createNode(char *new_name, int new_nodeID)
{
    node *new_node;
    new_node = xmalloc(sizeof(node));
    if(new_node == 0){
        writeDebug("Node kann nicht angelegt werden.");
        return 0;
    }
    strcpy(new_node->name, new_name);
    new_node->nodeID = new_nodeID;
    new_node->costsToRoot = STDCOSTSTOROOT;
    new_node->msgCnt = STDMSGCNT;
    new_node->nextHop = STDNEXTHOP;
    new_node->plink = STDLINK;
    new_node->root = new_node;
    new_node->nachfolger = STDNACHFOLGER;
    new_node->vorgaenger = STDVORGAENGER;
    return new_node;
}
//Ausgabe
void printNode(p_node this_node)
{
    if(this_node == 0){
        writeDebug("Node ist Nullpointer.");
        return;
    }
    fprintf(stdout,"Node:\t%s \n", this_node->name);
    fprintf(stdout,"ID:\t%d \n", this_node->nodeID);
    fprintf(stdout,"msgCnt:\t%d \n", this_node->msgCnt);
    if(this_node->root != 0)
    {
        fprintf(stdout,"Root:\t%s \n", this_node->root->name);
    }else{
        fprintf(stdout,"Root:\t(NULL) \n");
    }
    fprintf(stdout,"costsToRoot:\t%d \n", this_node->costsToRoot);
    if(this_node->nextHop != 0)
    {
        fprintf(stdout,"nextHop:\t%s \n", this_node->nextHop->name);
    }else{
        fprintf(stdout,"nextHop:\t(NULL) \n");
    }
    fprintf(stdout,"Vorgänger:\t%p \n", this_node->vorgaenger);
    fprintf(stdout,"Nachfolger:\t%p \n", this_node->nachfolger);


}
//Hinzufügen zur Liste
p_node addNodeToList(p_node node, p_node *nodelist)
{
    if((*nodelist) == 0)
    {
        writeDebug("Die Liste ist leer. Node wird beginn der Liste.");
        (*nodelist) = node;
    }else
    {
        //der Node ist der neue Beginn der Liste.
        (*nodelist)->vorgaenger = node;
        node->nachfolger = (*nodelist);
        (*nodelist) = node;
    }
    return *nodelist;
}
//Entfernen aus der Liste
p_node removeNodeFromList(p_node node, p_node *nodelist)
{
    p_node tmp = *nodelist;
    while(tmp != 0)
    {
        if(tmp == node)
        {
            if(tmp->vorgaenger != 0){
                tmp->vorgaenger->nachfolger = tmp->nachfolger;
            }else{
                (*nodelist) = tmp->nachfolger;
            }
            if(tmp->nachfolger != 0){
                tmp->nachfolger->vorgaenger = tmp->vorgaenger;
            }
            return tmp;
        }else
        {
            tmp = tmp->nachfolger;
        }
    }
    return tmp;
}
//Prüfen auf vorhandensein in Liste
int isInNodeList(p_node node, p_node *nodelist)
{
    p_node tmp = *nodelist;
    while(tmp != 0)
    {
       if(tmp == node)
       {
           return 1;
       }else
       {
           tmp = tmp->nachfolger;
       }
    }
    return 0;
}
p_node nodeExitsByName(char *name, p_node *nodelist)
{
    p_node tmp = *nodelist;
    while(tmp != 0)
    {
        if(strcmp(tmp->name, name) > 0 )
        {
            return tmp;
        }else
        {
            tmp = tmp->nachfolger;
        }
    }
    return 0;
}
p_node nodeExitsByID(int id, p_node *nodelist)
{
    p_node tmp = *nodelist;
    while(tmp != 0)
    {
        if(tmp->nodeID == id)
        {
            return tmp;
        }else
        {
            tmp = tmp->nachfolger;
        }
    }
    return 0;
}
//Löschen
void deleteNode(p_node *node)
{
    xfree(*node);
    *node = 0;
}
////////////////////////////////
//Link Methods
////////////////////////////////
//Erstellen
p_link createLink(int new_kosten, p_node *new_start, p_node *new_ziel)
{
    p_link kante;
    kante = xmalloc(sizeof(link));
    if(kante == 0){
        writeDebug("Link kann nicht angelegt werden.");
        return 0;
    }
    kante->kosten = new_kosten;
    kante->start = *new_start;
    kante->ziel = *new_ziel;
    kante->nachfolger = STDNACHFOLGER;
    kante->vorgaenger = STDVORGAENGER;
    return kante;
}
//Ausgeben
void printLink(p_link this_link)
{
    if(this_link == 0){
        writeDebug("Link ist Nullpointer.");
        return;
    }
    fprintf(stdout,"Start:\t%s \n", this_link->start->name);
    fprintf(stdout,"Ziel:\t%s \n", this_link->ziel->name);
    fprintf(stdout,"Kosten:\t%d \n", this_link->kosten);
    fprintf(stdout,"Vorgänger:\t%p \n", this_link->vorgaenger);
    fprintf(stdout,"Nachfolger:\t%p \n", this_link->nachfolger);
}
//Hinzufügen zur Liste
p_link addLinkToLinklist(p_link link, p_link *linklist)
{
    if((*linklist) == 0)
    {
        writeDebug("Die Liste ist leer. Link wird beginn der Liste.");
        (*linklist) = link;
    }else
    {
        //der link ist der neue Beginn der Liste.
        (*linklist)->vorgaenger = link;
        link->nachfolger = (*linklist);
        (*linklist) = link;
    }
    return *linklist;
}
//Enfernen von der Liste
p_link removeLinkFromList(p_link link, p_link *linklist)
{
    p_link tmp = *linklist;
    while(tmp != 0)
    {
        if(tmp == link)
        {
            if(tmp->vorgaenger != 0){
                tmp->vorgaenger->nachfolger = tmp->nachfolger;
            }else{
                (*linklist) = tmp->nachfolger;
            }
            if(tmp->nachfolger != 0){
                tmp->nachfolger->vorgaenger = tmp->vorgaenger;
            }
            return tmp;
        }else
        {
            tmp = tmp->nachfolger;
        }
    }
    return tmp;
}
//Prüfen auf Vorhandensein in der Liste
int isInLinkList(p_link link, p_link *linklist)
{
    p_link tmp = *linklist;
    while(tmp != 0)
    {
        if(tmp == link)
        {
            return 1;
        }else
        {
            tmp = tmp->nachfolger;
        }
    }
    return 0;
}
int linkExists(p_node start, p_node ziel, p_link *linklist)
{
    p_link tmp = *linklist;
    while(tmp != 0)
    {
        if(((tmp->start == start) && (tmp->ziel == ziel)|| (tmp->start == ziel) && (tmp->ziel == start)))
        {
            return 1;
        }else
        {
            tmp = tmp->nachfolger;
        }
    }
    return 0;
}
//Löschen
void deleteLink(p_link *link)
{
    xfree(*link);
    *link = 0;
}