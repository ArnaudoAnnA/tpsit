#include <stdio.h>
#include <stdlib.h>
#include "costants.h"

#include <string.h>

/*prototypes*/
char* getPlayerNameFromPid(int processPid);


int main(int argc, char** argv)
{
    if(argc!=5)
    {
        printf("\n  There was an error in passing parameters");
        printf("\n  USAGE: %s n_ordine n_tesori n_bombe n_prigionieri\n  ", argv[0]);
        return -1;
    }

    /*I get the arguments*/
    int n_ordine = atoi(argv[0]);
    int n_tesori = atoi(argv[1]);
    int n_bombe = atoi(argv[2]);
    int n_prigionieri = atoi(argv[3]);

    /*I create the shm that contains the field*/
    printf("\n  Creazione campo...");
    int** campo  = creaCampo(n_ordine, n_tesori, n_bombe, n_prigionieri);
    int mutex_field = mutex_create(IPC_CAMPO_KEY, 0);

    /*I create the shm that lead the list of players*/
    PlayerLine* table = createTable();

    /*now I can start the simulation*/
    char* command = " ";
    mutex_unlock(mutex_field);
    printf("\n  Il campo e' stato creato\n\n  In attesa di giocatori...\n  ");

    /*I create n_prigionieri players*/
    int i, pid;
    for(i=0; i<n_prigionieri && pid=fork(); i++)
    {
        if(pid==0)
        {
            /*if I'm in the son*/

            /* I take in input the number of possibility of the player*/
            int n_tentativi;
            printf("\n  Inserire la quantita' di tentativi per cui ha scommesso il giocatore%d:  ", i);
            scanf("%d", n_tentativi);

            /*I get the player to the table of players*/
            char* playerName;
            sprintf(playerName, "%d", i);
            playerName = strcat("giocatore", playerName);

            /* I prepare the vector of parameters to pass to the execvp*/
            char** parameters;
            parameters[0] = "giocatore";
            sprintf(parameters[1], "%d", n_ordine);
            sprintf(parameters[2], "%d", n_tentativi);
            parameters[3] = NULL;

            execvp("giocatore", parameters);
            printf("\n  errore: impossibile avviare giocatore%d", i);
            return -1;
        }
    }


    /*I cycle while there are still players in the player table*/
    while(getNplayers(table)!=0)
    {
        int retPlayer;
        wait(&retPlayer); /*I wait for one process die*/

        /*WHEN A PROCESS IS DIED*/

        /*the value returned by a player process is composed by two information:
            - the first number from right is due to how the process finished
            - the other numbers form the pid of the process
            so now I have to separate these two information
        */

        int returnValue = retPlayer % 10;
        int processPid = retPlayer / 10;

        /*I get the player name from his pid using the pid/name table*/
        char* playerName = getPlayerName(processPid);

        switch(returnValue)
        {
            case BOMBA:
                printf("\n  IL GIOCATORE DI NOME %s HA PERSO: IL SUO PRIGIONIERO E' FINITO SU UNA MINA\n", playerName);
            break;

            case VUOTA:
                printf("\n  IL GIOCATORE DI NOME %s HA FINITO I SUOI TENTATIVI SENZA TROVARE NULLA\n", playerName);
            break;

            case TESORO:
                printf("\n  IL GIOCATORE DI NOME %s HA VINTO: IL SUO PROGIONIERO HA TROVATO UN TESORO\n", playerName);
            break;
        }

        removePlayerFromTable(processPid);
    }
}

    freeTable();
    freeCampo(campo, n_ordine);

    return 0;
}


