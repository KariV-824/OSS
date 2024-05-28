#include "Ranking.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// 플레이어 정보 입력 함수
void rank_input(int score) {
    char player_name[50];

    printf("Game Over Enter name: ");
    scanf("%s", player_name);

    // 메모장 열기
    FILE* file = fopen("Rank_list.txt", "a");
    if (file == NULL) {
        printf("File open error\n");
        return;
    }

    // 이름과 점수 파일에 입력
    fprintf(file, "Player Name: %s\tScore: %d\n", player_name, score);

    fclose(file);
}

// 플레이어 정보 파일에서 읽기
int read_scores(Player players[], int max_players) {
    FILE* file = fopen("Rank_list.txt", "r");
    if (file == NULL) {
        printf("File open error\n");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "Player Name: %49s\tScore: %d\n", players[count].name, &players[count].score) == 2) {
        count++;
        if (count >= max_players) {
            break;
        }
    }

    fclose(file);
    return count;
}

// 점수를 기준으로 내림차순 정렬하는 함수
int compare_scores(const void* a, const void* b) {
    Player* playerA = (Player*)a;
    Player* playerB = (Player*)b;
    return playerA->score - playerB->score; // 내림차순 정렬
}

// 정렬된 결과 출력 함수
void print_sorted_scores(Player players[], int count) {
    printf("\n=== Sorted Scores ===\n");
    for (int i = 0; i < count; i++) {
        printf("%d Player Name: %s\tScore: %d\n",i+1, players[i].name, players[i].score);
    }
}

void showRanking() {
    // 입력받기 (필요시 주석 해제)
    // rank_input();

    // 최대 플레이어 수 정의
    const int MAX_PLAYERS = 100;
    Player players[MAX_PLAYERS];

    // 파일에서 플레이어 정보 읽기
    int player_count = read_scores(players, MAX_PLAYERS);

    // 점수 기준으로 정렬
    qsort(players, player_count, sizeof(Player), compare_scores);

    // 정렬된 결과 출력
    print_sorted_scores(players, player_count);

}