#ifndef SPANNINGTREE_DATASTRUCTURE_H
#include "main.h"
#endif //SPANNINGTREE_DATASTRUCTURE_H
#ifndef SPANNINGTREE_MYTOOLS_H
#include "mytools.h"
#endif //SPANNINGTREE_MYTOOLS_H
#ifndef SPANNINGTREE_DATEIEINLESEN_H
#include "dateieinlesen.h"
#endif //SPANNINGTREE_DATEIEINLESEN_H
#ifndef SPANNINGTREE_DATASTRUCTURE_H
#include "datastructure.h"
#endif //SPANNINGTREE_DATASTRUCTURE_H

////////////////////////////////
///Functions
////////////////////////////////
int dateieinlesen(char* filepath, p_node *nodelist) {

	FILE *graph;
	char puffer[ZEILENLAENGE];
	char knotenA[MAX_IDENT];
	char knotenB[MAX_IDENT];
    char tmpBuffer[999];
	int kosten;
	int id;
	int i, count,r_count;
	int read_count;

	//DATEI EINLESEN
	graph = openFile(filepath);

	if(graph == NULL)
        writeDebug("Datei konnte nicht geöffnet werden.\n");


	//PUFFER MIT 0 INITIALISIEREN
	for(i=0;i<ZEILENLAENGE;i++){
				puffer[i]=0;
	}
	r_count = 0; //Zeilenzähler
	//DATEN AUS STRING AUSLESEN
	while(fgets(puffer, ZEILENLAENGE, graph) != NULL){
		if(r_count >= MAX_ITEMS)
		{
			writeDebug("Maximale Anzahl an Einträgen in Topologiedatei überschritten.");
			break;
		}
		r_count++;
		count=0;
		while(puffer[count] == IGNORECHAR && count+1 < ZEILENLAENGE ){
			count=count+1;
		}
		if(puffer[count] == KOMMENTARCHAR && puffer[count+1] == KOMMENTARCHAR){
            writeDebug("HIER KOMMT EIN KOMMENTAR");
		}
		else{
			for(i=count;i<ZEILENLAENGE;i++){
				if(puffer[i] == IDTRENNZEICHEN){
                    writeDebug("HIER KOMMT EIN KNOTEN");
					sscanf(puffer, "%s = %d" , knotenA, &id);
					sprintf(tmpBuffer,"Knoten: %s mit der ID: %d\n", knotenA, id);
                    writeDebug(tmpBuffer);
					if(stringlength(knotenA) > MAX_IDENT)
					{
						writeDebug("KnotenIDENT zu lange. Überspringe.");
						continue;
					}
					p_node nodeA = nodeExitsByName(knotenA, nodelist);
					if(nodeA == 0){
						nodeA = createNode(knotenA, id);
						addNewNode(nodeA, nodelist);
					}else{
						writeDebug("Node existiert bereits. Dies sollte nicht passieren.");
					}
				}
				else if(puffer[i] == KOSTENTRENNZEICHEN){
                    writeDebug("HIER KOMMT EINE ZUWEISUNG");
					sscanf(puffer,"%s - %s : %d", knotenA, knotenB, &kosten);
					sprintf(tmpBuffer, "Knoten: %s und Konten: %s haben eine Verbindung: %d\n", knotenA, knotenB, kosten);
                    writeDebug(tmpBuffer);
                    if(stringlength(knotenA) > MAX_IDENT)
					{
						writeDebug("KnotenIDENT zu lange. Überspringe.");
						continue;
					}
					if(stringlength(knotenB) > MAX_IDENT)
					{
						writeDebug("KnotenIDENT zu lange. Überspringe.");
						continue;
					}
					//Checke ob Knoten A in Nodelist
					p_node nodeA = nodeExitsByName(knotenA, nodelist);
					if(nodeA == 0){
						writeDebug("Knoten 1 existiert noch nicht.");
						nodeA = createNode(knotenA, MAX_NODE_ID);
						addNewNode(nodeA, nodelist);
					}
					//Checke ob Knoten B in Nodelist
					p_node nodeB = nodeExitsByName(knotenB, nodelist);
					if(nodeB == 0) {
                        writeDebug("Knoten 2 existiert noch nicht.");
						nodeB = createNode(knotenB, MAX_NODE_ID);
						addNewNode(nodeB, nodelist);
					}
                    addNewLink(nodeA, nodeB, kosten, nodelist);
				}
			}
		}

		//AUSGABE DER EINGELESENEN ZEILE
		writeDebug(puffer);
		//PUFFER MIT 0 INITIALISIEREN
		for(i=0;i<ZEILENLAENGE;i++){
			puffer[i]=0;
		}
	}



	closeFile(graph);
	return EXIT_SUCCESS;
}

int fileReadable(char *filename)
{   //Gets the Filename and return 0 when the file is readable and 1 when the file is not readable
	writeDebug("fileReadable Aufgerufen mit:");
	writeDebug(filename);
	FILE *p_file;
	p_file = openFile(filename);
	if(p_file != 0){
		return closeFile(p_file);
	}
	return 1;
}
FILE* openFile(char *filename)
{
	FILE *p_file;
	p_file = fopen(filename, "r");
	if(p_file != 0){
		writeDebug("Datei wurde erfolgreich geöffnet. Pointer ist:");
		writeDebug(ptoa(p_file));
		return p_file;
	}
	writeDebug("Datei konnte nicht geöffnet werden. Der Fehlercode ist:");
	writeDebug(strerror(errno));
	return 0;
}
int closeFile(FILE *p_file)
{
	int result;
	result = fclose(p_file);
	if(result != 0) {
		writeDebug("Datei konnte nicht geschlossen werden. Der Fehlercode ist:");
		writeDebug(strerror(errno));
		return 1;
	}
	writeDebug("Datei wurde geschlossen. Der Returncode ist:");
	writeDebug(itoa(result));
	return 0;
}
p_node addNewNode(p_node node, p_node *nodelist)
{
	p_node tmpNode = *nodelist;
	p_link tmpLink;
	while(tmpNode != 0)
	{
		//Add new Node to existing Node Linklist
		tmpLink = linkExists(node, tmpNode, &tmpNode->plink);
		if(tmpLink == 0)
		{
			tmpLink = createLink(STDCOST, &node, &tmpNode);
			addLinkToLinklist(tmpLink, &tmpNode->plink);
		}
		//Add existing Node to new Node Linklist
		tmpLink = linkExists(node, tmpNode, &node->plink);
		if(tmpLink == 0)
		{
			tmpLink = createLink(STDCOST, &node, &tmpNode);
			addLinkToLinklist(tmpLink, &node->plink);
		}
		tmpNode = tmpNode->nachfolger;
	}
	//füge alle bestehenden Nodes zur Linklist hinzu.
	addNodeToList(node, nodelist);
	//printNode(node);
	return *nodelist;
}
p_node addNewLink(p_node start, p_node ziel, int kosten, p_node *nodelist)
{
	if(kosten > MAX_KOSTEN)
	{
		writeDebug("Die Kosten überschreiten die MAXIMALEN Kosten.");
		kosten = MAX_KOSTEN;
	}
	p_link tmpLink;
	//Add new Node to existing Node Linklist
	tmpLink = linkExists(start, ziel, &start->plink);
	if(tmpLink == 0)
	{
		writeDebug("Link existiert nicht. Das sollte nicht passieren!");
		return 0;
	}
	tmpLink->kosten = kosten;

	//Add existing Node to new Node Linklist
	tmpLink = linkExists(start, ziel, &ziel->plink);
	if(tmpLink == 0)
	{
		writeDebug("Link existiert nicht. Das sollte nicht passieren!");
		return 0;
	}
	tmpLink->kosten = kosten;
	return *nodelist;
}