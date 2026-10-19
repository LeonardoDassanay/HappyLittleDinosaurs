//
// Created by leode on 03/03/2024.
//

#include "giocatori.h"

Personaggio* caricaPersonaggi()
{
    int nl;  //variabile contatore per il numero di letture dal file
    int nPersonaggio=0; //variabile per tenere conto del numero relativo al personaggio (serve per l'indice dell'array di personaggi)

    /*allocazione memoria per l'array di personaggi e controllo*/
    Personaggio* arrayPersonaggi = calloc(MAX_GIOCATORI, sizeof (Personaggio));
    if (arrayPersonaggi == NULL)
    {
        printf("ERRORE NELL'ALLOCAZIONE DELL'ARRAY DI PERSONAGGI");
        exit(EXIT_FAILURE);
    }

    /*apertura file e controllo*/
    FILE* fp = fopen("personaggi.txt", "r");
    if (fp == NULL)
    {
        printf("ERRORE NELL'APERTURA DEL FILE personaggi.txt");
        exit(EXIT_FAILURE);
    }

    /*ripeto il ciclo per tutte le volte che ci sono 5 letture dal file*/
    do
    {
        nl = 0; //azzero ad ogni ciclo in contatore

        /*acquisisco ogni valore dell'array di bonus/malus e incremento il numero di letture*/
        for (int i = 0; i < ESAME; ++i)
        {
            nl += fscanf(fp, "%d ", &arrayPersonaggi[nPersonaggio].bonus_malus[i]);
        }

        nl += fscanf(fp, "%[^\n]s\n", arrayPersonaggi[nPersonaggio].nome);

        nPersonaggio++; //alla fine di ogni ciclo incremento il numero relativo al personaggio

    } while (nl==5 && nPersonaggio < MAX_GIOCATORI);

    //chiusura file
    fclose(fp);

    return arrayPersonaggi;
}

int* arrayPosizioniCasuali()
{

    srand(time(NULL));

    int* array = (int*) malloc(MAX_GIOCATORI * sizeof(int));
    if (array==NULL)
    {
        printf("ERRORE NELL'ALLOCAZIONE DELL'ARRAY DI NUMERI CASUALI");
        exit(EXIT_FAILURE);
    }

    int num=0;
    int aux=0;

    /*Popolo l'array con i numeri ordinati*/
    for (int i = 0; i < MAX_GIOCATORI; ++i)
    {
        array[i]=i;
    }

    /*Scambio i numeri tutti gli elementi dell'array con un elemento in un indice casuale dell' array*/
    for (int i = 0; i < MAX_GIOCATORI; ++i)
    {
        num = rand()%MAX_GIOCATORI; //numero generato casualmente

        /*scambio elementi*/
        aux = array[i];
        array[i] = array[num];
        array[num] = aux;
    }

    return array;
}

Giocatore* creaGiocatoreInCoda(Giocatore* giocatori, Giocatore aux)
{
    Giocatore* nuovo_giocatore = (Giocatore*) malloc(sizeof(Giocatore)); //viene allocata la memoria per il nuovo giocatore
    if (nuovo_giocatore == NULL)
    {
        printf("ERRORE NELL'ALLOCAZIONE DEL GIOCATORE");
        exit(EXIT_FAILURE);
    }

    /*il nuovo giocatore prende le informazioni necessarie, e dato che sarà l'ultimo il puntatore al successivo sarà NULL*/
    *nuovo_giocatore = aux;
    nuovo_giocatore->next=NULL;

    Giocatore* temp = giocatori; //creo la lista per scorrere i giocatori


    if (giocatori==NULL) //se la lista dei giocatori è vuota il nuovo giocatore sarà l'unico
        giocatori=nuovo_giocatore;
    else //se la lista dei giocatori non è vuota trovo l'ultimo giocatore per poter inserire il nuovo giocatore dopo di esso
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = nuovo_giocatore;
    }

    return giocatori;
}

Giocatore* creaGiocatori(Personaggio* personaggio)
{
    Giocatore* giocatori = NULL; //creo la lista di giocatori vuota

    int* arrayCas = arrayPosizioniCasuali(); //creo un array con numeri da 0 a 3 in posizione casuale

    Giocatore aux; //variabile ausiliaria che contiene le informazioni della stuttura Giocatore

    int ng=0; //variabile che contiene il numero di giocatori

    /*chiedo il numero di giocatori finchè viene inserito un valore non accettabile*/
    do {
        printf("INSERISCI IL NUMERO DI GIOCATORI (MAX 4): -->");
        scanf("%d", &ng);
    }while(ng<=0 || ng>4);

    /*aggiungo alla lista dei giocatori un nuovo giocatore con le informazioni necessarie, utilizzando aux per raccoglierle*/
    for (int i = 0; i < ng; ++i)
    {
        printf("Inserisci il nome utente del %d giocatore: -->",i+1);
        scanf(" %31s", aux.nome_utente);

        aux.personaggio=personaggio[arrayCas[i]]; //assegno il personaggio casualmente grazie al vettore arrayCas

        aux.punti_cfu=0;

        aux.carteCfu=NULL;

        aux.carteOstacolo=NULL;

        /*non acquisisco informazioni su carte cfu ed ostacolo perchè ad inizio gioco il giocatore non ne possiede*/

        giocatori= creaGiocatoreInCoda(giocatori, aux);

    }

    return giocatori;

}

void stampaGiocatore (Giocatore *giocatori)
{

        printf("\n\nGIOCATORE:  %s\n "
               "\npersonaggio ---> %s\n", giocatori->nome_utente, giocatori->personaggio.nome);

        printf("\nbonus/malus personaggio --->");
        for (int i = 0; i < ESAME; ++i)
        {
            switch (i)
            {

                case 1:
                    printf("\n\tSTUDIO ---> %d", giocatori->personaggio.bonus_malus[i]);
                    break;
                case 2:
                    printf("\n\tSOPRAVVIVENZA ---> %d", giocatori->personaggio.bonus_malus[i]);
                    break;
                case 3:
                    printf("\n\tSOCIALE ---> %d", giocatori->personaggio.bonus_malus[i]);
                    break;
                default:
                    printf("\n\tESAME ---> %d", giocatori->personaggio.bonus_malus[i]);
                    break;
            }
        }

        printf("\npunti cfu ---> %d\n", giocatori->punti_cfu);

        if (giocatori->carteCfu == NULL)
            printf("---> IL GIOCATORE NON HA CARTE CFU\n");
        else
            stampaMazzoCfu(giocatori->carteCfu);

        if (giocatori->carteOstacolo == NULL)
            printf("---> IL GIOCATORE NON HA CARTE OSTACOLO\n");
        else
            for (Carte_ostacolo* scorri = giocatori->carteOstacolo;  scorri!=NULL ; scorri=scorri->next)
            {
                stampaOstacolo(scorri);
            }



    /*non gestisco il caso in cui la lista sia vuota perchè non permetto l'inserimento di 0 giocatori*/

}

Giocatore* deallocaGiocatori(Giocatore* giocatori)
{
    //variabile che acquisisce il puntatore al nodo successivo
    Giocatore* prossimo_giocatore= NULL;

    //viene deallocata la memoria di ogni nodo della lista giocatori sino all'ultimo che punta a NULL
    while (giocatori != NULL)
    {
        prossimo_giocatore = giocatori->next;
        free(giocatori);
        giocatori = prossimo_giocatore;
    }

    return NULL;
}

int contaGiocatori(Giocatore* giocatori)
{
    int n_giocatori=0;
    do
    {
        n_giocatori++;
        giocatori= giocatori->next;
    } while (giocatori!=NULL);

    return n_giocatori;
}

int* contaMani(Giocatore* giocatori, int ng)
{
    int* array_mani = (int*) calloc(ng, sizeof(int)); //inizializzo l'array dei numeri di carte in mano
    if (array_mani==NULL)
    {
        printf("PROBLEMA DI MEMORIA");
        exit(EXIT_FAILURE);
    }

    int num_carte=0;

    /*ogni posizione dell'array conterrà il numero delle carte che ha in mano un giocatore*/
    for (int i=0;i<ng;++i)
    {
        num_carte = contaMazzoCfu(giocatori->carteCfu);

        array_mani[i] = num_carte;

        giocatori = giocatori->next;
    }


    return array_mani;
}

Carte_cfu* pescaCarteCfu(Carte_cfu* mazzo, Giocatore* giocatore)
{

    if (mazzo != NULL) //se il mazzo non è vuoto
    {
        giocatore->carteCfu = inserisciInCimaCfu(giocatore->carteCfu, *mazzo);  //viene creato un nodo nella lista di carte in mano con le informazioni della prima carta del mazzo cfu

        mazzo = eliminaCartaCfu(mazzo);
    }
    else //quando il mazzo è vuoto
        printf("IL MAZZO E' FINITO!!!!");


    return mazzo;
}

void stampaAvversari (Giocatore* giocatore, int ng, int i_gioc_attuale)
{
    /**/
    for (int i = 0; i < ng && giocatore!=NULL; ++i)
    {

        /*stampo le informazioni di tutti i giocatori apparte il giocatore che sta giocando*/
        if (i != i_gioc_attuale)
        {
            printf("\n\nGIOCATORE:  %s\n "
                   "\npersonaggio ---> %s\n", giocatore->nome_utente, giocatore->personaggio.nome);

            printf("\nbonus/malus personaggio --->");
            for (int j= 0; j < ESAME; ++j)
            {
                switch (j)
                {

                    case 1:
                        printf("\n\tSTUDIO ---> %d", giocatore->personaggio.bonus_malus[j]);
                        break;
                    case 2:
                        printf("\n\tSOPRAVVIVENZA ---> %d", giocatore->personaggio.bonus_malus[j]);
                        break;
                    case 3:
                        printf("\n\tSOCIALE ---> %d", giocatore->personaggio.bonus_malus[j]);
                        break;
                    default:
                        printf("\n\tESAME ---> %d", giocatore->personaggio.bonus_malus[j]);
                        break;
                }
            }

            printf("\n\npunti cfu ---> %d\n", giocatore->punti_cfu);

            if (giocatore->carteCfu == NULL)
                printf("\n---> IL GIOCATORE NON HA CARTE CFU\n");
            else
                printf("\ncarte cfu ---> %d\n", contaMazzoCfu(giocatore->carteCfu)); //stampo il numero delle carte cfu in mano al giocatore al posto di stampare le carte

            if (giocatore->carteOstacolo == NULL)
                printf("\n---> IL GIOCATORE NON HA CARTE OSTACOLO\n");
            else
                for (Carte_ostacolo* scorri = giocatore->carteOstacolo;  scorri!=NULL ; scorri=scorri->next)
                {
                stampaOstacolo(scorri);
                }
        }
        giocatore=giocatore->next; //scorro la lista di giocatori
    }
}

bool ripescaCfu(Giocatore* giocatore)
{
    Carte_cfu * temp = giocatore->carteCfu;
    int conta_Cfu=0; // contatore carte Cfu

    /*scorro le carte in mano, se tutte hanno nCfu 0 (quindi sono carte istantanee), il contatore rimarrà a 0*/
    while (temp!=NULL)
    {
        if (temp->nCfu!=0)
            conta_Cfu++;

        temp=temp->next;
    }

    /*viene restituito true se il giocatore non ha carte Cfu, e quindi dovrà scartare e ripescare tutta la mano*/
    if (conta_Cfu==0)
        return true;
    else
        return false;
}

void findVinTurno (Giocatore* giocatori, int* array_punti)
{

    int max=array_punti[0];

    bool* array_vin = (bool*) calloc(contaGiocatori(giocatori), sizeof (bool));

    for (int i = 0; i < contaGiocatori(giocatori); ++i)
    {
        if (array_punti[i]>=max)
            max=array_punti[i];
    }

    for (int i = 0; i < contaGiocatori(giocatori); ++i)
    {
        if(array_punti[i]==max)
            array_vin[i]=true;
    }


    for (int i = 0; giocatori!=NULL; ++i)
    {
        if (array_vin[i])
            giocatori->punti_cfu += max;

        giocatori=giocatori->next;
    }
    free(array_vin);
}

void spareggioPerdenti (Giocatore* giocatori, int* array_punti, Carte_ostacolo* ostacolo_turno, Carte_cfu* mazzo_scarti)
{
    int min = array_punti[0];

    Giocatore* spareggianti = NULL;


    for (int i = 0; i < contaGiocatori(giocatori); ++i)
    {
        if (array_punti[i]<min)
        {
            min= array_punti[i];
        } else if (array_punti[i]==min)
        {
            spareggianti= creaGiocatoreInCoda(spareggianti, *giocatori);
        }

        giocatori=giocatori->next;
    }

    int ng=contaGiocatori(spareggianti);

    int scegli_carta=0;

    if (ng>1)
    {
        for (int i = 0; i < ng; ++i)
        {
            if(contaMazzoCfu(spareggianti->carteCfu)==0)
            {
                printf("IL GIOCATORE NON HA CARTE IN MANO");
                exit(0);
            }

            printf("Scegli la carta da giocare:\n");
            stampaMazzoCfu(spareggianti->carteCfu);
            printf("\n--->");
            do
            {
                scanf("%d", &scegli_carta);
            } while (scegli_carta<1 || scegli_carta>5);

            mazzo_scarti = utilizzaCarta(mazzo_scarti, &spareggianti->carteCfu, scegli_carta);

            spareggianti=spareggianti->next;
        }
    }
}

