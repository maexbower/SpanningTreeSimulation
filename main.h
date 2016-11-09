//
// Created by max on 02.10.16.
//
#ifndef SPANNINGTREE_MAIN_H
#define SPANNINGTREE_MAIN_H
#endif //SPANNINGTREE_MAIN_H


//lege die Laufzeitvariablen fest.
#define MAX_ITEMS 99        //maximale Anzahl an Zeilen in der Definitionsdatei
#define MAX_KOSTEN 99       //maximale Kosten pro Knoten
#define MAX_NODE_ID 99      //maximaler Wert der Node ID
#define MAX_IDENT 99         //maximale Anzahl an Stellen für den Node Identifikator

//Parameter zum Auslesen der Topologie
#define ZEILENLAENGE 255
#define KOMMENTARCHAR '/'   //String mit dem eine Kommentar beginnt
#define IDTRENNZEICHEN '='       //mögliche Zeichen um Zuweisungen zu machen
#define KOSTENTRENNZEICHEN '-'        //Zeichen zwischen zwei Elementen
#define IGNORECHAR ' '        //Zeichen das ignoriert wird

//Standardwerte für Nodes
#define STDLINK 0
#define STDNEXTHOP 0
#define STDMSGCNT 0
#define STDCOSTSTOROOT 0
#define STDNACHFOLGER 0
#define STDVORGAENGER 0
#define STDNODEID -1
//Standardwerte für Links
#define STDCOST 0
#define STDVISITED 0

//Parameter zur darstellung
#define MINCHARSFORNAME 12

//Parameter fuer die Berechnung
#define USESTATICRAND 0
//Alles Andere wird durch gegebene Werte oder das Element selbst ersetzt.

////////////////////////////////
// pre define Functions
////////////////////////////////
