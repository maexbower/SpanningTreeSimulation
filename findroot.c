/* Dijkstra's Algorithm in C
 * http://www.codewithc.com/dijkstras-algorithm-in-c/
 * */

#include "findroot.h"

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
