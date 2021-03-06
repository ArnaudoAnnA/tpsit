#include <stdio.h>
#include <stdlib.h>
#include "sys/types.h"

#include "costants.h"

int main(int argc, char** argv)
{
    if(argc!=4)
    {
        printf("\n  USAGE: %s n_ordine n_tentativi", argv[0]);
        return -1;
    }

    /* getting the parameters*/
    char* playerName = argv[1];
    int n_ordine = atoi(argv[2]);
    int n_tentativi = atoi(argv[3]);


    /*I register the new player in the table (the access to the table is in mutual exclusion)*/
    addPlayer(playerName, getpid());
    printf("\n  il giocatore %s e' stato creato", playerName);

    /*getting the shm that contains the field*/
    int shm_id;
    int** shm_field_ind = (int**) shm_find(IPC_CAMPO_KEY, &shm_id);

    /*getting the mutex that control access to the field*/
    int mutex_field_id = mutex_find(IPC_CAMPO_KEY);

    /*I cycle many times as the number of possibility of the player
        every cycle I get a random cell of the two dimension array and
        check what is inside
    */
    srand(time(NULL));
    int i, rRandom, cRandom, cellValue;
    for(i = 0; i<n_tentativi && cellValue==VUOTA; i++)
    {
        rRandom = rand()%n_ordine-1;
        cRandom = rand()%n_ordine-1;

        /*I get to the field in mutual exclusion*/
        mutex_lock(mutex_field_id);
        cellValue = shm_field_ind[rRandom][cRandom];

        printf("\n  %s: sto' eseguendo il tentativo %d di %d\n  casella: [%d] [%d]", playerName, i, n_tentativi, rRandom, cRandom);

        mutex_unlock(mutex_field_id);
    }

    return getpid()*10+cellValue;
}
