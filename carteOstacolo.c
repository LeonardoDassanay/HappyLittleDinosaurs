//
// Created by leode on 03/03/2024.
//

#include "carteOstacolo.h"


Carte_ostacolo* inserisciInCimaOstacoli(Carte_ostacolo* mazzo, Carte_ostacolo aux)
{

    Carte_ostacolo * nuovaCarta= (Carte_ostacolo *)malloc(sizeof(Carte_ostacolo)); //allocazione memoria per il nuovo nodo

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

Carte_ostacolo* creaMazzoOstacoli()
{
    FILE* fp = fopen("ostacoli.txt", "r"); //apertura del file in lettura
    if (fp == NULL) {
        printf("ERRORE NELL'APERTURA DEL FILE ostacoli.txt\n");
        exit(EXIT_FAILURE);
    }

    int nl; //variabile contatore del numero di letture

    int nc=0; //numero carte ostacolo dello stesso tipo

    int ct=0; //contatore per il tipo di carta ostacolo

    Carte_ostacolo* mazzo= NULL; //variabile puntatore alla struttura delle carte ostacolo

    Carte_ostacolo aux; //variabile ausiliaria per l'acquisizione dei valori dal file


    //ciclo per creare una nuova carta finchè in numero di letture dal file è 2
    do
    {

        /*ogni volta che si incontra il numero di carte ostacolo di un certo tipo il numero dell'enumerazione viene incrementato,
         * questo viene fatto ad ogni ciclo per tutto il file, attraverso la variabile ct(contatore tipo).
         * inoltre viene salvato nella variabile nc il numero di carte di un certo tipo*/
        if (fscanf(fp, "%d", &nc) != 1)
            break;

        ct++;


        //ciclo per assegnare al numero di carte ostacolo dello stesso tipo i valori richiesti
        for (int i = 0; i < nc; ++i)
        {
            nl = 0;

            /*attraverso la fscanf vengono registrati i valori presi dal file nelle variabili di acquisizione
             * e viene anche incrementato il valore del contatore ad ogni lettura dal file*/
            nl += fscanf(fp, "\n%31[^\n]", aux.nome);
            nl += fscanf(fp, "\n%127[^\n]", aux.descrizione);
            aux.tipoOstacolo = ct;

            if (nl==2) //ho inserito un controllo sull'aggiunta dei nuovi nodi, perchè dopo la lettura dell'ultima riga, si rientrava nel ciclo e veniva creata una nuova carta
            {
                //creo le carte del mazzo assegnandoli i valori salvati nella variabil aux aux
                mazzo = inserisciInCimaOstacoli(mazzo, aux);
            }
        }

    }while(nl == 2);


    //chisura file
    fclose(fp);

    return mazzo;
}

void stampaOstacolo (Carte_ostacolo *mazzo)
{
    //messaggio che viene stampato se il mazzo è vuoto, o finito
    if (mazzo==NULL)
        return;
    else
    {
        printf("\nNOME CARTA:  %s\n"
               "DESCRIZIONE: %s\n",
               mazzo->nome, mazzo->descrizione);
        switch (mazzo->tipoOstacolo)
        {
            case STUDIO:
                printf("TIPO: STUDIO\n\n");
                break;
            case SOPRAVVIVENZA:
                printf("TIPO: SOPRAVVIVENZA\n\n");
                break;
            case SOCIALE:
                printf("TIPO: SOCIALE\n\n");
                break;
            default:
                printf("TIPO: ESAME\n\n");
                break;
        }
    }
}

void mescolaMazzoOstacoli (Carte_ostacolo* mazzo)
{
    /*quando il mazzo finisce o è vuoto la funzione restituisce NULL*/
    if (mazzo == NULL)
        return;


    int conta_carte = 0; //variabile per contare le carte del mazzo
    int num= 0; //variabile che contiene il numero generato casualmente per mischiare il mazzo

    Carte_ostacolo aux; //variabile ausiliaria utilizzata per contenere i dati della struttura carte_ostacolo

    Carte_ostacolo* mazzo_temporaneo = mazzo; //utilizzo la variabile mazzo_temporaneo per copiare il mazzo originale

    /*il ciclo conta il numero di carte del mazzo, questo mi servirà poi per allocare la memoria dell'array ausiliario*/
    while (mazzo_temporaneo != NULL)
    {
        conta_carte++;
        mazzo_temporaneo = mazzo_temporaneo->next;
    }

    /*creo l'array che mi servirà per mischiare il mazzo e alloco la memoria per il numero di carte del mazzo*/
    Carte_ostacolo* array_aux = (Carte_ostacolo*)calloc(conta_carte, sizeof(Carte_ostacolo));
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
        strcpy(mazzo_temporaneo->descrizione, array_aux[conta_carte].descrizione);
        mazzo_temporaneo->tipoOstacolo = array_aux[conta_carte].tipoOstacolo;
        mazzo_temporaneo = mazzo_temporaneo->next;

        conta_carte++;
    }

    /*la memoria del mazzo operazioni e dell' array ausiliario non mi servono più*/
    free(array_aux);
    free(mazzo_temporaneo);
}

Carte_ostacolo* deallocaMazzoOstacoli(Carte_ostacolo* mazzo)
{
    //variabile che acquisisce il puntatore al nodo successivo
    Carte_ostacolo* prossima_carta= NULL;

    //viene deallocata la memoria di ogni nodo del mazzo sino all'ultimo che punta a NULL
    while (mazzo != NULL)
    {
        prossima_carta = mazzo->next;
        free(mazzo);
        mazzo = prossima_carta;
    }

    return NULL;
}

int contaMazzoOstacoli (Carte_ostacolo* mazzo)
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

Carte_ostacolo* eliminaCartaOstacolo (Carte_ostacolo* mazzo, int nc)
{

    Carte_ostacolo* temp= NULL;

    // il ciclo libera la memoria allocata per un nodo, per N volte
    for (int i = 0; i < nc; ++i)
    {
        temp = mazzo; //utilizzo un mazzo ausiliario per cancellare i nodi e non perdere il mazzo originale

        mazzo = mazzo->next;

        free(temp);
    }

    return mazzo;
}

  Carte_ostacolo* pescaOstacolo(Carte_ostacolo* mazzo_ostacoli, Carte_ostacolo* carta_pescata)
{

    if (mazzo_ostacoli != NULL)
    {
        *carta_pescata = *mazzo_ostacoli;

        carta_pescata->next=NULL;

        mazzo_ostacoli = eliminaCartaOstacolo(mazzo_ostacoli, 1);
    }
    else
        printf("IL MAZZO OSTACOLI E' FINITO!!!!");


    return mazzo_ostacoli;
}



