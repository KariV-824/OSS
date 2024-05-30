#include <stdio.h>
#include <stdlib.h>

#define EASY_BOARD_SIZE 5
#define EASY_SHIPS_COUNT 4
#define HARD_BOARD_SIZE 6
#define HARD_SHIPS_COUNT 7

int boardSize;  // 전역 변수로 보드 크기 설정

void initializeBoard(char board[][boardSize]) {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            board[i][j] = '~';  // 모든 칸을 '~' (물)로 초기화
        }
    }
}

void printBoard(char board[][boardSize]) {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            char displayChar = (board[i][j] == 'S') ? '~' : board[i][j];
            printf("%c ", displayChar);
        }
        printf("\n");
    }
}

void placeShips(char board[][boardSize], int shipsCount) {
    int row, col;
    for (int i = 0; i < shipsCount; i++) {
        printf("Enter the coordinates for Ship %d (row column): ", i + 1);
        while (scanf("%d %d", &row, &col) != 2 || row < 0 || row >= boardSize || col < 0 || col >= boardSize || board[row][col] != '~') {
            while (getchar() != '\n');  // 입력 버퍼를 비웁니다.
            printf("Invalid coordinates or already occupied. Try again.\n");
            printf("Enter the coordinates for Ship %d (row column): ", i + 1);
        }
        board[row][col] = 'S';  // 배를 배치
    }
}

int isValidGuess(int row, int col) {
    return row >= 0 && row < boardSize && col >= 0 && col < boardSize;
}

int hasWon(char board[][boardSize]) {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j] == 'S' || board[i][j] == 'H') {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    char difficulty;
    printf("Select difficulty (e for easy, h for hard): ");
    scanf(" %c", &difficulty);
    while(getchar() != '\n');  // 입력 버퍼 비우기

    if (difficulty == 'h') {
        boardSize = HARD_BOARD_SIZE;
    } else if (difficulty == 'e') {
        boardSize = EASY_BOARD_SIZE;
    } else {
        printf("Invalid input value!\n");
        return 1;
    }

    int shipsCount = (difficulty == 'h') ? HARD_SHIPS_COUNT : EASY_SHIPS_COUNT;
    char board[boardSize][boardSize];  // VLA 사용하여 동적 배열 생성
    initializeBoard(board);
    placeShips(board, shipsCount);

    printf("=== Battleship Game ===\nGuess the location of the ships on the board.\n");

    int guessRow, guessCol;
    while (!hasWon(board)) {
        printBoard(board);
        printf("Enter your guess (row column): ");
        while (scanf("%d %d", &guessRow, &guessCol) != 2 || !isValidGuess(guessRow, guessCol)) {
            while (getchar() != '\n');  // 입력 버퍼를 비웁니다.
            printf("Invalid guess! Please enter valid coordinates.\n");
        }

        if (board[guessRow][guessCol] == 'S') {
            printf("You hit a ship!\n");
            board[guessRow][guessCol] = 'H';  // 첫 번째 명중
        } else if (board[guessRow][guessCol] == 'H') {
            printf("Congratulations! You destroyed a ship!\n");
            board[guessRow][guessCol] = 'X';  // 배 파괴
        } else if (board[guessRow][guessCol] == '~') {
            printf("Missed! Try again.\n");
            board[guessRow][guessCol] = 'O';  // 빗나감
        } else {
            printf("You've already guessed this location. Try again.\n");
        }
    }

    printBoard(board);
    printf("Congratulations! You sunk all the ships.\n");

    return 0;
}
