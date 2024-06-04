#include "PlaceshipFun.h"


int remainShips1=0;
int remainShips2=0;
int findShipcnt1=0;
int findShipcnt2=0;

// 보드를 초기화하는 함수
void initializeBoard(char board[][boardSize], int boardSize) {
    int i, j;
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardSize; j++) {
            board[i][j] = '~'; // 모든 보드칸을 초기화
        }
    }
}

// 보드를 출력하는 함수
void printBoard(char board[][boardSize], int boardSize) {
    int i, j;
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardSize; j++) {
            char cell = board[i][j];
            if (cell == '~') { // cell이 빈 칸일 경우
                printf("\033[0;34m"); // 파란색
                printf("%c ", cell);
                printf("\033[0;37m"); // 기본색
            } else if (cell == 'H') { // cell이 이미 맞춘 배일 경우
                printf("\033[0;33m"); // 노란색
                printf("%c ", cell);
                printf("\033[0;37m"); // 기본색
            } else if (cell == 'O') { // cell이 배일 경우
                printf("\033[0;31m"); // 빨간색
                printf("%c ", cell);
                printf("\033[0;37m"); // 기본색
            } else if (cell == 'X') { // cell이 비어 있을 경우
                printf("\033[0;36m"); // 초록색
                printf("%c ", cell);
                printf("\033[0;37m"); // 기본색
            } else {
                printf("\033[0;34m"); // 파란색
                printf("~ ");
                printf("\033[0;37m"); // 기본색
            }
        }
        printf("\n");
    }
}

// 배를 보드에 배치하는 함수
void placeShips(char board[][boardSize], int boardSize, int shipsCount) {
    int i;
    for (i = 0; i < shipsCount; i++) {
        int row, col;
        printf("Enter the coordinates for Ship %d(row column): ", i + 1);
        int result = scanf("%d %d", &row, &col); 
        if (result == 2) { // 2개의 정수가 입력되었을 때만 실행
            if (getchar() != '\n') { 
                printf("Too many inputs. Only enter two numbers. Try again!\n");
                while (getchar() != '\n'); 
                i--; // 이번 입력을 무효화하고, 입력을 다시 받도록 함
                continue; 
            }

            if (row >= 0 && row < boardSize && col >= 0 && col < boardSize) {
                if (board[row][col] != '~') {
                    printf("There is already a ship at that location. Try again!\n");
                    i--; // 잘못된 위치 입력 시, 입력을 다시 받도록 함
                } else {
                    board[row][col] = 'S';
                }
            } else {
                printf("Invalid coordinates. Try again!\n");
                i--; // 범위 밖의 좌표 입력 시, 입력을 다시 받도록 함
            }
        } else { // 입력받은 데이터가 2개의 정수가 아니라면
            printf("Invalid input. You need to enter two numbers. Try again!\n");
            while (getchar() != '\n'); 
            i--; // 이번 입력을 무효화하고, 입력을 다시 받도록 함
        }
    }
}

// 배를 보드에 랜덤으로 배치하는 함수
void placeShipsRandom(char board[][boardSize], int boardSize, int shipsCount) {
    int i;
    srand(time(0)); // rand() 함수의 난수 생성을 위해 현재 시간을 시드로 설정

    for (i = 0; i < shipsCount; i++) {
        int row, col;
        do {
            row = rand() % boardSize; // 랜덤 '행' 생성
            col = rand() % boardSize; // 랜덤 '열' 생성
        } while (board[row][col] != '~'); 
        board[row][col] = 'S'; // 배 배치
    }
}

// 추측한 배의 범위가 유효한지를 확인하는 함수
int isValidGuess(int row, int col, int boardSize) {
    return (row >= 0 && row < boardSize && col >= 0 && col < boardSize); // 유효하면 1, 유효하지 않으면 0 반환
}

// 모든 배가 격추되었는지를 확인하는 함수
int hasWon(char board[][boardSize], int boardSize) {
    int i, j;
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardSize; j++) {
            if (board[i][j] == 'S' || board[i][j] == 'H') {
                return 0; // 보드판에 배가 남아있다면 0을 반환
            }
        }
    }
    return 1; // 보드판에 배가 없다면 1을 반환(승리)
}



// Player의 추측을 처리하는 함수
void processGuess(char board[][boardSize], int boardSize, int player) {
    int guessRow, guessCol;
    
    printBoard(board, boardSize); // 보드판 출력
    
    printf("Player %d, enter your guess! (row column): ", player);
    while (scanf("%d %d", &guessRow, &guessCol) != 2 || !isValidGuess(guessRow, guessCol, boardSize) || getchar() != '\n') { // 유효하지 않는 입력을 받으면 버퍼를 비우는 작업
        while (getchar() != '\n'); 
        printf("Invalid guess! Please enter valid coordinates\n");
        printf("Player %d, enter your guess! (row column): ", player);
    }

    char cell = board[guessRow][guessCol]; 
    if (cell == 'S') { // cell이 배일 경우
        printf("Player %d hit a ship!\n", player);
        Beep(_B,100);
        board[guessRow][guessCol] = 'H'; // cell을 'H'로 변경하여 배를 맞췄음을 표시
    } else if (cell == 'H') { // cell이 이미 맞춘 배일 경우
        printf("Player %d, Congratulations! You destroyed a ship!\n", player);
        if (player == 0) { // Player0이 배를 찾으면(싱글플레이 모드)
            findShipcnt1++;
            remainShips1--;
        } else if(player == 1) { // Player1이 배를 찾으면(멀티플레이 모드)
            findShipcnt1++; // Player1이 찾은 배 개수 +1
            remainShips2--; // Player2의 남은 배 개수 -1
        } else { // Player2가 배를 찾으면(멀티플레이 모드)
            findShipcnt2++; // Player2가 찾은 배 개수 +1 
            remainShips1--; // Player1의 남은 배 개수 -1
        }
        Beep(_B,100);
        board[guessRow][guessCol] = 'O'; // cell을 'O'로 변경하여 배를 파괴했음을 표시
    } else if (cell == '~') { // cell이 빈 칸일 경우
        printf("Player %d missed! Try again!\n", player);
        Beep(_F,100);
        board[guessRow][guessCol] = 'X'; // cell을 'X'로 변경하여 틀렸음을 표시
    } else { // 이미 추측한 위치일 경우
        printf("Player %d, you've already guessed this location. Try again!\n", player);
    }
}
