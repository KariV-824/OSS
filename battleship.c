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

// 비프음 재생을 위한 음계값 정의
#define _C 1046.502
#define _D 1108.731
#define _E 1318.510
#define _F 1396.913
#define _G 1567.982
#define _A 1760.000
#define _B 1975.533

typedef struct {
    char name[50];
    int attempt;
} Player;

int boardSize = 0;
int shipsCount = 0;
int attempts = 0;
int attempts1 = 0;
int attempts2 = 0;
int remainShips1 = 0;
int remainShips2 = 0;
int findShipcnt1 = 0;
int findShipcnt2 = 0;

void printHeadUI();
void printSingleTailUI(int attempts, int remain, int find);
void printMultiTailUI(int attempts1, int attempts2, int remain1, int remain2, int find1, int find2);
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
    gameMode();  // 게임 모드 선택
    return 0;
}

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

// Player의 추측을 처리하는 함수
void processGuess(char board[][boardSize], int boardSize, int player) {
    int guessRow, guessCol;
    
    printBoard(board, boardSize); // 보드판 출력
    
    printf("Player %d, enter your guess! (row column): ", player);
    while (scanf("%d %d", &guessRow, &guessCol) != 2 || !isValidGuess(guessRow, guessCol, boardSize) || getchar() != '\n') { // 유효하지 않는 입력을 받으면 버퍼를 비우는 작업
        while (getchar() != '\n'); 
        printf("Invalid guess! Please enter valid coordinates\n");
        printf("Player %d, enter your guess! (row column): ", player);
    }

    char cell = board[guessRow][guessCol]; 
    if (cell == 'S') { // cell이 배일 경우
        printf("Player %d hit a ship!\n", player);
        Beep(_B,100);
        board[guessRow][guessCol] = 'H'; // cell을 'H'로 변경하여 배를 맞췄음을 표시
    } else if (cell == 'H') { // cell이 이미 맞춘 배일 경우
        printf("Player %d, Congratulations! You destroyed a ship!\n", player);
        if (player == 0) { // Player0이 배를 찾으면(싱글플레이 모드)
            findShipcnt1++;
            remainShips1--;
        } else if(player == 1) { // Player1이 배를 찾으면(멀티플레이 모드)
            findShipcnt1++; // Player1이 찾은 배 개수 +1
            remainShips2--; // Player2의 남은 배 개수 -1
        } else { // Player2가 배를 찾으면(멀티플레이 모드)
            findShipcnt2++; // Player2가 찾은 배 개수 +1 
            remainShips1--; // Player1의 남은 배 개수 -1
        }
        Beep(_B,100);
        board[guessRow][guessCol] = 'O'; // cell을 'O'로 변경하여 배를 파괴했음을 표시
    } else if (cell == '~') { // cell이 빈 칸일 경우
        printf("Player %d missed! Try again!\n", player);
        Beep(_F,100);
        board[guessRow][guessCol] = 'X'; // cell을 'X'로 변경하여 틀렸음을 표시
    } else { // 이미 추측한 위치일 경우
        printf("Player %d, you've already guessed this location. Try again!\n", player);
    }
}

// 게임 난이도를 선택하는 함수
void selectDifficulty(int *boardSize, int *shipsCount) {
    int difficulty;

    printf("Select Difficulty\n");
    printf("1: Easy  2: Hard  -->  ");
    scanf("%d", &difficulty);
    while (getchar() != '\n'); 

    if (difficulty == 1) { // Easy 난이도를 선택한 경우
        *boardSize = EASY_BOARD_SIZE;
        *shipsCount = EASY_SHIPS_COUNT;
        remainShips1 = EASY_SHIPS_COUNT;
        remainShips2 = EASY_SHIPS_COUNT;
    } else if (difficulty == 2) { // Hard 난이도를 선택한 경우
        *boardSize = HARD_BOARD_SIZE;
        *shipsCount = HARD_SHIPS_COUNT;
        remainShips1 = HARD_SHIPS_COUNT;
        remainShips2 = HARD_SHIPS_COUNT;
    } else {
        printf("Invalid input value!\n");
        selectDifficulty(boardSize, shipsCount); // 함수 재호출로 난이도 재선택
    }
}

// 싱글플레이 모드 함수
void singlePlay(int boardSize, int shipsCount) {
    char board[boardSize][boardSize];
    int guessRow, guessCol;
    int a = 0;
    time_t start, end; 

    initializeBoard(board, boardSize); // 보드 초기화 작업
    placeShipsRandom(board, boardSize, shipsCount); // 배 랜덤배치 작업
    printHeadUI(); // HeadUI 출력

    time(&start); // 게임 시작 시간 기록
    
    while (!hasWon(board, boardSize)) {  // 보드에 배가 남아있지 않을 때까지
        processGuess(board, boardSize, 0); // 배의 위치를 추측
        attempts++; 
        printSingleTailUI(attempts, remainShips1, findShipcnt1); // 한번 추측할때마다 TailUI 출력
    }

    time(&end); // 게임 종료 시간 기록
    int time_taken = difftime(end, start); // 걸린 시간 계산

    printf("\n");
    printBoard(board, boardSize); // 보드판 출력
    printf("Congratulations! All battleships have been shot down. Attempts: %d\n", attempts);
    printf("Time taken: %d seconds\n", time_taken); 
    if (boardSize == 5) { // 보드사이즈에 따라 각각 다른 랭킹표를 표시
        rank_input_E(attempts); // Easy모드 랭킹표
    } else {
        rank_input_H(attempts); // Hard모드 랭킹표
    } 

    while (1) {
        printf("Would you like to check the ranking table?(1: Yes  2: No)  -->  ");
        scanf("%d", &a);
        while(getchar() != '\n');
        if (a == 1) {
            showRanking(boardSize); // 랭킹 출력
            break;
        } else if (a == 2) {
            return;
        } else {
            printf("Invalid Select. Try again!\n");
        }
    }
}

// 멀티플레이 모드 함수
void multiPlay(int boardSize, int shipsCount) {
    char board1[boardSize][boardSize];
    char board2[boardSize][boardSize];
    int guessRow1, guessCol1;
    int guessRow2, guessCol2;
    int mode1, mode2; 

    while (1) {
        printf("Player 1: Choose ship placement mode(1: Manual  2: Random)  -->  "); 
        scanf("%d", &mode1);
        while(getchar() != '\n');

        initializeBoard(board1, boardSize); // 보드1 초기화 작업

        if (mode1 == 1) { // Player1이 배의 위치를 직접 선택하는 경우
            placeShips(board1, boardSize, shipsCount); // Player1의 배 수동배치 작업
            break;
        } else if (mode1 == 2) { // 자동으로 배의 위치를 선택하는 경우
            placeShipsRandom(board1, boardSize, shipsCount); // 보드1의 배 랜덤배치 작업
            break;
        } else {
            printf("Invalid input value! Please try again!\n");
        }
    }

    while (1) {
        printf("Player 2: Choose ship placement mode(1: Manual  2: Random)  -->  ");
        scanf("%d", &mode2);
        while(getchar() != '\n'); 

        initializeBoard(board2, boardSize); // 보드2 초기화 작업

        if (mode2 == 1) { // Player2가 배의 위치를 직접 선택하는 경우
            placeShips(board2, boardSize, shipsCount); // Player2의 배 수동배치 작업
            break;
        } else if (mode2 == 2) { // 자동으로 배의 위치를 선택하는 경우
            placeShipsRandom(board2, boardSize, shipsCount); // 보드2의 배 랜덤배치 작업
            break;
        } else {
            printf("Invalid input value! Please try again!\n");
        }
    }

    printHeadUI(); // HeadUI 출력
    printf("Guess the location of the battleship on the board!\n");
    printf("Enter row and column numbers from 0 to %d\n", boardSize - 1);

    int turn = 1;

    while (!hasWon(board1, boardSize) && !hasWon(board2, boardSize)) {  // 두 보드 중 어느 한쪽에서도 승리 조건이 만족되지 않을 때까지
        if (turn == 1) {
            printf("Player 1's turn: \n");
            processGuess(board1, boardSize, 1); // 보드1의 배 위치를 추측
            attempts1++; 
            printMultiTailUI(attempts1, attempts2, remainShips1, remainShips2, findShipcnt1, findShipcnt2); // 한번 추측할때마다 TailUI 출력
            if (hasWon(board1, boardSize)) { // 만약 Player1이 배를 모두 찾았다면
                printf("Player 1 wins!\n");
                break;
            }
            turn = 2; 
        } else {
            printf("Player 2's turn: \n");
            processGuess(board2, boardSize, 2); // 보드2의 배 위치를 추측
            attempts2++; 
            printMultiTailUI(attempts1, attempts2, remainShips1, remainShips2, findShipcnt1, findShipcnt2); // 한번 추측할때마다 TailUI 출력
            if (hasWon(board2, boardSize)) { // 만약 Player2가 배를 모두 찾았다면
                printf("Player 2 wins!\n");
                break;
            }
            turn = 1;
        }
    }
 
    printf("\n");
    printf("\n");
    printBoard(board1, boardSize); // 보드판1 출력
    printf("\n\n\n");
    printBoard(board2, boardSize); // 보드판2 출력
}

// 게임 모드를 선택하는 함수
void gameMode() {
    int n;
    
    printf("Select Mode\n");
    printf("1: SinglePlay  2: MultiPlay  -->  ");
    scanf("%d", &n);
    while(getchar() != '\n');

    if (n == 1) { // 싱글플레이 모드 선택시
        selectDifficulty(&boardSize, &shipsCount); // 난이도 선택
        singlePlay(boardSize, shipsCount); // 싱글플레이 모드 시작
    } else if (n == 2) { // 멀티플레이 모드 선택시
        selectDifficulty(&boardSize, &shipsCount); // 난이도 선택
        multiPlay(boardSize, shipsCount); // 멀티플레이 모드 시작
    } else { 
        printf("Invalid Select. Try again!\n");
        gameMode(); // 함수 재호출로 게임 모드 재선택
    }
}

// 보드를 초기화하는 함수
void initializeBoard(char board[][boardSize], int boardSize) {
    int i, j;
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardSize; j++) {
            board[i][j] = '~'; // 모든 보드칸을 초기화
        }
    }
}

// 보드를 출력하는 함수
void printBoard(char board[][boardSize], int boardSize) {
    int i, j;
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardSize; j++) {
            char cell = board[i][j];
            if (cell == '~') { // cell이 빈 칸일 경우
                printf("\033[0;34m"); // 파란색
                printf("%c ", cell);
                printf("\033[0;37m"); // 기본색
            } else if (cell == 'H') { // cell이 이미 맞춘 배일 경우
                printf("\033[0;33m"); // 노란색
                printf("%c ", cell);
                printf("\033[0;37m"); // 기본색
            } else if (cell == 'O') { // cell이 배일 경우
                printf("\033[0;31m"); // 빨간색
                printf("%c ", cell);
                printf("\033[0;37m"); // 기본색
            } else if (cell == 'X') { // cell이 비어 있을 경우
                printf("\033[0;36m"); // 초록색
                printf("%c ", cell);
                printf("\033[0;37m"); // 기본색
            } else {
                printf("\033[0;34m"); // 파란색
                printf("~ ");
                printf("\033[0;37m"); // 기본색
            }
        }
        printf("\n");
    }
}

// 배를 보드에 배치하는 함수
void placeShips(char board[][boardSize], int boardSize, int shipsCount) {
    int i;
    for (i = 0; i < shipsCount; i++) {
        int row, col;
        printf("Enter the coordinates for Ship %d(row column): ", i + 1);
        int result = scanf("%d %d", &row, &col); 
        if (result == 2) { // 2개의 정수가 입력되었을 때만 실행
            if (getchar() != '\n') { 
                printf("Too many inputs. Only enter two numbers. Try again!\n");
                while (getchar() != '\n'); 
                i--; // 이번 입력을 무효화하고, 입력을 다시 받도록 함
                continue; 
            }

            if (row >= 0 && row < boardSize && col >= 0 && col < boardSize) {
                if (board[row][col] != '~') {
                    printf("There is already a ship at that location. Try again!\n");
                    i--; // 잘못된 위치 입력 시, 입력을 다시 받도록 함
                } else {
                    board[row][col] = 'S';
                }
            } else {
                printf("Invalid coordinates. Try again!\n");
                i--; // 범위 밖의 좌표 입력 시, 입력을 다시 받도록 함
            }
        } else { // 입력받은 데이터가 2개의 정수가 아니라면
            printf("Invalid input. You need to enter two numbers. Try again!\n");
            while (getchar() != '\n'); 
            i--; // 이번 입력을 무효화하고, 입력을 다시 받도록 함
        }
    }
}

// 배를 보드에 랜덤으로 배치하는 함수
void placeShipsRandom(char board[][boardSize], int boardSize, int shipsCount) {
    int i;
    srand(time(0)); // rand() 함수의 난수 생성을 위해 현재 시간을 시드로 설정

    for (i = 0; i < shipsCount; i++) {
        int row, col;
        do {
            row = rand() % boardSize; // 랜덤 '행' 생성
            col = rand() % boardSize; // 랜덤 '열' 생성
        } while (board[row][col] != '~'); 
        board[row][col] = 'S'; // 배 배치
    }
}

// 추측한 배의 범위가 유효한지를 확인하는 함수
int isValidGuess(int row, int col, int boardSize) {
    return (row >= 0 && row < boardSize && col >= 0 && col < boardSize); // 유효하면 1, 유효하지 않으면 0 반환
}

// 모든 배가 격추되었는지를 확인하는 함수
int hasWon(char board[][boardSize], int boardSize) {
    int i, j;
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardSize; j++) {
            if (board[i][j] == 'S' || board[i][j] == 'H') {
                return 0; // 보드판에 배가 남아있다면 0을 반환
            }
        }
    }
    return 1; // 보드판에 배가 없다면 1을 반환(승리)
}

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