#include "GameMode.h"


int attempts=0;
int boardSize=0;
int shipsCount=0;


void selectDifficulty(int *boardSize, int *shipsCount) {
    int difficulty;

    printf("Select Difficulty\n");
    printf("1: Easy  2: Hard  --> ");
    scanf("%d", &difficulty);
    while (getchar() != '\n');  // 입력 버퍼 비우기

    if (difficulty == 1) {
        *boardSize = EASY_BOARD_SIZE;
        *shipsCount = EASY_SHIPS_COUNT;
    } else if (difficulty == 2) {
        *boardSize = HARD_BOARD_SIZE;
        *shipsCount = HARD_SHIPS_COUNT;
    } else {
        printf("Invalid input value!\n");
        selectDifficulty(boardSize, shipsCount);
    }
}

void singlePlay(int boardSize, int shipsCount) {
    attempts=0;
    char board[boardSize][boardSize];
    int guessRow, guessCol;
    int a = 0;
    time_t start, end; // 시간 측정을 위한 변수

    initializeBoard(board, boardSize); // 초기화
    placeShipsRandom(board, boardSize, shipsCount); // 랜덤 배치
    printHeadUI();

    time(&start); // 게임 시작 시간 기록
    // 게임 루프
    while (!hasWon(board, boardSize)) {  // 보드에 전함이 남아있으면
        processGuess(board, boardSize, 1);
        attempts++; //시도 횟수 증가
        printTailUI(attempts);
    }

    time(&end); // 게임 종료 시간 기록
    int time_taken = difftime(end, start); // 걸린 시간 계산

    // 게임 종료, 최종 보드 상태와 시도 횟수 출력
    printf("\n");
    printBoard(board, boardSize);
    printf("Congratulations! All battleships have been shot down. Attempts: %d\n", attempts);
    printf("Time taken: %d seconds\n", time_taken); // 총 소요 시간 출력
    
    if (boardSize == 5) {
        rank_input_E(attempts);
    } else {
        rank_input_H(attempts);
    }

    printf("Would you like to check the ranking table? 1: Yes  2: No  --> ");
    scanf("%d", &a);
    if (a == 1) {
        showRanking(boardSize);
    } else if ( a == 2) {
        return;
    }
}

void multiPlay(int boardSize, int shipsCount) {
    char board1[boardSize][boardSize]; // 1플레이어 보드
    char board2[boardSize][boardSize]; // 2플레이어 보드 
    int guessRow1, guessCol1;
    int guessRow2, guessCol2;
    int mode1, mode2; // 각 플레이어의 배치 모드

    // 플레이어 1의 배치 모드 선택
    printf("Player 1: Choose ship placement mode(1: Manual  2: Random)  --> ");
    scanf("%d", &mode1);
    initializeBoard(board1, boardSize);

    if (mode1 == 1) {
        placeShips(board1, boardSize, shipsCount);
    } else {
        placeShipsRandom(board1, boardSize, shipsCount);
    }

    // 플레이어 2의 배치 모드 선택
    printf("Player 2: Choose ship placement mode(1: Manual  2: Random)  --> ");
    scanf("%d", &mode2);
    initializeBoard(board2, boardSize);

    if (mode2 == 1) {
        placeShips(board2, boardSize, shipsCount);
    } else {
        placeShipsRandom(board2, boardSize, shipsCount);
    }

    // 게임 설명 출력
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("@        BATTLESHIP        @\n");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("Guess the location of the battleship on the board.\n");
    printf("Enter row and column numbers from 0 to %d.\n", boardSize - 1);

    int turn = 1;
    // 게임 루프
    while (!hasWon(board1, boardSize) && !hasWon(board2, boardSize)) {  // 보드에 전함이 남아있으면
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
    printf("1: SinglePlay  2: MultiPlay  --> ");
    scanf("%d", &n);

    if (n == 1) {
        selectDifficulty(&boardSize, &shipsCount);
        singlePlay(boardSize, shipsCount);
    } else if (n == 2) {
        selectDifficulty(&boardSize, &shipsCount);
        multiPlay(boardSize, shipsCount);
    } else {
        printf("Invaild Select! Try again.\n");
        gameMode(); // 잘못 입력시 다시 모드 선택하도록 함.
    }
}