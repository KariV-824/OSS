#include <stdio.h>
#include "Ranking.h"
#include "Function.h"
#include "SinglePlay.h"



void singleplay(){
    char board[BOARD_SIZE][BOARD_SIZE];
    int guessRow, guessCol;
    int attempts = 0;
    int a=0;
     // 게임 보드를 초기화하고 전함을 배치함
    initializeBoard(board); //초기화화
    placeShips(board); //배치  -> 랜덤 배치 들어오면 추가해줌.

    // 게임 설명 출력
    printf("=== Battleship Game ===\n");
    printf("Guess the location of the battleship on the board.\n");
    printf("Enter row and col numbers from 0 to 4.\n");

    // 게임 루프
    while (!hasWon(board)) {  //보드에 전함이 남아있으면
        // 현재 보드 상태 출력
        printf("\n");
        printBoard(board); //군함을 감춰서 출력력

        // 사용자의 다음 수를 입력받음
        printf("Enter the coordinates you want to guess (row col): ");
        scanf("%d %d", &guessRow, &guessCol);  //사용자가 추측하는 군함의 위치치

        // 사용자의 추측을 유효성 검사함
        if (!isValidGuess(guessRow, guessCol)) { //사이즈가 벗어나면
            printf("This is a wrong guess! Please enter valid coordinates.\n");
            continue; //다시 while문의 처음으로 감감
        }

        // 추측이 전함을 맞췄는지, 실패했는지, 이전에 이미 추측한 위치인지 확인함
        if (board[guessRow][guessCol] == 'S') {
            printf("Congratulations! The battleship has been shot down!\n");
            board[guessRow][guessCol] = 'X';  // 'X'는 맞힌 곳을 나타냄
        } else if (board[guessRow][guessCol] == '~') {
            printf("Failed! Please try again.\n");
            board[guessRow][guessCol] = 'O';  // 'O'는 실패한 곳을 나타냄
        } else {
            printf("The location has already been guessed. Please try again.\n");
        }

        attempts++; //시도 횟수 증가
    }

    // 게임 종료, 최종 보드 상태와 시도 횟수 출력
    printf("\n");
    printBoard(board);
    printf("congratulations! All battleships have been shot down. attempts: %d\n", attempts);
    
    rank_input(attempts);
    printf("Would you like to check the ranking table? 1: O 2: X ");
    scanf("%d",&a);
    if(a==1){
        showRanking();
    }
    else if(a==2){
        return;
    }
    else{
        return;
    } 

}
