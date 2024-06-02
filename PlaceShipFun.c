#include "PlaceshipFun.h"


// 전함을 보드에 배치하는 함수
void placeShips(char board[][boardSize], int boardSize, int shipsCount) {
    int i;
    for (i = 0; i < shipsCount; i++) {
        int row, col;
        printf("Enter the coordinates for Ship %d(row column): ", i + 1);
        int result = scanf("%d %d", &row, &col); // 2개의 정수를 입력받아서 result에 저장
        if (result == 2) { // 2개의 정수가 입력되었을 때만 실행
            if (getchar() != '\n') { // 2개의 정수 이후에 추가 문자가 버퍼에 남아있다면
                printf("Too many inputs. Only enter two numbers. Try again.\n");
                while (getchar() != '\n'); // 버퍼에 남은 모든 문자를 버리며 '\n'를 만날 때까지 반복
                i--; // i를 감소시켜 이번 입력을 무효화하고, 입력을 다시 받도록 함
                continue; // for 루프의 처음으로 돌아가 재시작
            }

            if (row >= 0 && row < boardSize && col >= 0 && col < boardSize) {
                if (board[row][col] != '~') {
                    printf("There is already a ship at that location. Try again.\n");
                    i--; // 잘못된 위치 입력 시 다시 입력
                } else {
                    board[row][col] = 'S';
                }
            } else {
                printf("Invalid coordinates. Try again.\n");
                i--; // 범위 밖 좌표 입력 시 다시 입력
            }
        } else { // 입력받은 데이터가 2개의 정수가 아니라면
            printf("Invalid input. You need to enter only two numbers. Try again.\n");
            while (getchar() != '\n'); // 버퍼에 남은 모든 문자를 버리며 '\n'를 만날 때까지 반복
            i--; // i를 감소시켜 이번 입력을 무효화하고, 입력을 다시 받도록 함
        }
    }
}

// 전함을 보드에 랜덤으로 배치하는 함수
void placeShipsRandom(char board[][boardSize], int boardSize, int shipsCount) {
    int i;
    srand(time(0)); // 시드 설정: rand() 함수를 통한 랜덤 값을 생성하기 위해 현재 시간을 시드로 사용

    for (i = 0; i < shipsCount; i++) {
        int row, col;
        do {
            row = rand() % boardSize; // 0부터 boardSize-1 사이의 랜덤 행 값 생성
            col = rand() % boardSize; // 0부터 boardSize-1 사이의 랜덤 열 값 생성
        } while (board[row][col] != '~'); // 배가 이미 있는지 확인하고, 빈 자리(~)일 때까지 반복
        board[row][col] = 'S'; // 배 배치
    }
}

// 유효한 추측인지 확인하는 함수
int isValidGuess(int row, int col, int boardSize) {
    return (row >= 0 && row < boardSize && col >= 0 && col < boardSize); // 보드 사이즈 안에 있으면 T리턴 아니면 F리턴
}

// 모든 전함이 격추되었는지 확인하는 함수
int hasWon(char board[][boardSize], int boardSize) {
    int i, j;
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardSize; j++) {
            if (board[i][j] == 'S' || board[i][j] == 'H') {
                return 0; // 아직 격추되지 않은 전함이 하나 이상 남아있음
            }
        }
    }
    return 1; // 모든 전함이 격추됨
}
// 보드를 빈 칸으로 초기화하는 함수
void initializeBoard(char board[][boardSize], int boardSize) { // 모두 '~'로 출력함함
    int i, j;
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardSize; j++) {
            board[i][j] = '~'; // '~'는 빈 칸을 나타냄
        }
    }
}

// 전함 위치를 감추고 보드를 출력하는 함수
void printBoard(char board[][boardSize], int boardSize) {
    int i, j;
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardSize; j++) {
            char cell = board[i][j];
            if (cell == '~') {
                printf("\033[0;34m");
                printf("%c ", cell);
            } else if (cell == 'H') {
                printf("\033[0;33m"); // 노란색
                printf("%c ", cell);
            } else if (cell == 'O') {
                printf("\033[0;31m");
                printf("%c ", cell);
            } else if (cell == 'X') {
                printf("\033[0;36m");
                printf("%c ", cell);
            } else {
                printf("\033[0;34m");
                printf("~");  // Hide ship locations with '~'
            }
        }
        printf("\n");
    }
}


void processGuess(char board[][boardSize], int boardSize, int player) {
    int guessRow, guessCol;
    
    printBoard(board, boardSize);
    
    printf("Player %d, enter your guess (row column): ", player);
    while (scanf("%d %d", &guessRow, &guessCol) != 2 || !isValidGuess(guessRow, guessCol, boardSize)) {
        while (getchar() != '\n'); 
        printf("Invalid guess! Please enter valid coordinates.\n");
        printf("Player %d, enter your guess (row column): ", player);
    }

    char cell = board[guessRow][guessCol];
    if (cell == 'S') {
        printf("Player %d hit a ship!\n", player);
        Beep(_B,100);
        board[guessRow][guessCol] = 'H';
    } else if (cell == 'H') {
        printf("Player %d, congratulations! You destroyed a ship!\n", player);
        Beep(_B,100);
        board[guessRow][guessCol] = 'O';
    } else if (cell == '~') {
        printf("Player %d missed! Try again.\n", player);
        Beep(_F,100);
        board[guessRow][guessCol] = 'X';
    } else {
        printf("Player %d, you've already guessed this location. Try again.\n", player);
    }
}






