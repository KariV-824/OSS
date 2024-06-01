//by ?scar Poblete S?enz
#include <stdio.h>
#define BOARD_SIZE 5 // 보드 크기 정의
#define SHIPS_COUNT 4 // 배의 수 정의
void initializeBoard(char board[][BOARD_SIZE]) { // 초기화된 보드판을 생성하는 함수, 2차원 문자 배열을 매개변수로 받음
    int i, j;
    for(i = 0; i < BOARD_SIZE; i++) {
        for(j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = '~'; // 기본 세팅값을 전부 '~'로 초기화
        }
    }
}
void printBoard(char board[][BOARD_SIZE]) { // 보드판의 상태를 출력하는 함수
    int i, j;
    for(i = 0; i < BOARD_SIZE; i++) {
        for(j = 0; j < BOARD_SIZE; j++) {
            if(board[i][j] == '~' || board[i][j] == 'O' || board[i][j] == 'X') { 
                printf
                ("%c", board[i][j]); 
            } 
            else{ 
                printf("~ "); // 해당 자리가 S이면 '~'를 표시해서 숨김
            }
        }
        printf("\n");
    }
}
void placeShips(char board[][BOARD_SIZE]) {// 숨길 배의 위치를 입력받는 함수
    int i;
    for(i = 0; i < SHIPS_COUNT; i++) {
        int row, col;
        printf("Enter the coordinates for Ship %d(row column): ", i + 1);
        int result = scanf("%d %d", &row, &col); // 2개의 정수를 입력받아서 result에 저장
        if(result == 2) { // 2개의 정수가 입력되었을때만 실행
            if(getchar() != '\n') { // 2개의 정수 이후에 추가 문자가 버퍼에 남아있다면
                printf("Too many inputs. Only enter two numbers. Try again.\n"); 
                while(getchar() != '\n'); // 버퍼에 남은 모든 문자를 버리며 '\n'를 만날 때까지 반복  
                i--; // i를 감소시켜 이번 입력을 무효화하고, 입력을 다시 받도록 함
                continue; // for 루프의 처음으로 돌아가 재시작
            }
            
            if(row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) {
                if(board[row][col] != '~') {
                    printf("There is already a ship at that location. Try again.\n");
                    i--;// 잘못된 위치 입력 시 다시 입력
                } 
                else{
                    board[row][col] = 'S';
                }
            } 
            else{
                printf("Invalid coordinates. Try again.\n");
                i--;// 범위 밖 좌표 입력 시 다시 입력
            }
        } 
        else{ // 입력받은 데이터가 2개의 정수가 아니라면
            printf("Invalid input. You need to enter two numbers. Try again.\n");
            while(getchar() != '\n'); // 버퍼에 남은 모든 문자를 버리며 '\n'를 만날 때까지 반복
            i--; // i를 감소시켜 이번 입력을 무효화하고, 입력을 다시 받도록 함
        }
    }
}
int isValidGuess(int row, int col) { // 추측한 배의 범위가 유효한지를 확인하는 함수, int타입의 row, col 인자를 받음
    return(row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE); // 유효하면 1, 유효하지 않으면 0 반환
}
int hasWon(char board[][BOARD_SIZE]) { // 모든 배가 격추되었는지를 확인하는 함수
    int i, j;
    for(i = 0; i < BOARD_SIZE; i++) {
        for(j = 0; j < BOARD_SIZE; j++) {
            if(board[i][j] == 'S') { 
                return 0; // 보드판에 배가 남아있다면 0을 반환
            }
        }
    }
    return 1; // 보드판에 배가 없다면 1을 반환(승리)
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
    while(!hasWon(board)) { // hasWon함수가 0을 반환하는 동안(보드판에 배가 남아있는 동안) 반복
        printf("\n");
        printBoard(board);
        printf("Enter your guess (row column): ");
        scanf("%d %d", &guessRow, &guessCol);
        if(!isValidGuess(guessRow, guessCol)) { // isValidGuess함수가 0을 반환하면
            printf("Invalid guess! Please enter valid coordinates.\n");
            continue; // while문의 처음으로 넘어감
        }
        if(board[guessRow][guessCol] == 'S') {
            printf("Congratulations! You hit a ship!\n");
            board[guessRow][guessCol] = 'O'; // 맞추면 'S'에서 'O'로 변경
        } 
        else if(board[guessRow][guessCol] == '~') {
            printf("Missed! Try again.\n");
            board[guessRow][guessCol] = 'X'; // 틀리면 '~'에서 'X'로 변경
        } 
        else{
            printf("You've already guessed this location. Try again.\n"); 
        }
        attempts++;
    }
    printf("\n");
    printBoard(board);
    printf("Congratulations! You sunk all the ships in %dattempts.\n", attempts);
    return 0;
}