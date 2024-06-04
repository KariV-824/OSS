#include "PlaceshipFun.h"

int remainShips1=0;
int remainShips2=0;
int findShipcnt1=0;
int findShipcnt2=0;

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


void placeShips(char board[][boardSize], int boardSize, int shipsCount) {
    int i;
    for (i = 0; i < shipsCount; i++) {
        int row, col;
        printf("Enter the coordinates for Ship %d(row column): ", i + 1);
        int result = scanf("%d %d", &row, &col); 
        if (result == 2) { 
            if (getchar() != '\n') { 
                printf("Too many inputs. Only enter two numbers. Try again!\n");
                while (getchar() != '\n'); 
                i--; 
                continue; 
            }

            if (row >= 0 && row < boardSize && col >= 0 && col < boardSize) {
                if (board[row][col] != '~') {
                    printf("There is already a ship at that location. Try again!\n");
                    i--; 
                } else {
                    board[row][col] = 'S';
                }
            } else {
                printf("Invalid coordinates. Try again!\n");
                i--;
            }
        } else { 
            printf("Invalid input. You need to enter two numbers. Try again!\n");
            while (getchar() != '\n'); 
            i--; 
        }
    }
}

void placeShipsRandom(char board[][boardSize], int boardSize, int shipsCount) {
    int i;
    srand(time(0)); 

    for (i = 0; i < shipsCount; i++) {
        int row, col;
        do {
            row = rand() % boardSize; 
            col = rand() % boardSize; 
        } while (board[row][col] != '~'); 
        board[row][col] = 'S'; 
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



void processGuess(char board[][boardSize], int boardSize, int player) {
    int guessRow, guessCol;
    
    printBoard(board, boardSize);
    
    printf("Player %d, enter your guess! (row column): ", player);
    while (scanf("%d %d", &guessRow, &guessCol) != 2 || !isValidGuess(guessRow, guessCol, boardSize) || getchar() != '\n') {
        while (getchar() != '\n'); 
        printf("Invalid guess! Please enter valid coordinates\n");
        printf("Player %d, enter your guess! (row column): ", player);
    }

    char cell = board[guessRow][guessCol];
    if (cell == 'S') {
        printf("Player %d hit a ship!\n", player);
        Beep(_B,100);
        board[guessRow][guessCol] = 'H';
    } else if (cell == 'H') {
        printf("Player %d, Congratulations! You destroyed a ship!\n", player);
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
        printf("Player %d missed! Try again!\n", player);
        Beep(_F,100);
        board[guessRow][guessCol] = 'X';
    } else {
        printf("Player %d, you've already guessed this location. Try again!\n", player);
    }
}





