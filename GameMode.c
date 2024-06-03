#include "GameMode.h"


int attempts=0;
int boardSize=0;
int shipsCount=0;


void selectDifficulty(int *boardSize, int *shipsCount) {
    int difficulty;

    printf("Select Difficulty\n");
    printf("1: Easy  2: Hard  -->  ");
    scanf("%d", &difficulty);
    while (getchar() != '\n');  // �Է� ���� ����

    if (difficulty == 1) {
        *boardSize = EASY_BOARD_SIZE;
        *shipsCount = EASY_SHIPS_COUNT;
        remainships1 = EASY_SHIPS_COUNT;
        remainships2 = EASY_SHIPS_COUNT;
    } else if (difficulty == 2) {
        *boardSize = HARD_BOARD_SIZE;
        *shipsCount = HARD_SHIPS_COUNT;
        remainships1 = HARD_SHIPS_COUNT;
        remainships2 = HARD_SHIPS_COUNT;
    } else {
        printf("Invalid input value!\n");
        exit(1);
    }
}

void singlePlay(int boardSize, int shipsCount) {
    char board[boardSize][boardSize];
    int guessRow, guessCol;


    int a = 0;
    time_t start, end; // �ð� ������ ���� ����

    initializeBoard(board, boardSize); // �ʱ�ȭ
    placeShipsRandom(board, boardSize, shipsCount); // ���� ��ġ
    printHeadUI();

    time(&start); // ���� ���� �ð� ���
    // ���� ����
    while (!hasWon(board, boardSize)) {  // ���忡 ������ ����������
        processGuess(board, boardSize, 0);
        attempts++; //�õ� Ƚ�� ����
        printTailUI(attempts,remainships1,findshipcnt1);
    }

    time(&end); // ���� ���� �ð� ���
    int time_taken = difftime(end, start); // �ɸ� �ð� ���

    // ���� ����, ���� ���� ���¿� �õ� Ƚ�� ���
    printf("\n");
    printBoard(board, boardSize);
    printf("Congratulations! All battleships have been shot down. Attempts: %d\n", attempts);
    printf("Time taken: %d seconds\n", time_taken); // �� �ҿ� �ð� ���
    
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

    // ���� ���� ���
    printHeadUI();
    printf("Guess the location of the battleship on the board\n");
    printf("Enter row and column numbers from 0 to %d\n", boardSize - 1);

    int turn = 1;
    // ���� ����
    while (!hasWon(board1, boardSize) && !hasWon(board2, boardSize)) {
        printMultiUI(attempts,remainships1,remainships2,findshipcnt1,findshipcnt2);  // ���忡 ������ ����������
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
    selectDifficulty(&boardSize, &shipsCount);

    if (n == 1) {
        singlePlay(boardSize, shipsCount);
    } else if (n == 2) {
        multiPlay(boardSize, shipsCount);
    } else {
        printf("Invaild Select! Try again\n");
        gameMode(); // �߸� �Է½� �ٽ� ��� �����ϵ��� ��.
    }
}