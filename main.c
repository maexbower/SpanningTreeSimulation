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
#endif //EINLESEN_H


int main(int argc, char* argv[])
{
    setbuf(stdout, NULL);
    //Prüfe die Parameter, mit denen das Programm aufgerufen wurde.
    if(argc < 2 || argc > 4) {
        writeDebug("Anzahl der Argumente passt nicht.\nEs muss mindestens die Topologiedatei angegeben sein\nAufruf: spt <ToPo File> [Anzahl Iterationen] [DEBUG]\n");
        return 1;
    }
    //Kopiere den ersten Parameter in eine persitente Variable.
    char *filename;
    int durchlaufe = 30;
    if(argc >= 3){
        if(atoi(argv[2]) > 0){
            durchlaufe = atoi(argv[2]);
            fprintf(stdout,"Die Anzahl der Durchläufe wurde auf: %d gesetzt.\n", durchlaufe);
        }else{
            if(strcmp(argv[2], "DEBUG") != 0){
                debugmode = 1;
                fprintf(stdout,"Debug Mode gesetzt.\n");
            }
        }
        if(argc > 3){
            if(atoi(argv[3]) > 0){
                durchlaufe = atoi(argv[2]);
                fprintf(stdout,"Die Anzahl der Durchläufe wurde auf: %d gesetzt.\n", durchlaufe);
            }else{
                if(strcmp(argv[2], "DEBUG") != 0){
                    debugmode = 1;
                    fprintf(stdout,"Debug Mode gesetzt.\n");
                }
            }
        }
    }
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
    int konsitenz = checkDatenKonsitenz(&nodelist);
    if(konsitenz>0)
    {
        fprintf(stdout, "Es wurde ein Fehler in der Datenkonsitenz gefunden. Bitte kontrollieren Sie die Topologie Datei.\n");
        if(konsitenz == 1)
        {
            fprintf(stdout, "Ein Node ist nicht definiert.\n");
        }
        if(konsitenz == 2)
        {
            fprintf(stdout, "Ein Node ist nicht angeschlossen.\n");
        }
        return 1;
    }
    fprintf(stdout, "Datei wurde eingelesen. Dies ist der aktuelle Stand:\n");
    printStructure(&nodelist);
    srand((unsigned)time(NULL));
    if (USESTATICRAND == 1)
    {
        srand(1);
    }
    p_node tmpNode;
    for(int i = 0; i < durchlaufe; i++)
    {
        tmpNode = getRandomNode(&nodelist);
        fprintf(stdout, "#%d: Node %s ist an der Reihe.\n",i, tmpNode->name);
        findroot(tmpNode);
    }
    printStructure(&nodelist);
    return 0;
}