#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include "costants.h"

int main(int argc, char** argv)
{
    PlayerLine* table = createTable();

    addPlayer("Anna", getpid());
    addPlayer("Giacomo", getpid()+1);

    char* prova = getPlayerName(getpid());

    int n = getNplayers(table);

    removePlayerFromTable(getpid());

    n = getNplayers(table);

    freeTable();

}
