#ifndef SPANNINGTREE_MAIN_H
#include "main.h"
#endif //SPANNINGTREE_MAIN_H
#ifndef SPANNINGTREE_MYTOOLS_H
#include "mytools.h"
#endif //SPANNINGTREE_MYTOOLS_H
#ifndef SPANNINGTREE_DATASTRUCTURE_H
#include "datastructure.h"
#endif //SPANNINGTREE_DATASTRUCTURE_H
#ifndef SPANNINGTREE_DATEIEINLESEN_H
#include "dateieinlesen.h"
#endif //SPANNINGTREE_DATEIEINLESEN_H
#ifndef DIJKSTRA_DIJKSTRA_H
#include "findroot.h"
#endif //DIJKSTRA_DIJKSTRA_H

int main(int argc, char* argv[])
{
    setbuf(stdout, NULL);
    //Prüfe die Parameter, mit denen das Programm aufgerufen wurde.
    if(argc < 2 || argc > 3) {
        writeDebug("Anzahl der Argumente passt nicht.\nEs muss mindestens die Topologiedatei angegeben sein\nAufruf: spt <ToPo File> [Name des Graphen]\n");
        return 1;
    }
    //Kopiere den ersten Parameter in eine persitente Variable.
    char *filename;
    filename = xmalloc(sizeof(argv[1] + 1));
    strcpy(filename, argv[1]);
    //Prüfe die exitenz und lesbarkeit der Definitionsdatei
    if(fileReadable(filename) != 0)
    {
        writeDebug("Datei nicht lesbar.");
        return 1;
    }
    writeDebug("Öffne Datei");
    p_node nodelist;
    nodelist = 0;
    //Datei Einlesen
    dateieinlesen(filename, &nodelist);
    //Konsitenzprüfung
    if(checkDatenKonsitenz(&nodelist)>0)
    {
        fprintf(stdout, "Es wurde ein Fehler in der Datenkonsitenz gefunden. Bitte kontrollieren Sie die Topologie Datei.\n");
        return 1;
    }
    //ToDo start Spanning Tree Actions
    fprintf(stdout, "Datei wurde eingelesen. Dies ist der aktuelle Stand:\n");
    printStructure(&nodelist);
    srand((unsigned)time(NULL));
    if (USESTATICRAND == 1)
    {
        srand(1);
    }
    for(int i = 1; i< 100; i++)
    {
        fprintf(stdout, "Suche besten Weg %d\n", i);
        findroot(getRandomNode(&nodelist));
        fprintf(stdout, "Die Struktur hat sich wie folgt geaendert:\n");
        printStructure(&nodelist);
    }

    //testfunction(filename);
    return 0;
}


void testfunction(char* filename)
{
    p_node nodelist;
    nodelist = 0;
    dateieinlesen(filename, &nodelist);
    p_link linklist;
    linklist = 0;
    p_node testnode = createNode("Beta1", 1);
    p_node testnode2 = createNode("Beta2", 2);
    p_link testlink = createLink(12, &testnode2, &testnode);
    p_link testlink2 = createLink(9, &testnode2, &testnode);
    if(testnode == 0)
    {
        writeDebug("Fehler beim erstellen des Testnodes.");
    }else{
        addNodeToList(testnode, &nodelist);
        writeDebug("Füge zweiten Node hinzu:");
        addNodeToList(testnode2,&nodelist);
        writeDebug("Das Element 1 befindet sich in der Liste?");
        writeDebug(xitoa(isInNodeList(testnode, &nodelist)));
        writeDebug("Das Element der Name Beta1 befindet sich in der Liste?");
        writeDebug(ptoa(nodeExitsByName("Beta1", &nodelist)));
        writeDebug("Das Element der ID 1 befindet sich in der Liste?");
        writeDebug(ptoa(nodeExitsByID(1, &nodelist)));
        writeDebug("Entferne Node aus Liste");
        removeNodeFromList(testnode,&nodelist);
        writeDebug("Lösche Node");
        deleteNode(&testnode);
        printNode(testnode);
        writeDebug("Das Element 1 befindet sich in der Liste?");
        writeDebug(xitoa(isInNodeList(testnode, &nodelist)));
        writeDebug("Die Nodeliste hat noch folgenden Pointer");
        writeDebug(ptoa(nodelist));
    }
    if(testlink == 0)
    {
        writeDebug("Fehler beim erstellen des Testlinks.");
    }else{
        addLinkToLinklist(testlink, &linklist);
        writeDebug("Das Element befindet sich noch in der Liste?");
        writeDebug(xitoa(isInLinkList(testlink, &linklist)));
        writeDebug("Das Element von Node 1 zu 2 befindet sich noch in der Liste?");
        writeDebug(ptoa(linkExists(testnode, testnode2, &linklist)));
        writeDebug("Füge zweiten Link hinzu:");
        addLinkToLinklist(testlink2,&linklist);
        writeDebug("Entferne link aus Liste");
        removeLinkFromList(testlink,&linklist);
        writeDebug("Lösche Link");
        deleteLink(&testlink);
        printLink(testlink);
        writeDebug("Das Element befindet sich noch in der Liste?");
        writeDebug(xitoa(isInLinkList(testlink, &linklist)));
        writeDebug("Die Linkliste hat noch folgenden Pointer");
        writeDebug(ptoa(linklist));
    }
}