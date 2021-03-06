//
// Created by max on 10.09.16.
//

#ifndef SPANNINGTREE_DATASTRUCTURE_H
#include "datastructure.h"
#endif //SPANNINGTREE_DATASTRUCTURE_H

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
        if(strcmp(tmp->name, name) == 0 )
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
    kante->visited = STDVISITED;
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
p_link linkExists(p_node start, p_node ziel, p_link *linklist)
{
    p_link tmp = *linklist;
    while(tmp != 0)
    {
        if(((tmp->start == start) && (tmp->ziel == ziel)|| (tmp->start == ziel) && (tmp->ziel == start)))
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
void deleteLink(p_link *link)
{
    xfree(*link);
    *link = 0;
}
void printStructure(p_node *nodelist)
{
    p_node tmpNode;
    p_link tmpLink;
    tmpNode = *nodelist;
    int nodecount = countNodes(nodelist);
    int maxNameLength = 0;
    int maxIDLength = 0;
    int currentNamelength = 0;
    int currentIDlength = 0;
    //Lese Grundliegende Eigenschaften der Struktur
    while(tmpNode != 0)
    {
        currentIDlength = numcount(tmpNode->nodeID);
        if(currentIDlength > maxIDLength)
        {
            maxIDLength = currentIDlength;
        }
        currentNamelength = stringlength(&tmpNode->name[0]);
        if(currentNamelength > maxNameLength){
            maxNameLength = currentNamelength;
        }
        tmpNode = tmpNode->nachfolger;
    }
    if(maxNameLength < MINCHARSFORNAME)
    {
        maxNameLength = MINCHARSFORNAME; //nur zu Darstellungszwecken
    }
    //Die Breite der Spalten sollte nun so breit sein wie die längste Beschreibung
    //Außerdem steht die Anzahl der Spalten nun fest.
    for(int i = 0; i < maxNameLength+2+maxIDLength; i++)
    {
        fprintf(stdout, "-");
    }
    fprintf(stdout,"|");
    fprintf(stdout,"|");
    for(int j = 0; j < nodecount; j++)
    {
        for(int i = 0; i < maxNameLength+2+maxIDLength; i++)
        {
            fprintf(stdout, "-");
        }
        fprintf(stdout,"|");
    }
    fprintf(stdout,"\n");
    for(int i = 0; i < maxNameLength+2+maxIDLength; i++)
    {
        fprintf(stdout, " ");
    }
    fprintf(stdout,"|");
    fprintf(stdout,"|");
    tmpNode = *nodelist;
    while(tmpNode != 0)
    {
        fprintf(stdout, "%*s(%*d)", maxNameLength ,tmpNode->name, maxIDLength, tmpNode->nodeID);
        tmpNode = tmpNode->nachfolger;
        fprintf(stdout,"|");
    }
    fprintf(stdout,"\n");
    for(int i = 0; i < maxNameLength+2+maxIDLength; i++)
    {
        fprintf(stdout, "-");
    }
    fprintf(stdout,"|");
    fprintf(stdout,"|");
    for(int j = 0; j < nodecount; j++)
    {
        for(int i = 0; i < maxNameLength+2+maxIDLength; i++)
        {
            fprintf(stdout, "-");
        }
        fprintf(stdout,"|");
    }
    fprintf(stdout,"\n");
    //Gehe für jede Zeile durch
    tmpNode = *nodelist;
    p_node tmpNodeSpalte;
    char* color = RESET;
    char tmpString[255];
    while(tmpNode != 0)
    {
        fprintf(stdout, "%*s(%*d)", maxNameLength ,tmpNode->name,maxIDLength , tmpNode->nodeID);
        fprintf(stdout,"|");
        fprintf(stdout,"|");
        //Nun jede Spalte durchgehen
        tmpNodeSpalte = *nodelist;
        while(tmpNodeSpalte != 0)
        {
            tmpLink = linkExists(tmpNode, tmpNodeSpalte, &tmpNode->plink);
            if(tmpLink != 0){
                if(tmpLink->visited == 0)
                {
                    color = BLU; //nicht besuchte Links werden blau dargestellt
                }else{
                    color = GRN; //wurde ein Link mindestens ein mal verarbeitet, so wird er gruen dargestellt.
                }
                sprintf(tmpString, "%d",tmpLink->kosten);
                if(tmpNode->root == tmpNodeSpalte)
                {
                    sprintf(tmpString, "%s (r k:%d)", tmpString, tmpNode->costsToRoot);
                }
                fprintf(stdout,"%s %*s %s", color,  maxNameLength+0+maxIDLength, tmpString, RESET);
                color = RESET;
            }else
            {
                color = RED;
                fprintf(stdout, "%s %*c %s", color, maxNameLength+0+maxIDLength, '-', RESET);
                color = RESET;
            }
            tmpNodeSpalte = tmpNodeSpalte->nachfolger;
            fprintf(stdout,"|");
        }

        tmpNode = tmpNode->nachfolger;
        fprintf(stdout,"\n");
        fflush(stdout);
    }
    fprintf(stdout, "Anzahl Nodes: %d und maxNameLength: %d\n", nodecount, maxNameLength);
    tmpNode = *nodelist;
    //print Routes
    fprintf(stdout, "Routen zum root Node:\n");
    while(tmpNode != 0)
    {
        fprintf(stdout, "%s ", tmpNode->name);
        tmpLink = linkExists(tmpNode, tmpNode->nextHop, &tmpNode->plink);
        while(tmpLink != 0)
        {
            fprintf(stdout, "-> %s(%d) ", tmpLink->ziel->name, tmpLink->kosten);
            tmpLink = linkExists(tmpLink->ziel, tmpLink->ziel->nextHop, &tmpLink->ziel->plink);
        }
        fprintf(stdout, "=> %s(%d)\n", tmpNode->root->name, tmpNode->costsToRoot);
        tmpNode = tmpNode->nachfolger;
    }
}
int countNodes(p_node *nodelist)
{
    int count = 0;
    p_node tmpNode;
    tmpNode = *nodelist;
    while(tmpNode != 0)
    {
        count++;
        tmpNode = tmpNode->nachfolger;
    }
    return count;
}
int checkDatenKonsitenz(p_node *nodelist)
{
    //prüfe auf nicht definierte Nodes
    p_node tmpNode;
    p_link tmpLink;
    int linkcheck;
    tmpNode = *nodelist;
    while(tmpNode != 0)
    {
        if(tmpNode->nodeID == STDNODEID)
        {
            writeDebug("Konsitenzprüfung fehlgeschlagen. Ein Node wurde nicht definiert.");
            return 1;
        }
        tmpNode = tmpNode->nachfolger;
    }
    //prüfe auf nicht verbundene Nodes
    tmpNode = *nodelist;
    while(tmpNode != 0)
    {
        writeDebug("Node:");
        writeDebug(tmpNode->name);
        linkcheck = 0;
        tmpLink = tmpNode->plink;
        while(tmpLink != 0)
        {
            if(tmpLink->kosten != STDCOST)
            {
                linkcheck = 1;
            }
            tmpLink = tmpLink->nachfolger;
        }
        if(linkcheck == 0)
        {
            writeDebug("Konsitenzprüfung fehlgeschlagen. Ein Node ist nicht angeschlossen.");
            return 2;
        }
        tmpNode = tmpNode->nachfolger;
    }
    return 0;
}
p_node getRandomNode(p_node *nodelist) {
    p_node node;
    node = *nodelist;
    int randomNumber = rand()% countNodes(nodelist);
    writeDebug("Zufallszahl ist:");
    writeDebug(xitoa(randomNumber));
    //fprintf(stdout, "Zufallszahl: %d \n",randomNumber);
    for(int i = 0; i < randomNumber; i++)
    {
        node = node->nachfolger;
    }
    return node;
}
p_node findroot(p_node start)
{
    char tmpString[255];
    sprintf(tmpString, "Untersuche Node: %s", start->name);
    writeDebug(tmpString);
    //fprintf(stdout, "%s\n", tmpString);
    nearestRoot(start);
    return start;
}
p_node nearestRoot(p_node start)
{
    p_link tmpLink;
    p_node tmpNode;
    tmpLink = start->plink;
    tmpNode = start;
    int kosten = tmpNode->costsToRoot;
    while(tmpLink != 0)
    {
        if(tmpLink->kosten == STDCOST)
        {
            tmpLink = tmpLink->nachfolger;
            continue; //Dann existiert der Link nicht
        }
        writeDebug("------------------------------");
        writeDebug("aktueller start:");
        writeDebug(start->name);
        writeDebug("aktueller tmpNode:");
        writeDebug(tmpNode->name);
        writeDebug("aktuelle Rootkosten des tmpNode: ");
        writeDebug(xitoa(kosten));
        writeDebug("tmpLink->ziel->name: ");
        writeDebug(tmpLink->ziel->name);
        writeDebug("tmpLink->ziel->costsToRoot:");
        writeDebug(xitoa(tmpLink->ziel->costsToRoot));
        writeDebug("aktuelle Kosten des tmpLink->kosten");
        writeDebug(xitoa(tmpLink->kosten));

        if(tmpLink->ziel->root->nodeID <= tmpNode->root->nodeID)
        {
            writeDebug("aktueller Link hat eine bessere oder gleich gute Root als der aktuelle Node");
            //Wenn ein Nachbarknoten eine Root mit niedrigerer ID gefunden hat, dann uebernehme diese.
            if(((tmpLink->ziel->costsToRoot + tmpLink->kosten) < kosten) || ((tmpNode == start) && (tmpLink->ziel->root != start)))
            {
                //Wenn die kosten zur root niedriger als die bisherigen sind, dann uebernehme diese wirklich
                writeDebug("Guenstigeren Node gefunden.");
                tmpNode = tmpLink->ziel;
                kosten = tmpNode->costsToRoot + tmpLink->kosten;

            }
        }
        tmpLink->visited++;
        tmpLink = tmpLink->nachfolger;
        writeDebug("------------------------------");
    }
    if(tmpNode == start)
    {
        writeDebug("Node bleibt die root, da es keine bekannte root mit niedrigerer ID gibt.");
        //fprintf(stdout, "Node bleibt die root, da es keine bekannte root mit niedrigerer ID gibt.\n");
    }else
    {
        start->root = tmpNode->root;
        start->costsToRoot = kosten;
        start->nextHop = tmpNode;
    }
    return tmpNode;
}