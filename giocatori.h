//
// Created by leode on 03/03/2024.
//

#ifndef PROGETTO2_PERSONAGGI_H
#define PROGETTO2_PERSONAGGI_H

#endif //PROGETTO2_PERSONAGGI_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "carteOstacolo.h"

#define MAX_GIOCATORI 4


/**Struttura dei personaggi, contiene tutti i dati delle plance di ogni personaggio,
 * verrà assegnato un personaggio diverso ad ogni giocatore con un array di personaggi**/
typedef struct personaggio
{
    char nome[MAX_CHAR];
    int bonus_malus[ESAME]; //array di interi che contiene i bonus e i malus che ogni personaggio ha per ogni tipologia di carta ostacolo
} Personaggio;


/**Struttura del giocatore, contiene i dati del giocatore, ad  ogni giocatore viene assegnato un personaggio,
 * inoltre ogni personaggio ha un mazzo di carte cfu (le carte che ha in mano) e un mazzo di carte ostacolo (le carte ricevute durante il gioco)**/
typedef struct gioctore
{
    char nome_utente[MAX_CHAR];
    Personaggio personaggio;
    int punti_cfu;
    Carte_cfu* carteCfu;
    Carte_ostacolo* carteOstacolo;
    struct gioctore* next;
} Giocatore;


/**La funzione serve per salvare in una array di personaggi, di dimensione uguale al massimo di giocatori,
 * le informazioni prese dal file personaggi.txt.
 * La funzione restituisce l'array di strutture personaggio**/
Personaggio* caricaPersonaggi();


/**La funzione mescola casualmente gli elementi di una array di 4 numeri, la utilizzo per assegnare casualmente un personaggio al giocatore.
 * La funzione restituisce l'array ordinato in modo casuale**/
int* arrayPosizioniCasuali();


/**La funzione serve per creare nuovi nodi in coda alla lista, prendendo come valori quelli di una variabile ausiliaria presa come parametro.
 * La funzione restituisce il puntatore alla testa della lista di giocatori**/
Giocatore* creaGiocatoreInCoda(Giocatore*, Giocatore);


/**La funzione assegna ad ogni nuovo nodo (giocatore) le informazioni necessarie,
 * nome utente (richiesto all'utente) e personaggio (assegnato casualmente)
 * le carte cfu e le carte ostacolo non vengono inserite perchè all'inizio del gioco il giocatore non ne dispone.
 * La funzione restituisce la lista di giocatori**/
Giocatore* creaGiocatori(Personaggio*);

/**La funzione serve a stampare l'intera lista di giocatori nodo per nodo**/
void stampaGiocatore (Giocatore*);

/**La funzione dealloca la memoria riservata alla lista nodo per nodo.
 * La funzione restituisce NULL**/
Giocatore* deallocaGiocatori(Giocatore *);

/**La funzione conta il numero di giocatori.
 * La funzione restituisce il numero di giocatori.**/
int contaGiocatori (Giocatore*);

/**La funzione conta il numero di carte che ha ogni giocatore in mano.
 * La funzione restituisce un array di interi, che contiene il numero di carte in mano di ogni giocatore.**/
int* contaMani (Giocatore*, int );

/**La funzione fa pescare una cara ad un giocatore, e la elimina dal mazzo.
 * La funzione restituisce il mazzo delle carte cfu dop l'eliminazione della carta pescata**/
Carte_cfu* pescaCarteCfu(Carte_cfu*, Giocatore*);

/**La funzione stampa le informazioni (non visualizza le carte in mano ma solo il loro numero) di tutti i giocatori apparte quello che sta giocando**/
void stampaAvversari (Giocatore*, int, int);

/**La funzione serve a sapere se un giocatore ha carte cfu in mano.
 * Se il giocatore ha carte Cfu in mano la funzione restituisce 0,
 * altrimenti restituisce 1.**/
bool ripescaCfu(Giocatore*);

/**La funzione assegna i punti cfu accumulati al vincitore/i del turno e **/
void findVinTurno (Giocatore*, int*);


void spareggioPerdenti (Giocatore*, int*, Carte_ostacolo*, Carte_cfu*);

