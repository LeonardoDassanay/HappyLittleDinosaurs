//
// Created by leode on 03/03/2024.
//

#ifndef PROGETTO2_CARTEOSTACOLO_H
#define PROGETTO2_CARTEOSTACOLO_H

#endif //PROGETTO2_CARTEOSTACOLO_H

#include <stdio.h>
#include <stdlib.h>
#include "carteCfu.h"

#define MAX_DESCRIZIONE 128




/**Enumerazione che contiene tutti i tipi di carte ostacolo**/
typedef enum
{ STUDIO=1, SOPRAVVIVENZA, SOCIALE, ESAME} Tipo_ostacolo;


/**Struttura di una carta ostacolo, contiene tutti i dati della carta e il puntatore alla carta successiva,
 * ogni carta è un nodo del mazzo degli ostacoli**/
typedef struct carta_ostacolo
{
    char nome[MAX_CHAR];
    char descrizione[MAX_DESCRIZIONE];
    Tipo_ostacolo tipoOstacolo;
    struct carta_ostacolo* next;
} Carte_ostacolo;



/**La funzione serve per creare nuovi nodi ed inserirli in cima alla lista (mazzo),
 * prendendo come valori quelli di una variabile ausiliaria presa come parametro.
 * La funzione restituisce il puntatore alla cima**/
Carte_ostacolo* inserisciInCimaOstacoli(Carte_ostacolo*, Carte_ostacolo);

/**La funzione assegna ad ogni nuovo nodo, inserito in testa con la funzione inserisciInCima,
 * i valori presi dal file "carte.txt" attraverso la variabile ausiliaria aux.
 * La funzione restituisce la cima del mazzo**/
Carte_ostacolo* creaMazzoOstacoli();

/**La funzione serve a stampare l'intera lista (mazzo) nodo per nodo**/
void stampaOstacolo (Carte_ostacolo *);

/**Lafunzione serve per mischiare il mazzo delle carte ostacolo,
 * attraverso un array e un altro puntatore al mazzo, così da scorrere per tutte le operazioni necessarie senza perdere il riferimento al primo nodo.
 * La funzio restituisce il mazzo originale mischiato*/
void mescolaMazzoOstacoli (Carte_ostacolo*);

/**La funzione dealloca la memoria riservata alla lista (mazzo) nodo per nodo.
 * La funzione restituisce NULL**/
Carte_ostacolo* deallocaMazzoOstacoli(Carte_ostacolo*);

/**La funzione conta il numero delle carte rimaste nel mazzo.
 * La funzione restituisce il numero delle carte.**/
int contaMazzoOstacoli (Carte_ostacolo*);

/**La funzione elimina N nodi della lista (mazzo) uno alla volta partendo dalla cima.
 * la funzione restituisce il mazzo dopo le modifiche.**/
Carte_ostacolo* eliminaCartaOstacolo (Carte_ostacolo*, int);

/**La funzione pesca una carta dal mazzo ostacoli e la mette in una variabile per tenerla in gioco.
 * La funzione restituisce il puntatore alla carta pescata**/
Carte_ostacolo* pescaOstacolo(Carte_ostacolo*, Carte_ostacolo*);


