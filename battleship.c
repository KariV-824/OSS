//by Óscar Poblete Sáenz
#include <stdio.h>

#define BOARD_SIZE 5 // Define the size of the game board
#define SHIPS_COUNT 4 // Define the number of ships in the game

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
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == '~' || board[i][j] == 'X' || board[i][j] == 'O') {
                printf("%c ", board[i][j]);
            } else {
                printf("~ ");  // Hide ship locations with '~'
            }
        }
        printf("\n");
    }
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
    int attempts = 0;

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
            board[guessRow][guessCol] = 'X';  // 'X' represents a hit
        } else if (board[guessRow][guessCol] == '~') {
            printf("Missed! Try again.\n");
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
