#ifndef PLAYERSNAMETABLELIB_H_INCLUDED
#define PLAYERSNAMETABLELIB_H_INCLUDED

#include "costants.h"

/*typedef*/
typedef struct l_PlayerLine
{
    char* playerName;
    int processPid;
}PlayerLine;

/*prototypes*/
PlayerLine* createTable();
int getPidAt(int n);
char* getNameAt(int n);
void addPlayer(char* playerName, int processPid);
PlayerLine* getTable();
char* getPlayerName(int processPid);
int getNplayers(PlayerLine* table);
void freeTable();
void removePlayerFromTable(int processPid);


/*methods*/
PlayerLine* createTable()
{
    int len = sizeof(PlayerLine*)*MAX_PLAYERS;
    int shm_id;
    PlayerLine* table = (PlayerLine*) shm_create(IPC_PLAYERSNAMETABLE_KEY, len, &shm_id);
    int mutex_id = mutex_create(IPC_PLAYERSNAMETABLE_KEY, 1);

    return table;
}

int getPidAt(int n)
{
    PlayerLine* table = getTable();
    PlayerLine* player = table+n;
    return player->processPid;
}

char* getNameAt(int n)
{
    PlayerLine* table = getTable();
    PlayerLine* player = table+n;
    return player->playerName;
}

void addPlayer(char* playerName, int processPid)
{
    PlayerLine* table = getTable();

    PlayerLine* newPlayerLine =(PlayerLine*) malloc(sizeof(PlayerLine));
    newPlayerLine->playerName = playerName;
    newPlayerLine->processPid = processPid;
    int newPosition = getNplayers(table);

    *(table+newPosition) = *newPlayerLine;
}

PlayerLine* getTable()
{
    int shm_id;
    PlayerLine* table = (PlayerLine*) shm_find(IPC_PLAYERSNAMETABLE_KEY, &shm_id);

    return table;
}

char* getPlayerName(int processPid)
{
    int n = getNplayers(getTable());
    int i;
    char* ret = NULL;

    for(i = 0; i<n && ret==NULL; i++)
    {
        if(getPidAt(i) == processPid)
        {
            ret = getNameAt(i);
        }
    }

    return ret;
}

int getNplayers(PlayerLine* table)
{
    int ret;
    for(ret = 0;(table+ret)!=NULL; ret++) {}

    return ret;
}

void removePlayerFromTable(int processPid)
{
    PlayerLine* table = getTable();
    int n = getNplayers(table);
    int i;

    for(i = 0; i<n && (table+i)!=NULL; i++)
    {
        if(getPidAt(i) == processPid)
        {
            free((table+i)->playerName);
            free(table+i);
        }
    }

    for(i=i+1; i<n;i++)
    {
        table[i-1] = table[i];
    }

    void* endTable = table+n;
    endTable = NULL;
}


void freeTable()
{
    PlayerLine* table = getTable();
    int n = getNplayers(table);
    int i;

    for(i = 0; i<n; i++)
    {
        free((table+i)->playerName);
        free(table+i);
    }

    free(table);
}



#endif // PLAYERSNAMETABLELIB_H_INCLUDED
