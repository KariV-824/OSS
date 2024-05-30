//by Óscar Poblete Sáenz

#include <stdio.h>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")
#define BOARD_SIZE 5 // Define the size of the game board
#define SHIPS_COUNT 4 // Define the number of ships in the game

#define _C 1046.502
#define _D 1108.731
#define _E 1318.510
#define _F 1396.913
#define _G 1567.982
#define _A 1760.000
#define _B 1975.533

int attempts = 0;

void printHeadUI()
{
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("@        BATTLESHIP        @\n");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
}
void printtailUI(int attempts)
{
    printf("\033[0;37m");
    printf("@ @ @ @ @ @ @ @ @ @\n");
    printf("@  attempts : %d  @\n",attempts);
    printf("@ @ @ @ @ @ @ @ @ @\n");
}
void initializeBoard(char board[][BOARD_SIZE]) {
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = '~';  // '~' represents an empty cell
        }
    }
}

void printBoard(char board[][BOARD_SIZE]) {
    int i, j;
    printHeadUI();
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == '~')  
            {
                printf("\033[0;34m");
                printf("%c ", board[i][j]);
            }
            else if (board[i][j] == 'X')
            {
                printf("\033[0;31m");
                printf("%c ", board[i][j]);
            }
            else if (board[i][j] == 'O')
            {
                printf("\033[0;36m");
                printf("%c ", board[i][j]);
            }
            
            else {
                printf("\033[0;34m");
                printf("~ ");  // Hide ship locations with '~'
            }
        }
        printf("\n");
    }
    printtailUI(attempts);
}

void placeShips(char board[][BOARD_SIZE]) {
    int i;
    for (i = 0; i < SHIPS_COUNT; i++) {
        int row, col;
        printf("Enter the coordinates for Ship %d (row column): ", i + 1);
        scanf("%d %d", &row, &col);

        if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) {
            if (board[row][col] != '~') {
                printf("There is already a ship at that location. Try again.\n");
                i--;
            } else {
                board[row][col] = 'S';  // 'S' represents a ship
            }
        } else {
            printf("Invalid coordinates. Try again.\n");
            i--;
        }
    }
}

int isValidGuess(int row, int col) {
    return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE);
}

int hasWon(char board[][BOARD_SIZE]) {
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 'S') {
                return 0;  // At least one ship is still remaining
            }
        }
    }
    return 1;  // All ships have been sunk
}



int main() {
    char board[BOARD_SIZE][BOARD_SIZE];
    int guessRow, guessCol;


    initializeBoard(board);
    placeShips(board);

    printf("=== Battleship Game ===\n");
    printf("Guess the location of the ships on the board.\n");
    printf("Enter row and column numbers between 0 and 4.\n");



    while (!hasWon(board)) {
        printf("\n");
        printBoard(board);

        printf("Enter your guess (row column): ");
        scanf("%d %d", &guessRow, &guessCol);

        if (!isValidGuess(guessRow, guessCol)) {
            printf("Invalid guess! Please enter valid coordinates.\n");
            continue;
        }

        if (board[guessRow][guessCol] == 'S') {
            printf("Congratulations! You hit a ship!\n");
            Beep(_B,100);
            board[guessRow][guessCol] = 'X';  // 'X' represents a hit
        } else if (board[guessRow][guessCol] == '~') {
            printf("Missed! Try again.\n");
            Beep(_F,100);
            board[guessRow][guessCol] = 'O';  // 'O' represents a miss
        } else {
            printf("You've already guessed this location. Try again.\n");
        }

        attempts++;
    }

    printf("\n");
    printBoard(board);
    printf("Congratulations! You sunk all the ships in %d attempts.\n", attempts);

    return 0;
    
}
