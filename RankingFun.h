#ifndef __RANKINGFUN_H__
#define __RANKINGFUN_H__
#include <string.h>
#include <stdlib.h>

#include "GameModeFun.h"
typedef struct { // 플레이어 정보 구조체 정의
    char name[50];
    int attempt;
} Player;

void rank_input_E(int attempt);
int read_attempt_E(Player players[], int max_players);
void rank_input_H(int attempt);
int read_attempt_H(Player players[], int max_players);
int compare_attempt(const void* a, const void* b);
void print_sorted_attempt(Player players[], int count);
void showRanking(int boardSize);

#endif