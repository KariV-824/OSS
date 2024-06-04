#include "RankingFun.h"
#include <stdlib.h>

void rank_input_E(int attempt) {
    char player_name[50];

    printf("Game Over. Enter name: ");
    scanf("%s", player_name);


    FILE* file = fopen("Rank_list_E.txt", "a");
    if (file == NULL) {
        printf("File open error\n");
        return;
    }


    fprintf(file, "Player Name: %s\tattempt: %d\n", player_name, attempt);
    fclose(file);
}


int read_attempt_E(Player players[], int max_players) {
    FILE* file = fopen("Rank_list_E.txt", "r");
    if (file == NULL) {
        printf("File open error\n");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "Player Name: %49s\tattempt: %d\n", players[count].name, &players[count].attempt) == 2) {
        count++;
        if (count >= max_players) {
            break;
        }
    }

    fclose(file);
    return count;
}


void rank_input_H(int attempt) {
    char player_name[50];

    printf("Game Over! Enter name: ");
    scanf("%s", player_name);

    FILE* file = fopen("Rank_list_H.txt", "a");
    if (file == NULL) {
        printf("File open error\n");
        return;
    }


    fprintf(file, "Player Name: %s\tattempt: %d\n", player_name, attempt);
    fclose(file);
}


int read_attempt_H(Player players[], int max_players) {
    FILE* file = fopen("Rank_list_H.txt", "r");
    if (file == NULL) {
        printf("File open error\n");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "Player Name: %49s\tattempt: %d\n", players[count].name, &players[count].attempt) == 2) {
        count++;
        if (count >= max_players) {
            break;
        }
    }

    fclose(file);
    return count;
}


int compare_attempt(const void* a, const void* b) {
    Player* playerA = (Player*)a;
    Player* playerB = (Player*)b;
    return playerA->attempt - playerB->attempt; 
}


void print_sorted_attempt(Player players[], int count) {
    int i;
    printf("\n======= Sorted attempt =======\n");
    for (i = 0; i < count; i++) {
        printf("%d Player Name: %s\tattempt: %d\n", i + 1, players[i].name, players[i].attempt);
    }
}

void showRanking(int boardSize) {
    const int MAX_PLAYERS = 100;
    Player players[MAX_PLAYERS];
    int player_count;

    if (boardSize == 5) {
        player_count = read_attempt_E(players, MAX_PLAYERS);
    } else {
        player_count = read_attempt_H(players, MAX_PLAYERS);
    }
    
    qsort(players, player_count, sizeof(Player), compare_attempt); 
    print_sorted_attempt(players, player_count); 
}