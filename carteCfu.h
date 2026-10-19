//
// Created by leode on 03/03/2024.
//

#ifndef PROGETTO2_CARTECFU_H
#define PROGETTO2_CARTECFU_H

#endif //PROGETTO2_CARTECFU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_CHAR 32
#define CARTE_IN_MANO 5


/**Enumerazione che contiene gli effetti di tutte le carte cfu**/
typedef enum
{NESSUNO, SCARTAP, RUBA, SCAMBIADS, SCARTAE, SCARTAC, SCAMBIAP, DOPPIOE, SBIRCIA, SCAMBIAC, ANNULLA, AUMENTA, DIMINUISCI,INVERTI, SALVA, DIROTTA } Effetto;


/**Struttura di una carta cfu, contiene tutti i dati della carta e il puntatore alla carta successiva,
 * ogni carta è un nodo del mazzo**/
typedef struct carta_cfu
{
    char nome[MAX_CHAR];
    int nCfu;
    Effetto effetto;
    struct carta_cfu* next;
} Carte_cfu;



/**La funzione serve per creare nuovi nodi ed inserirli in cima alla lista (mazzo),
 * prendendo come valori quelli di una variabile ausiliaria presa come parametro.
 * La funzione restituisce il puntatore alla cima**/
Carte_cfu* inserisciInCimaCfu(Carte_cfu*, Carte_cfu);


/**La funzione assegna ad ogni nuovo nodo, inserito in testa con la funzione inserisciInCima,
 * i valori presi dal file "carte.txt" attraverso la variabile ausiliaria aux.
 * La funzione restituisce la cima del mazzo**/
Carte_cfu* creaMazzoCfu();


/**La funzione serve a stampare l'intera lista (mazzo) nodo per nodo**/
void stampaMazzoCfu (Carte_cfu*);


/**La funzione serve per mischiare il mazzo delle carte cfu,
 * attraverso un array e un altro puntatore al mazzo, così da scorrere per tutte le operazioni necessarie senza perdere il riferimento al primo nodo.
 * La funzio restituisce il mazzo originale mischiato*/
void mescolaMazzoCfu (Carte_cfu*);


/**La funzione dealloca la memoria riservata alla lista (mazzo) nodo per nodo.
 * La funzione restituisce NULL**/
Carte_cfu* deallocaMazzoCfu(Carte_cfu*);


/**La funzione conta il numero delle carte rimaste nel mazzo.
 * La funzione restituisce il numero delle carte.**/
int contaMazzoCfu (Carte_cfu*);


/**La funzione elimina N nodi della lista (mazzo) uno alla volta partendo dalla cima.
 * la funzione restituisce il mazzo dopo le modifiche.**/
Carte_cfu* eliminaCartaCfu (Carte_cfu*);


/**La funzione serve per copiare una carta da una lista di carte cfu (mano del giocatore) ad un altra (mazzo scarti), eliminandola dalla lista di origine.
 * La funzione restituisce la lista di destinazione (mazzo scarti).**/
Carte_cfu* utilizzaCarta (Carte_cfu*, Carte_cfu**, int );











