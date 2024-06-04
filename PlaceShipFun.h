#ifndef __PLACESHIPFUN_H__
#define __PLACESHIPFUN_H__
#include "GameMode.h"


int boardSize;
int shipsCount;
int remainShips1;
int remainShips2;
int findShipcnt1;
int findShipcnt2;

void placeShips(char board[][boardSize], int boardSize, int shipsCount);
void placeShipsRandom(char board[][boardSize], int boardSize, int shipsCount);
void initializeBoard(char board[][boardSize], int boardSize);
void printBoard(char board[][boardSize], int boardSize);
void processGuess(char board[][boardSize], int boardSize, int player);
int isValidGuess(int row, int col, int boardSize);
int hasWon(char board[][boardSize], int boardSize);

#endif


