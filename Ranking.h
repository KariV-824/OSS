#ifndef __RANKING_H__
#define __RANKING_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 플레이어 정보 구조체 정의
typedef struct {
    char name[50];
    int score;
} Player;

// 플레이어 정보 입력 함수
void rank_input(int score);
// 플레이어 정보 파일에서 읽기
int read_scores(Player players[], int max_players);
// 점수를 기준으로 내림차순 정렬하는 함수
int compare_scores(const void* a, const void* b);

// 정렬된 결과 출력 함수
void print_sorted_scores(Player players[], int count);

void showRanking();
#endif