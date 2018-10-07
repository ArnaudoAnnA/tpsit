#ifndef COSTANTS_H_INCLUDED
#define COSTANTS_H_INCLUDED

#define IPC_CAMPO_KEY 1
#define IPC_NGIOCATORI_KEY 2
#define IPC_PLAYERSNAMETABLE_KEY 3

#define VUOTA 0
#define BOMBA 1
#define TESORO 2
#define MAX_PLAYERS 50

#define END_GAME "fine gioco"

#include "../lib/mutex.h"
#include "../lib/shm.h"
#include "campoLib.h"
#include "playersNameTableLib.h"

#endif // COSTANTS_H_INCLUDED
