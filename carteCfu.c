//
// Created by leode on 03/03/2024.
//

#include "carteCfu.h"



Carte_cfu* inserisciInCimaCfu(Carte_cfu* mazzo, Carte_cfu aux)
{

    Carte_cfu * nuovaCarta= (Carte_cfu *)malloc(sizeof(Carte_cfu)); //allocazione memoria per il nuovo nodo

    //controllo dell'allocazione di memoria
    if (nuovaCarta == NULL)
    {
        printf("ERRORE NELL'ALLOCAZIONE DELLA CARTA CFU");
        exit(EXIT_FAILURE);
    }

    //acquisizione dei valori dalla variabile ausiliaria
    *nuovaCarta = aux;


    //inserimento del nuovo nodo in cima
    if(mazzo==NULL)
        nuovaCarta->next=NULL;
    else
        nuovaCarta->next=mazzo;


    mazzo = nuovaCarta;

    return mazzo;
}

Carte_cfu* creaMazzoCfu()
{
    FILE* fp = fopen("carte.txt", "r"); //apertura del file in lettura
    if (fp == NULL) {
        printf("ERRORE NELL'APERTURA DEL FILE carte.txt\n");
        exit(EXIT_FAILURE);
    }

    int nl; //variabile contatore del numero di letture

    int nc= 0; //variabile che acquisisce il numero di carte identiche dal file

    Carte_cfu* mazzo= NULL; //variabile puntatore alla struttura delle carte cfu,

    Carte_cfu aux; //variabile ausiliaria per l'acquisizione dei valori dal file


    //ciclo per creare una nuova carta finchè in numero di letture dal file è 4
    do
    {

        // il numero di letture viene azzerato ad ogni ripetizione del ciclo
        nl = 0;
        /*attraverso la fscanf vengono registrati i valori presi dal file nelle variabili di acquisizione
         * e viene anche incrementato il valore del contatore ad ogni lettura dal file*/
        nl += fscanf(fp, "%d", &nc);
        int effetto = 0;
        nl += fscanf(fp, " %d", &effetto);
        aux.effetto = (Effetto) effetto;
        nl += fscanf(fp, " %d", &aux.nCfu);
        nl += fscanf(fp, " %31[^\n]", aux.nome);

        /*ciclo per la creazione delle carte, anche i doppioni*/
        if (nl==4) //ho inserito un controllo sull'aggiunta dei nuovi nodi, perchè dopo la lettura dell'ultima riga, si rientrava nel ciclo e veniva creata una nuova carta
        {
            for (int i = 0; i < nc; ++i) {
                mazzo = inserisciInCimaCfu(mazzo, aux);
            }
        }

    }while(nl == 4);

    //chisura file
    fclose(fp);

    return mazzo;
}

void stampaMazzoCfu (Carte_cfu *mazzo)
{
    //ciclo che continua finchè il nodo non è NULL

    int n_carta = 1;


    while (mazzo!=NULL)
    {
        printf("\nNOME CARTA:  %s\n"
               "NUMERO CFU: %d                   [%d]\n",
               mazzo->nome, mazzo->nCfu, n_carta);
        switch (mazzo->effetto)
        {
            case NESSUNO:
                printf("EFFETTO: NESSUNO\n\n");
                break;
            case SCARTAP:
                printf("EFFETTO: SCARTAP\n\n");
                break;
            case RUBA:
                printf("EFFETTO: RUBA\n\n");
                break;
            case SCAMBIADS:
                printf("EFFETTO: SCAMBIADS\n\n");
                break;
            case SCARTAE:
                printf("EFFETTO: SCARTAE\n\n");
                break;
            case SCARTAC:
                printf("EFFETTO: SCARTAC\n\n");
                break;
            case SCAMBIAP:
                printf("EFFETTO: SCAMBIAP\n\n");
                break;
            case DOPPIOE:
                printf("EFFETTO: DOPPIE\n\n");
                break;
            case SBIRCIA:
                printf("EFFETTO: SBIRCIA\n\n");
                break;
            case SCAMBIAC:
                printf("EFFETTO: SCAMBIAC\n\n");
                break;
            case ANNULLA:
                printf("EFFETTO: ANNULLA\n\n");
                break;
            case AUMENTA:
                printf("EFFETTO: AUMENTA\n\n");
                break;
            case DIMINUISCI:
                printf("EFFETTO: DIMINUISCI\n\n");
                break;
            case INVERTI:
                printf("EFFETTO: INVERTI\n\n");
                break;
            case SALVA:
                printf("EFFETTO: SALVA\n\n");
                break;
            default:
                printf("EFFETTO: DIROTTA\n\n");
                break;
        }


        mazzo = mazzo->next; //si passa al nodo successivo
        n_carta++;
    }

    //messaggio che viene stampato se il mazzo è vuoto, o finito
    if (mazzo==NULL)
        return;

}

void mescolaMazzoCfu(Carte_cfu* mazzo)
{


    int conta_carte = 0; //variabile per contare le carte del mazzo
    int num= 0; //variabile che contiene il numero generato casualmente per mischiare il mazzo

    Carte_cfu aux; //variabile ausiliaria utilizzata per contenere i dati della struttura carte_cfu

    Carte_cfu* mazzo_temporaneo = mazzo; //utilizzo la variabile mazzo_temporaneo per copiare il mazzo originale

    /*il ciclo conta il numero di carte del mazzo, questo mi servirà poi per allocare la memoria dell'array ausiliario*/
    while (mazzo_temporaneo != NULL)
    {
        conta_carte++;
        mazzo_temporaneo = mazzo_temporaneo->next;
    }

    /*creo l'array che mi servirà per mischiare il mazzo e alloco la memoria per il numero di carte del mazzo*/
    Carte_cfu* array_aux = (Carte_cfu*)calloc(conta_carte ,sizeof(Carte_cfu));
    if (array_aux == NULL)
    {
        printf("ERRORE NELL'ALLOCAZIONE PER L'ARRAY DEL MAZZO");
        exit(EXIT_FAILURE);
    }

    /*azzero conta_carte così da poterla utilizzare come indice del vettore*/
    conta_carte = 0;

    mazzo_temporaneo = mazzo; //nel mazzo di ausilio, dopo averlo utilizzato ed essere arrivato alla fine, risalvo le informazioni del mazzo originale

    /*utilizzo il ciclo per assegnare ad ogni posizione dell'array le informazioni di un nodo del mazzo,
     * e incremento count_carte per passare all'indice successivo del vettore*/
    while (mazzo_temporaneo != NULL)
    {
        array_aux[conta_carte] = *mazzo_temporaneo;

        mazzo_temporaneo = mazzo_temporaneo->next;

        conta_carte++;
    }

    /*mischio l'array contenente le informazioni del mazzo scambiando gli indici*/
    for (int i = 0; i < conta_carte; ++i)
    {
        num = rand() % conta_carte;

        aux = array_aux[i];
        array_aux[i] = array_aux[num];
        array_aux[num] = aux;
    }

    mazzo_temporaneo = mazzo; //nel mazzo di ausilio, dopo averlo utilizzato ed essere arrivato alla fine, risalvo le informazioni del mazzo originale

    conta_carte = 0; //riutilizzo la variabile conta_carte come indice per scorrere l'array

    /*ciclo per riassegnare il mazzo mischiato attraverso l'array alla lista mazzo*/
    while (mazzo_temporaneo != NULL)
    {
        strcpy(mazzo_temporaneo->nome, array_aux[conta_carte].nome);
        mazzo_temporaneo->nCfu = array_aux[conta_carte].nCfu;
        mazzo_temporaneo->effetto = array_aux[conta_carte].effetto;
        mazzo_temporaneo = mazzo_temporaneo->next;

        conta_carte++;
    }

    /*la memoria del mazzo operazioni e dell' array ausiliario non mi servono più*/
    free(array_aux);
    free(mazzo_temporaneo);

}

Carte_cfu *deallocaMazzoCfu(Carte_cfu* mazzo)
{
    //variabile che acquisisce il puntatore al nodo successivo
    Carte_cfu* prossima_carta= NULL;

    //viene deallocata la memoria di ogni nodo del mazzo sino all'ultimo che punta a NULL
    while (mazzo != NULL)
    {
        prossima_carta = mazzo->next;
        free(mazzo);
        mazzo = prossima_carta;
    }

    return NULL;
}

int contaMazzoCfu (Carte_cfu* mazzo)
{
    int n_carte=0;

    if (mazzo==NULL)
        n_carte=0;

    else
    {
        do
        {
            n_carte++;
            mazzo=mazzo->next;
        } while (mazzo!=NULL);
    }


    return n_carte;
}

Carte_cfu* eliminaCartaCfu (Carte_cfu* mazzo)
{

    Carte_cfu* temp=  mazzo; //utilizzo un mazzo ausiliario per cancellare i nodi e non perdere il mazzo originale

    mazzo = mazzo->next;

    free(temp);

    return mazzo;
}

Carte_cfu* utilizzaCarta (Carte_cfu* mazzo_scarti, Carte_cfu** mazzo, int n_carta)
{
    Carte_cfu* mazzo_temp = *mazzo; //creo il mazzo temporaneo per scorrere il mazzo cfu

    // gestisco il mazzo vuoto
    if (mazzo_temp==NULL)
    {
        printf("MAZZO VUOTO\n");
        return mazzo_scarti;
    }

    if (n_carta < 1 || n_carta > contaMazzoCfu(*mazzo)) {
        printf("Numero carta non valido\n");
        return mazzo_scarti;
    }

    /*ciclo per trovare la carta da utilizzare*/
    for (int i = 0; i < n_carta-1 ; ++i)
    {
        mazzo_temp = mazzo_temp->next;
    }
    mazzo_scarti = inserisciInCimaCfu(mazzo_scarti, *mazzo_temp); // la carta da utilizzare viene messa in cima al mazzo degli scarti

    Carte_cfu* p_temp = mazzo_temp; //la variabile prende il puntatore alla carta successiva a quella da eliminare



    //se la carta scelta è la prima devo solo scorrere il puntatore alla cima del mazzo originale che ho passato come parametro attraverso un doppio puntatore
    if (n_carta==1)
    {
        *mazzo = (*mazzo)->next;

        mazzo_temp->next=NULL;

        free(mazzo_temp);
    }

    else
    {
        mazzo_temp = *mazzo; //il mazzo temporaneo è di nuovo uguale al mazzo cfu


        /*ciclo per trovare la carta precedente a quella da utilizzare*/
        for (int i = 0; i < n_carta-2 ; ++i)
        {
            mazzo_temp = mazzo_temp->next;
        }

        mazzo_temp->next = p_temp->next; //imposto il campo next della carta precedente all'indirizzo di quella successiva, rispetto a quella da utilizzare

        mazzo_temp = p_temp;

        mazzo_temp->next=NULL;

        free(mazzo_temp);
    }




    return mazzo_scarti;
}



