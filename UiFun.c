#include "UiFun.h"

void printHeadUI() {
    printf("\033[0;37m");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("@     BATTLESHIP GAME!     @\n");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
}

void printTailUI(int attempts, int remain, int find) {
    printf("\033[0;37m");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("@              Attempts : %d              @\n", attempts);
    printf("@               Remain : %d               @\n", remain);
    printf("@                Find :  %d               @\n", find);
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
}

void printMultiUI(int attempts, int remain1, int remain2, int find1, int find2) {
    printf("\033[0;37m");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("@              Attempts : %d              @\n", attempts);
    printf("@   P1 Remain : %d       P2 Remain : %d   @\n", remain1, remain2);
    printf("@    P1 Find : %d         P2 Find : %d    @\n", find1, find2);
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
}