#include <stdio.h>
#include <stdlib.h>

// 보드의 기본 크기와 배의 개수를 상수로 정의
#define EASY_BOARD_SIZE 5
#define EASY_SHIPS_COUNT 4
#define HARD_BOARD_SIZE 6
#define HARD_SHIPS_COUNT 7

// 게임 보드를 초기화하는 함수
void initializeBoard(char board[][HARD_BOARD_SIZE], int boardSize) {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            board[i][j] = '~';  // 모든 칸을 '~' (물)로 초기화
        }
    }
}

// 게임 보드를 출력하는 함수
void printBoard(char board[][HARD_BOARD_SIZE], int boardSize) {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j] == '~' || board[i][j] == 'X' || board[i][j] == 'O' || board[i][j] == 'H') {
                printf("%c ", board[i][j]);  // 보드의 현재 상태를 출력
            } else {
                printf("~ ");  // 배 위치는 숨기고 물로 표시
            }
        }
        printf("\n");
    }
}

// 배를 랜덤 위치가 아닌 사용자 입력으로 배치하는 함수
void placeShips(char board[][HARD_BOARD_SIZE], int boardSize, int shipsCount) {
    for (int i = 0; i < shipsCount; i++) {
        int row, col;
        printf("Enter the coordinates for Ship %d (row column): ", i + 1);
        scanf("%d %d", &row, &col);  // 사용자로부터 배의 위치를 입력 받음

        if (row >= 0 && row < boardSize && col >= 0 && col < boardSize) {
            if (board[row][col] != '~') {
                printf("There is already a ship at that location. Try again.\n");  // 이미 배가 있는 위치면 다시 입력 요청
                i--;  // 재입력을 위해 카운터 감소
            } else {
                board[row][col] = 'S';  // 입력된 위치에 배를 배치
            }
        } else {
            printf("Invalid coordinates. Try again.\n");  // 유효하지 않은 좌표 입력시 경고
            i--;  // 재입력을 위해 카운터 감소
        }
    }
}

// 사용자의 추측이 유효한지 확인하는 함수
int isValidGuess(int row, int col, int boardSize) {
    return (row >= 0 && row < boardSize && col >= 0 && col < boardSize);  // 추측한 좌표가 보드 범위 내인지 확인
}

// 모든 배가 파괴되었는지 확인하는 함수
int hasWon(char board[][HARD_BOARD_SIZE], int boardSize) {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j] == 'S' || board[i][j] == 'H') {
                return 0;  // 하나라도 파괴되지 않은 배가 있으면 0 반환
            }
        }
    }
    return 1;  // 모든 배가 파괴되었으면 1 반환
}

int main() {
    int boardSize, shipsCount;
    char difficulty;

    // 난이도를 사용자에게 입력 받음
    printf("Select difficulty (e for easy, h for hard): ");
    scanf(" %c", &difficulty);

    // 입력된 난이도에 따라 보드 크기와 배의 개수를 결정
    if (difficulty == 'h') {
        boardSize = HARD_BOARD_SIZE;
        shipsCount = HARD_SHIPS_COUNT;
    } else {
        boardSize = EASY_BOARD_SIZE;
        shipsCount = EASY_SHIPS_COUNT;
    }

    // 보드 배열 선언 및 초기화
    char board[HARD_BOARD_SIZE][HARD_BOARD_SIZE];
    initializeBoard(board, boardSize);
    placeShips(board, boardSize, shipsCount);

    // 게임 시작 메시지 출력
    printf("=== Battleship Game ===\n");
    printf("Guess the location of the ships on the board.\n");

    // 게임 진행 루프
    while (!hasWon(board, boardSize)) {
        printBoard(board, boardSize);

        int guessRow, guessCol;
        printf("Enter your guess (row column): ");
        scanf("%d %d", &guessRow, &guessent

        // 추측이 유효한지 확인
        if (!isValidGuess(guessRow, guessCol, boardSize)) {
            printf("Invalid guess! Please enter valid coordinates.\n");
            continue;
        }

        // 추측 결과 처리
        if (board[guessRow][guessCol] == 'S') {
            printf("You hit a ship, but it is not destroyed yet!\n");
            board[guessRow][guessCol] = 'H';  // 첫 명중 시 'H'로 표시
        } else if (board[guessRow][guessCol] == 'H') {
            printf("Congratulations! You destroyed a ship!\n");
            board[guessRow][guessCol] = 'X';  // 두 번째 명중 시 'X'로 표시하여 배 파괴
        } else if (board[guessRow][guessCol] == '~') {
            printf("Missed! Try again.\n");
            board[guessRow][guessCol] = 'O';  // 빗나감을 'O'로 표시
        } else if (board[guessRow][guessCol] == 'O' || board[guess_Row][guessCol] == 'X') {
            printf("You've already guessed this location. Try again.\n");  // 이미 추측한 위치는 경고 메시지 출력
        }
    }

    // 게임 종료 후 보드 출력 및 승리 메시지
    printBoard(board, boardSize);
    printf("Congratulations! You sunk all the ships.\n");

    return 0;
}
