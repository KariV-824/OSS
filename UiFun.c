#include "UiFun.h"

// 게임 이름을 출력하는 함수
void printHeadUI() {
    printf("\033[0;37m");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("@      BATTLESHIP GAME!    @\n");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
}

// 싱글플레이 모드에서 시도 횟수, 남은 배 개수, 찾은 배 개수를 출력하는 함수
void printSingleTailUI(int attempts, int remain, int find) { 
    printf("\033[0;37m");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("               Attempts : %d               \n", attempts);
    printf("                Remain : %d                \n", remain);
    printf("                 Find :  %d                \n", find);
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
}

// 멀티플레이 모드에서 Player별 시도 횟수, 남은 배 개수, 찾은 배 개수를 출력하는 함수
void printMultiTailUI(int attempts1, int attempts2, int remain1, int remain2, int find1, int find2) {
    printf("\033[0;37m");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("   P1 Attempts : %d    P2 Attempts : %d   \n", attempts1, attempts2);
    printf("    P1 Remain : %d       P2 Remain : %d    \n", remain1, remain2);
    printf("     P1 Find : %d         P2 Find : %d     \n", find1, find2);
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
}

