#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <mmsystem.h>
#include <string.h>

#include <time.h>
#pragma comment (lib, "winmm.lib")

#define EASY_BOARD_SIZE 5   
#define EASY_SHIPS_COUNT 4 

#define HARD_BOARD_SIZE 6
#define HARD_SHIPS_COUNT 7

#define _C 1046.502
#define _D 1108.731
#define _E 1318.510
#define _F 1396.913
#define _G 1567.982
#define _A 1760.000
#define _B 1975.533

// 플레이어 정보 구조체 정의
typedef struct {
    char name[50];
    int attempt;
} Player;

int boardSize = 0;
int shipsCount = 0;
int attempts = 0;
int remainShips1 = 0;
int remainShips2 = 0;
int findShipcnt1 = 0;
int findShipcnt2 = 0;

void printHeadUI();
void printTailUI(int attempts, int remain, int find);
void printMultiUI(int attempts, int remain1, int remain2, int find1, int find2);
void processGuess(char board[][boardSize], int boardSize, int player);
void selectDifficulty(int* boardSize, int* shipsCount);
void singlePlay(int boardSize, int shipsCount);
void multiPlay(int boardSize, int shipsCount);
void gameMode();
void initializeBoard(char board[][boardSize], int boardSize);
void printBoard(char board[][boardSize], int boardSize);
void placeShips(char board[][boardSize], int boardSize, int shipsCount);
void placeShipsRandom(char board[][boardSize], int boardSize, int shipsCount);
int isValidGuess(int row, int col, int boardSize);
int hasWon(char board[][boardSize], int boardSize);
void rank_input_E(int attempt);
int read_attempt_E(Player players[], int max_players);
void rank_input_H(int attempt);
int read_attempt_H(Player players[], int max_players);
int compare_attempt(const void* a, const void* b);
void print_sorted_attempt(Player players[], int count);
void showRanking(int boardSize);

int main() {
    gameMode();
    return 0;
}

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

void processGuess(char board[][boardSize], int boardSize, int player) {
    int guessRow, guessCol;
    
    printBoard(board, boardSize);
    
    printf("Player %d, enter your guess (row column): ", player);
    while (scanf("%d %d", &guessRow, &guessCol) != 2 || !isValidGuess(guessRow, guessCol, boardSize) || getchar() != '\n') {
        while (getchar() != '\n'); 
        printf("Invalid guess! Please enter valid coordinates\n");
        printf("Player %d, enter your guess (row column): ", player);
    }

    char cell = board[guessRow][guessCol];
    if (cell == 'S') {
        printf("Player %d hit a ship!\n", player);
        Beep(_B,100);
        board[guessRow][guessCol] = 'H';
    } else if (cell == 'H') {
        printf("Player %d, congratulations! You destroyed a ship!\n", player);
        if (player == 0) {
            findShipcnt1++;
            remainShips1--;
        } else if(player == 1) {
            findShipcnt1++;
            remainShips2--;
        } else {
            findShipcnt2++;
            remainShips1--;
        }
        Beep(_B,100);
        board[guessRow][guessCol] = 'O';
    } else if (cell == '~') {
        printf("Player %d missed! Try again\n", player);
        Beep(_F,100);
        board[guessRow][guessCol] = 'X';
    } else {
        printf("Player %d, you've already guessed this location. Try again\n", player);
    }
}

void selectDifficulty(int *boardSize, int *shipsCount) {
    int difficulty;

    printf("Select Difficulty\n");
    printf("1: Easy  2: Hard  -->  ");
    scanf("%d", &difficulty);
    while (getchar() != '\n');

    if (difficulty == 1) {
        *boardSize = EASY_BOARD_SIZE;
        *shipsCount = EASY_SHIPS_COUNT;
        remainShips1 = EASY_SHIPS_COUNT;
        remainShips2 = EASY_SHIPS_COUNT;
    } else if (difficulty == 2) {
        *boardSize = HARD_BOARD_SIZE;
        *shipsCount = HARD_SHIPS_COUNT;
        remainShips1 = HARD_SHIPS_COUNT;
        remainShips2 = HARD_SHIPS_COUNT;
    } else {
        printf("Invalid input value!\n");
        selectDifficulty(boardSize, shipsCount);

    }
}


void singlePlay(int boardSize, int shipsCount) {
    char board[boardSize][boardSize];
    int guessRow, guessCol;
    int a = 0;
     time_t start, end; // 시간 측정을 위한 변수
    // 게임 보드를 초기화하고 전함을 배치함
    initializeBoard(board, boardSize); // 초기화
    placeShipsRandom(board, boardSize, shipsCount); // 랜덤 배치
    printHeadUI();

    time(&start); // 게임 시작 시간 기록
    while (!hasWon(board, boardSize)) {
        processGuess(board, boardSize, 1);
        attempts++;
        printTailUI(attempts, remainShips1, findShipcnt1);
    }

    time(&end); // 게임 종료 시간 기록
    int time_taken = difftime(end, start); // 걸린 시간 계산
    // 게임 종료, 최종 보드 상태와 시도 횟수 출력
    printf("\n");
    printBoard(board, boardSize);
    printf("Congratulations! All battleships have been shot down. Attempts: %d\n", attempts);
    printf("Time taken: %d seconds\n", time_taken); // 걸린 시간 출력부분
    
    if (boardSize == 5) {
        rank_input_E(attempts);
    } else {
        rank_input_H(attempts);
    }

    printf("Would you like to check the ranking table?(1: Yes  2: No)  -->  ");
    scanf("%d", &a);
    if (a == 1) {
        showRanking(boardSize);
    } else if ( a == 2) {

        return;
    }
}


void multiPlay(int boardSize, int shipsCount) {
    char board1[boardSize][boardSize]; 
    char board2[boardSize][boardSize]; 
    int guessRow1, guessCol1;
    int guessRow2, guessCol2;
    int mode1, mode2;
    // 플레이어 1의 배치 모드 선택
    printf("Player 1: Choose ship placement mode(1: Manual  2: Random)  -->  ");
    scanf("%d", &mode1);
    initializeBoard(board1, boardSize);
    // 입력 1이면 수동 배치, 입력 2면 자동랜덤배치, 나머지는 예외처리
    if (mode1 == 1) {
        placeShips(board1, boardSize, shipsCount);
    } else if (mode1 == 2) {
        placeShipsRandom(board1, boardSize, shipsCount);
    } else {
        printf("Invalid input value!\n");
        multiPlay(boardSize, shipsCount);
    }

    // 플레이어 2의 배치 모드 선택
    printf("Player 2: Choose ship placement mode(1: Manual  2: Random)  -->  ");
    scanf("%d", &mode2);
    initializeBoard(board2, boardSize);
    // 입력 1이면 수동 배치, 입력 2면 자동랜덤배치, 나머지는 예외처리
    if (mode2 == 1) {
        placeShips(board2, boardSize, shipsCount);
    } else if (mode2 == 2) {
        placeShipsRandom(board2, boardSize, shipsCount);
    } else {
        printf("Invalid input value!\n");
        multiPlay(boardSize, shipsCount);       
    }


    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("@     BATTLESHIP GAME!     @\n");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("Guess the location of the battleship on the board\n");
    printf("Enter row and column numbers from 0 to %d\n", boardSize - 1);

    int turn = 1;
    while (!hasWon(board1, boardSize) && !hasWon(board2, boardSize)) { 
        if (turn == 1) {
            printf("Player 1's turn: \n");

            processGuess(board1, boardSize, 1);
            if (hasWon(board1, boardSize)) {
                printf("Player 1 wins!\n");
                break;
            }
            turn = 2;
        } else {
            printf("Player 2's turn: \n");

            processGuess(board2, boardSize, 2);
            if (hasWon(board2, boardSize)) {
                printf("Player 2 wins!\n");
                break;
            }
            turn = 1;
        }
    }


    // 게임 종료, 최종 보드 상태 출력 
    printf("\n");
    printf("\n");
    printBoard(board1, boardSize);
    printf("\n\n\n");
    printBoard(board2, boardSize);
}


void gameMode() {
    int n;
    
    printf("Select Mode\n");
    printf("1: SinglePlay  2: MultiPlay  -->  ");
    scanf("%d", &n);

    if (n == 1) {
        selectDifficulty(&boardSize, &shipsCount);
        singlePlay(boardSize, shipsCount);
    } else if (n == 2) {
        selectDifficulty(&boardSize, &shipsCount);
        multiPlay(boardSize, shipsCount);
    } else {
        printf("Invaild Select! Try again\n");
        gameMode();
    }
}


void initializeBoard(char board[][boardSize], int boardSize) { 
    int i, j;
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardSize; j++) {
            board[i][j] = '~'; 
        }
    }
}


void printBoard(char board[][boardSize], int boardSize) {
    int i, j;
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardSize; j++) {
            char cell = board[i][j];
            if (cell == '~') {
                printf("\033[0;34m");
                printf("%c ", cell);
                printf("\033[0;37m");
            } else if (cell == 'H') {
                printf("\033[0;33m");
                printf("%c ", cell);
                printf("\033[0;37m");
            } else if (cell == 'O') {
                printf("\033[0;31m");
                printf("%c ", cell);
                printf("\033[0;37m");
            } else if (cell == 'X') {
                printf("\033[0;36m");
                printf("%c ", cell);
                printf("\033[0;37m");
            } else {
                printf("\033[0;34m");
                printf("~ ");
                printf("\033[0;37m");
            }
        }
        printf("\n");
    }
}


// 전함을 보드에 배치하는 함수

void placeShips(char board[][boardSize], int boardSize, int shipsCount) {
    int i;
    for (i = 0; i < shipsCount; i++) {
        int row, col;
        printf("Enter the coordinates for Ship %d(row column): ", i + 1);

        int result = scanf("%d %d", &row, &col); 
        if (result == 2) { 
            if (getchar() != '\n') { 
                printf("Too many inputs. Only enter two numbers. Try again\n");
                while (getchar() != '\n'); 
                i--; 
                continue; 
            }

            if (row >= 0 && row < boardSize && col >= 0 && col < boardSize) {
                if (board[row][col] != '~') {
                    printf("There is already a ship at that location. Try again\n");
                    i--; 

                } else {
                    board[row][col] = 'S';
                }
            } else {

                printf("Invalid coordinates. Try again\n");
                i--;
            }
        } else { 
            printf("Invalid input. You need to enter only two numbers. Try again\n");
            while (getchar() != '\n'); 
            i--; 
        }
    }
}

// 전함을 보드에 랜덤으로 배치하는 함수
void placeShipsRandom(char board[][boardSize], int boardSize, int shipsCount) {
    int i;
    srand(time(0)); // 시드 설정: rand() 함수를 통한 랜덤 값을 생성하기 위해 현재 시간을 시드로 사용

    for (i = 0; i < shipsCount; i++) {
        int row, col;
        do {
            row = rand() % boardSize; // 0부터 boardSize-1 사이의 랜덤 행 값 생성
            col = rand() % boardSize; 
        } while (board[row][col] != '~'); // 배가 이미 있는지 확인하고, 빈 자리(~)일 때까지 반복
        board[row][col] = 'S'; // 배 배치
    }
}


int isValidGuess(int row, int col, int boardSize) {
    return (row >= 0 && row < boardSize && col >= 0 && col < boardSize); 
}


int hasWon(char board[][boardSize], int boardSize) {
    int i, j;
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardSize; j++) {
            if (board[i][j] == 'S' || board[i][j] == 'H') {
                return 0; 
            }
        }
    }
    return 1;

}


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

    printf("Game Over. Enter name: ");
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
    printf("\n=== Sorted attempt ===\n");
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