#include "GameMode.h"


int attempts=0;
int attempts1=0;
int attempts2=0;
int boardSize=0;
int shipsCount=0;


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
    time_t start, end; 

    initializeBoard(board, boardSize); 
    placeShipsRandom(board, boardSize, shipsCount); 
    printHeadUI();

    time(&start);
    
    while (!hasWon(board, boardSize)) {  
        processGuess(board, boardSize, 0);
        attempts++; 
        printTailUI(attempts, remainShips1, findShipcnt1);
    }

    time(&end);
    int time_taken = difftime(end, start); 


    printf("\n");
    printBoard(board, boardSize);
    printf("Congratulations! All battleships have been shot down. Attempts: %d\n", attempts);
    printf("Time taken: %d seconds\n", time_taken);
    if (boardSize == 5) {
        rank_input_E(attempts);
    } else {
        rank_input_H(attempts);
    } 

    while (1) {
        printf("Would you like to check the ranking table?(1: Yes  2: No)  -->  ");
        scanf("%d", &a);
        while(getchar() != '\n');
        if (a == 1) {
            showRanking(boardSize);
            break;
        } else if (a == 2) {
            return;
        } else {
            printf("Invalid Select. Try again!\n");
        }
    }
}

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

        initializeBoard(board1, boardSize);

        if (mode1 == 1) {
            placeShips(board1, boardSize, shipsCount);
            break;
        } else if (mode1 == 2) {
            placeShipsRandom(board1, boardSize, shipsCount);
            break;
        } else {
            printf("Invalid input value! Please try again!\n");
        }
    }

    while (1) {
        printf("Player 2: Choose ship placement mode(1: Manual  2: Random)  -->  ");
        scanf("%d", &mode2);
        while(getchar() != '\n'); 

        initializeBoard(board2, boardSize);

        if (mode2 == 1) {
            placeShips(board2, boardSize, shipsCount);
            break;
        } else if (mode2 == 2) {
            placeShipsRandom(board2, boardSize, shipsCount);
            break;
        } else {
            printf("Invalid input value! Please try again!\n");
        }
    }

    printHeadUI();
    printf("Guess the location of the battleship on the board!\n");
    printf("Enter row and column numbers from 0 to %d\n", boardSize - 1);

    int turn = 1;

    while (!hasWon(board1, boardSize) && !hasWon(board2, boardSize)) {
        if (turn == 1) {
            printf("Player 1's turn: \n");
            processGuess(board1, boardSize, 1);
            attempts1++; 
            printMultiUI(attempts1, attempts2, remainShips1, remainShips2, findShipcnt1, findShipcnt2);
            if (hasWon(board1, boardSize)) {
                printf("Player 1 wins!\n");
                break;
            }
            turn = 2;
        } else {
            printf("Player 2's turn: \n");
            processGuess(board2, boardSize, 2);
            attempts2++; 
            printMultiUI(attempts1, attempts2, remainShips1, remainShips2, findShipcnt1, findShipcnt2);
            if (hasWon(board2, boardSize)) {
                printf("Player 2 wins!\n");
                break;
            }
            turn = 1;
        }
    }
 
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
    while(getchar() != '\n');

    if (n == 1) {
        selectDifficulty(&boardSize, &shipsCount);
        singlePlay(boardSize, shipsCount);
    } else if (n == 2) {
        selectDifficulty(&boardSize, &shipsCount);
        multiPlay(boardSize, shipsCount);
    } else {
        printf("Invalid Select. Try again!\n");
        gameMode();
    }
}