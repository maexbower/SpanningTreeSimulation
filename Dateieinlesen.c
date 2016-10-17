#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ZEILENLAENGE 255
#define IDTRENNZEICHEN =
#define KOSTENTRENNZEICHEN -
#define MAX_NODE_ID 10
#define MAX_KOSTEN 100
#define MAX_IDENT 10
#define MAX_ITEMS 100

int main() {

	FILE *graph;
	char puffer[ZEILENLAENGE];
	char knotenA[MAX_IDENT];
	char knotenB[MAX_IDENT];
	int kosten;
	int id;
	int i, count,r_count;
	int read_count;

	//DATEI EINLESEN
	graph = fopen("//home/anja/Dokumente/graphgemischt.txt", "r");

	if(graph == NULL)
			printf("Datei konnte nicht geöffnet werden.\n");


	//PUFFER MIT 0 INITIALISIEREN
	for(i=0;i<ZEILENLAENGE;i++){
				puffer[i]=0;
	}

	//DATEN AUS STRING AUSLESEN
	while(fgets(puffer, ZEILENLAENGE, graph) != NULL){

		count=0;
		while(puffer[count] == ' ' && count+1 < ZEILENLAENGE ){
			count=count+1;
		}
		if(puffer[count] == '/' && puffer[count+1] == '/'){
			printf("HIER KOMMT EIN KOMMENTAR");
		}
		else{
			for(i=count;i<ZEILENLAENGE;i++){
				if(puffer[i] == '='){
					printf("HIER KOMMT EIN KNOTEN");
					sscanf(puffer, "%s = %d" , knotenA, &id);
					printf("Knoten: %s mit der ID: %d\n", knotenA, id);
				}
				else if(puffer[i] == '-'){
					printf("HIER KOMMT EINE ZUWEISUNG");
					sscanf(puffer,"%s - %s : %d", knotenA, knotenB, &kosten);
					printf("Knoten: %s und Konten: %s haben eine Verbindung: %d\n", knotenA, knotenB, kosten);
				}
			}
		}

		//AUSGABE DER EINGELESENEN ZEILE
		printf("%s", puffer);

		//PUFFER MIT 0 INITIALISIEREN
		for(i=0;i<ZEILENLAENGE;i++){
			puffer[i]=0;
		}
	}



	fclose(graph);
	return EXIT_SUCCESS;
}
