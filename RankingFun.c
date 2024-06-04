#include "RankingFun.h"
#include <stdlib.h>


// Easy모드의 랭킹표 입력 함수
void rank_input_E(int attempt) {
    char player_name[50];

    printf("Game Over. Enter name: ");
    scanf("%s", player_name);


    FILE* file = fopen("Rank_list_E.txt", "a"); // Rank_list_E.txt를 쓰기 전용으로 open
    if (file == NULL) {
        printf("File open error\n");
        return;
    }

    fprintf(file, "Player Name: %s\tattempt: %d\n", player_name, attempt); // Player 이름과 시도 횟수를 파일에 저장
    fclose(file); 
}

// Easy모드 파일을 읽어서 구조체 배열에 저장하는 함수
int read_attempt_E(Player players[], int max_players) {
    FILE* file = fopen("Rank_list_E.txt", "r");  // Rank_list_E.txt를 읽기 전용으로 open
    if (file == NULL) {
        printf("File open error\n");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "Player Name: %49s\tattempt: %d\n", players[count].name, &players[count].attempt) == 2) { // fscanf를 통해 값을 모두 읽어오면 값이 2개이므로 2를 반환
        count++; // 배열의 다음 인덱스로 넘어감
        if (count >= max_players) {
            break;
        }
    }

    fclose(file);
    return count;
}

// Hard모드의 랭킹표 입력 함수
void rank_input_H(int attempt) {
    char player_name[50];

    printf("Game Over! Enter name: ");
    scanf("%s", player_name);

    FILE* file = fopen("Rank_list_H.txt", "a"); // Rank_list_H.txt를 쓰기 전용으로 open
    if (file == NULL) {
        printf("File open error\n");
        return;
    }

    fprintf(file, "Player Name: %s\tattempt: %d\n", player_name, attempt); // Player 이름과 시도 횟수를 파일에 저장
    fclose(file);
}

// Hard모드 파일을 읽어서 구조체 배열에 저장하는 함수
int read_attempt_H(Player players[], int max_players) {
    FILE* file = fopen("Rank_list_H.txt", "r"); // Rank_list_H.txt를 읽기 전용으로 open
    if (file == NULL) {
        printf("File open error\n");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "Player Name: %49s\tattempt: %d\n", players[count].name, &players[count].attempt) == 2) { // fscanf를 통해 값을 모두 읽어오면 값이 2개이므로 2를 반환
        count++; // 배열의 다음 인덱스로 넘어감
        if (count >= max_players) {
            break;
        }
    }

    fclose(file);
    return count;
}

// 오름차순으로 정렬하기 위한 비교 함수
int compare_attempt(const void* a, const void* b) {
    Player* playerA = (Player*)a; // 첫 번째 매개변수를 Player 구조체 포인터로 형 변환
    Player* playerB = (Player*)b; // 두 번째 매개변수를 Player 구조체 포인터로 형 변환
    return playerA->attempt - playerB->attempt; // 두 Player의 시도 횟수 차이를 반환
}

// 랭킹표 출력 함수
void print_sorted_attempt(Player players[], int count) {
    int i;
    printf("\n======= Sorted attempt =======\n");
    for (i = 0; i < count; i++) {
        printf("%d Player Name: %s\tattempt: %d\n", i + 1, players[i].name, players[i].attempt);
    }
}

// 랭킹을 보여주기 위한 함수
void showRanking(int boardSize) {
    const int MAX_PLAYERS = 100;
    Player players[MAX_PLAYERS];
    int player_count;

    if (boardSize == 5) { // 보드 사이즈에 따라 난이도에 맞는 파일을 열어 랭킹표 출력
        player_count = read_attempt_E(players, MAX_PLAYERS); // Easy모드 랭킹표
    } else {
        player_count = read_attempt_H(players, MAX_PLAYERS); // Hard모드 랭킹표
    }
    
    qsort(players, player_count, sizeof(Player), compare_attempt); // players 배열을 compare_attempt 비교 함수를 사용하여 오름차순으로 정렬
    print_sorted_attempt(players, player_count); // 정렬된 랭킹표를 출력
}