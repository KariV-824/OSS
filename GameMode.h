#ifndef __GAMEMODE_H__
#define __GAMEMODE_H__

#include <stdio.h>
#include <time.h>
#include <stdio.h>

#include "PlaceShipFun.h"
#include "RankingFun.h"
#include "UiFun.h"

#define EASY_BOARD_SIZE 5   
#define EASY_SHIPS_COUNT 4 
#define HARD_BOARD_SIZE 6
#define HARD_SHIPS_COUNT 7


extern int attempts;
extern int boardSize;
extern int shipsCount;
extern int remainships1;
extern int remainships2;
extern int findshipcnt1;
extern int findshipcnt2;


void selectDifficulty(int* boardSize, int* shipsCount);
void singlePlay(int boardSize, int shipsCount);
void multiPlay(int boardSize, int shipsCount);
void gameMode();


#endif