#include "GameMode.h"


int attempts=0;
int attempts1=0;
int attempts2=0;
int boardSize=0;
int shipsCount=0;


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