#include "Function.h"
#include "SinglePlay.h"
#include "MultiPlay.h"

#include <stdio.h>

#define BOARD_SIZE 5 // 게임 보드의 크기 정의
#define SHIPS_COUNT 4 // 게임의 전함 수 정의

//싱글 플레이와 멀티 플레이를 선택하는 함수
void gamemode(){
    int n;
    printf("Select Mode \n");
    printf("1: SiglePlay 2:MultiPlay ");
    scanf("%d",&n);
    if(n==1){
        singleplay();
    }
    else if(n==2){
        multplay();
    }
    else{
        printf("wrong!\n");
        gamemode();
    }
    
}
 
// 보드를 빈 칸으로 초기화하는 함수
void initializeBoard(char board[][BOARD_SIZE]) { // 모두 '~'로 출력함함
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = '~';  // '~'는 빈 칸을 나타냄
        }
    }
}

// 전함 위치를 감추고 보드를 출력하는 함수
void printBoard(char board[][BOARD_SIZE]) {
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == '~' || board[i][j] == 'X' || board[i][j] == 'O') { //전함은 'S'임 
                printf("%c ", board[i][j]);
            } else {
                printf("~ ");  // 전함 위치를 '~'로 감춤 
            }
        }
        printf("\n");
    }
}

// 전함을 보드에 배치하는 함수
void placeShips(char board[][BOARD_SIZE]) { // 숨길 배의 위치를 입력받는 함수
    int i;
    for(i = 0; i < SHIPS_COUNT; i++) {
        int row, col;
        printf("Enter the coordinates for Ship %d(row column): ", i + 1);
        int result = scanf("%d %d", &row, &col); // 2개의 정수를 입력받음
        if(result == 2) { // 2개의 정수가 입력되었을때만 실행
            char check = getchar(); // 입력 버퍼에서 다음 문자를 읽음, 입력의 끝을 확인하기 위함
            if(check != '\n') { // 읽은 문자가 개행 문자('\n')가 아니라면, 즉 추가 입력이 있다면
                printf("Too many inputs. Only enter two numbers. Try again.\n");
                while(getchar() != '\n'); // 입력 버퍼를 비워 더 이상 읽을 문자가 없을 때까지 반복  
                i--; // i를 감소시켜 입력을 다시 받도록 함
                continue; // 다음 반복으로 넘어가지 않고 현재 반복을 재시작
            }
            
            if(row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) {
                if(board[row][col] != '~') {
                    printf("There is already a ship at that location. Try again.\n");
                    i--; // 잘못된 위치 입력 시 다시 입력
                } 
                else{
                    board[row][col] = 'S';
                }
            } 
            else{
                printf("Invalid coordinates. Try again.\n");
                i--; // 범위 밖 좌표 입력 시 다시 입력
            }
        } 
        else{ // 입력받은 데이터가 2개의 정수가 아니면
            printf("Invalid input. You need to enter two numbers. Try again.\n");
            while(getchar() != '\n'); // 나머지 잘못된 입력을 모두 버림
            i--; // i를 감소시켜 입력을 다시 받도록 함
        }
    }
}
// 유효한 추측인지 확인하는 함수
int isValidGuess(int row, int col) {
    return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE);  //보드 사이즈 안에있으면 T리턴 아니면 F리턴
}

// 모든 전함이 격추되었는지 확인하는 함수
int hasWon(char board[][BOARD_SIZE]) {
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 'S') {  
                return 0;  // 아직 격추되지 않은 전함이 하나 이상 남아있음
            }
        }
    }
    return 1;  // 모든 전함이 격추됨
}

