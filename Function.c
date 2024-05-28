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
void placeShips(char board[][BOARD_SIZE]) {
    int i;
    for (i = 0; i < SHIPS_COUNT; i++) { //현재는 4개를 입력받음
        int row, col;  //행,열 
        printf("Enter the coordinates of the battleship%d (row col): ", i + 1);
        scanf("%d %d", &row, &col); // 행, 열 입력 받음음

        if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) { //보드 사이즈 안에 있는 행과 열이면면
            if (board[row][col] != '~') { //이미 전함이 있으면 
                printf("There is already a battleship at that location. Please enter again.\n");
                i--;
            } else { 
                board[row][col] = 'S';  // 'S'는 전함을 나타냄
            }
        } else {  // 보드 사이즈를 넘어서면 
            printf("Invalid coordinates. Please enter again.\n");
            i--;
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

