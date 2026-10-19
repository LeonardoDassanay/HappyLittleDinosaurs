#include <stdio.h>
#include <stdlib.h>
#include "giocatori.h"


int main()
{
    setbuf(stdout, 0);

    srand(time(NULL));



    Carte_cfu* mazzo_cfu= creaMazzoCfu(); //creo il mazzo delle carte cfu

    Carte_ostacolo* mazzo_ostacoli= creaMazzoOstacoli(); //creo il mazzo delle carte ostacolo

    Personaggio* personaggi = caricaPersonaggi(); //carico i personaggi dal file

    Giocatore* giocatore = creaGiocatori(personaggi); //creo i giocatori chiedendo i nomi all'utente



    Carte_cfu* mazzo_scarti = NULL;



    mescolaMazzoCfu(mazzo_cfu); //mischio il mazzo delle carte cfu

    mescolaMazzoOstacoli(mazzo_ostacoli); //mischio il mazzo delle carte ostacolo

    int n_giocatori = contaGiocatori(giocatore); //conto i giocatori



    int* mano = contaMani(giocatore, n_giocatori); //conto il numero delle carte in mano di ogni giocatore





    int count_turno=1; //inizio a contare i turni di gioco


    bool vittoria=false;




    //ciclo del turno
    while (!vittoria && n_giocatori>1)
    {
        /*faccio pescare a ogni giocatore il numero di carte necessarie per averne 5 in mano*/
        Giocatore* scorri_giocatori =giocatore;
        free(mano);
        mano = contaMani(giocatore, n_giocatori);
        int count_gioc=0;
        for (int i = 0; i < n_giocatori; ++i)
        {
            for (int j = mano[count_gioc]; j < CARTE_IN_MANO && mazzo_cfu != NULL; ++j)
            {
                mazzo_cfu = pescaCarteCfu(mazzo_cfu, scorri_giocatori);
            }

            /*finché il giocatore ha solo carte istantanee in mano*/
            while (scorri_giocatori->carteCfu != NULL && ripescaCfu(scorri_giocatori) && mazzo_cfu != NULL)
            {
                printf("carte ripescate");
                //mando nel mazzo degli scarti tutte le carte che ha in mano
                while (scorri_giocatori->carteCfu != NULL)
                {
                    //viene scartata sempre l'ultima carta disponibile
                    mazzo_scarti=utilizzaCarta(mazzo_scarti, &scorri_giocatori->carteCfu, contaMazzoCfu(scorri_giocatori->carteCfu));
                }

                //e faccio ripescare le carte
                for (int j = 0; j < CARTE_IN_MANO && mazzo_cfu != NULL; ++j)
                {
                    mazzo_cfu = pescaCarteCfu(mazzo_cfu, scorri_giocatori);
                }
            }




            scorri_giocatori=scorri_giocatori->next;
            count_gioc++;
        }


        //------------------------------------------------------------------------------------------------------------------------------


        printf("\n\n========== TURNO %d =============\n", count_turno); //inizia il turno di gioco


        /*viene scelta la carta ostacolo del turno*/
        Carte_ostacolo* carta_ostacolo_gioco = (Carte_ostacolo*) malloc(sizeof(Carte_ostacolo));
        if (mazzo_ostacoli == NULL) {
            printf("Mazzo ostacoli esaurito: fine partita.\n");
            free(carta_ostacolo_gioco);
            break;
        }
        mazzo_ostacoli = pescaOstacolo(mazzo_ostacoli, carta_ostacolo_gioco);
        printf("CARTA OSTACOLO DI QUESTO TURNO\n"
               "              |\n"
               "              |\n"
               "              v\n\n");
        stampaOstacolo(carta_ostacolo_gioco);





        /*pulizia terminale*/
        printf("\n\nPremi INVIO per andare avanti");
        getchar();
        getchar();
        /* Pulizia schermo rimossa: comando specifico di Windows. */






        int* array_punti = (int*) calloc(n_giocatori, sizeof(int));


        Giocatore* giocatore_temp = giocatore;

        for (int i = 0; i < contaGiocatori(giocatore) && giocatore_temp!=NULL; ++i)
        {
            /*condizioni per la fine della partita*/



            /*viene chiesto ad ogni giocatore quale scelta eseguire*/
            int scelta = 0;
            printf("\n\nGIOCA %s\n",giocatore_temp->nome_utente);

            int scegli_carta = 0;
            /*il giocatore finisce di giocare dopo aver scelto una carta*/
            do
            {
                do {
                    printf("\n\nINFORMAZIONI GIOCATORE ATTUALE\n\n"
                                  "===================================\n\n");
                    stampaGiocatore(giocatore_temp);
                    printf("\n\n=================================="
                           "\n\nINSERISCI (DEVI GIOCARE UNA CARTA PER FINIRE IL TURNO)\n"
                           "[0] PER USCIRE DALLA PARTITA\n"
                           "[1] PER SCEGLIERE LA CARTA DA GIOCARE\n"
                           "[2] PER VISUALIZZARE LO STATO DEGLI ALTRI GIOCATORI\n"
                           "--> ");
                    scanf("%d", &scelta);
                } while (scelta < 0 || scelta > 2);



                /*pulizia terminale*/
                /* Pulizia schermo rimossa: comando specifico di Windows. */


                scegli_carta = 0;



                /*viene eseguita la scelta del giocatore*/
                switch (scelta) {
                    case 1:
                        if (contaMazzoCfu(giocatore_temp->carteCfu) == 0)
                        {
                            printf("IL GIOCATORE NON HA CARTE IN MANO");
                            exit(0);
                        }

                        printf("[0] per uscire dalla scelta delle carte\n"
                                      "Scegli la carta da giocare:\n");
                        stampaMazzoCfu(giocatore_temp->carteCfu);
                        printf("\n--->");

                        /*il giocatore sceglie la carta*/
                        do
                        {
                            scanf("%d", &scegli_carta);
                        } while (scegli_carta < 0 || scegli_carta > contaMazzoCfu(giocatore_temp->carteCfu));

                        if (scegli_carta==0)
                            break;

                        mazzo_scarti = utilizzaCarta(mazzo_scarti, &giocatore_temp->carteCfu, scegli_carta);

                        printf("\n\ncarte rimaste in mano -- > %d\n\n", contaMazzoCfu(giocatore_temp->carteCfu));
                        stampaMazzoCfu(giocatore_temp->carteCfu);

                        /*i punti di ogni giocatore sono dalla somma dei cfu della carta giocata e i bonus/malus derivati dal tipo di ostacolo in gioco*/
                        array_punti[i] = mazzo_scarti->nCfu +
                                         giocatore_temp->personaggio.bonus_malus[carta_ostacolo_gioco->tipoOstacolo - 1];

                        break;
                    case 2:
                        /*il giocatore visualizza lo stato degli avversari*/
                        stampaAvversari(giocatore, n_giocatori, i);

                        printf("\n\n\nPremi INVIO per andare avanti");
                        getchar();
                        getchar();
                        /* Pulizia schermo rimossa: comando specifico di Windows. */

                        break;
                    default:
                        /*fine gioco*/
                        printf("\n"
                               "   _____ _____ ____   _____ ____    _______ ______ _____  __  __ _____ _   _       _______ ____   \n"
                               "  / ____|_   _/ __ \\ / ____/ __ \\  |__   __|  ____|  __ \\|  \\/  |_   _| \\ | |   /\\|__   __/ __ \\  \n"
                               " | |  __  | || |  | | |   | |  | |    | |  | |__  | |__) | \\  / | | | |  \\| |  /  \\  | | | |  | | \n"
                               " | | |_ | | || |  | | |   | |  | |    | |  |  __| |  _  /| |\\/| | | | | . ` | / /\\ \\ | | | |  | | \n"
                               " | |__| |_| || |__| | |___| |__| |    | |  | |____| | \\ \\| |  | |_| |_| |\\  |/ ____ \\| | | |__| | \n"
                               "  \\_____|_____\\____/ \\_____\\____/     |_|  |______|_|  \\_\\_|  |_|_____|_| \\_/_/    \\_\\_|  \\____/  \n"
                               "                                                                                                  \n");

                        printf("\n\n\nPremi INVIO per uscire dalla partita");
                        getchar();
                        getchar();
                        exit(0);
                        break;



                }
            } while (scelta!=1 || scegli_carta==0);

            giocatore_temp->punti_cfu += contaMazzoOstacoli(giocatore_temp->carteOstacolo);

            giocatore_temp=giocatore_temp->next;


            /*pulizia terminale*/
            if (giocatore_temp!=NULL)
                printf("\n\nPremi INVIO per passare al giocatore successivo (%s)", giocatore_temp->nome_utente);

            else
                printf("\n\nPremi INVIO per passare al turno successivo");

            getchar();
            getchar();
            /* Pulizia schermo rimossa: comando specifico di Windows. */



        } //fine ciclo giocatori

        findVinTurno(giocatore, array_punti);
        free(array_punti);
        free(carta_ostacolo_gioco);
        Giocatore *controllo_vittoria = giocatore;
        while (controllo_vittoria != NULL) {
            if (controllo_vittoria->punti_cfu >= 60) {
                printf("\nVINCITORE: %s (%d CFU)\n", controllo_vittoria->nome_utente, controllo_vittoria->punti_cfu);
                vittoria = true;
                break;
            }
            controllo_vittoria = controllo_vittoria->next;
        }



        /*trovaPerdente*/

        /*eliminaGiocatori*/

        count_turno++; //si passa al turno successivo

    }




    return 0;
}
