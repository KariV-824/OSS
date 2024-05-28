#ifndef __FUNCTION_H__
#define __FUNCTION_H__
#include "SinglePlay.h"
#include "MultiPlay.h"



//싱글 플레이와 멀티 플레이를 선택하는 함수
void gamemode();
 
// 보드를 빈 칸으로 초기화하는 함수
void initializeBoard(char board[][BOARD_SIZE]);

// 전함 위치를 감추고 보드를 출력하는 함수
void printBoard(char board[][BOARD_SIZE]);
// 전함을 보드에 배치하는 함수
void placeShips(char board[][BOARD_SIZE]);

// 유효한 추측인지 확인하는 함수
int isValidGuess(int row, int col);
// 모든 전함이 격추되었는지 확인하는 함수
int hasWon(char board[][BOARD_SIZE]);

#endif