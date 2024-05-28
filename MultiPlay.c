
#include <stdio.h>
#include "Function.h"
#include "MultiPlay.h"

void multplay(){
    char board1[BOARD_SIZE][BOARD_SIZE]; //1플레이어 보드
    char board2[BOARD_SIZE][BOARD_SIZE]; //2플레이어 보드 
    
    int guessRow1, guessCol1;
    int guessRow2, guessCol2;
     // 게임 보드를 초기화하고 전함을 배치함
   
    initializeBoard(board1); //초기화화
    placeShips(board1); //배치  -> 랜덤 배치 들어오면 추가해줌.
    initializeBoard(board2); //초기화화
    placeShips(board2);

    // 게임 설명 출력
    printf("=== Battleship Game ===\n");
    printf("Guess the location of the battleship on the board.\n");
    printf("Enter row and col numbers from 0 to 4.\n");

    // 게임 루프
    while (!hasWon(board1) && !hasWon(board2)) {  //보드에 전함이 남아있으면
        // 현재 보드 상태 출력
        printf("\n");
        printBoard(board1); //군함을 감춰서 출력력
        printf("\n\n\n");
        printBoard(board2);
        
        
first_player:
        // 사용자의 다음 수를 입력받음
        printf("Player 1: Enter the coordinates you want to guess (row col): ");
        scanf("%d %d", &guessRow1, &guessCol1);  //사용자가 추측하는 군함의 위치치
        if (!isValidGuess(guessRow1, guessCol1)) { //사이즈가 벗어나면
            printf("This is a wrong guess! Please enter valid coordinates.\n");
            goto first_player; //다시 while문의 처음으로 감감
        }
second_player:
        printf("Player 2: Enter the coordinates you want to guess (row col): ");
        scanf("%d %d", &guessRow2, &guessCol2);
        // 사용자의 추측을 유효성 검사함
        if (!isValidGuess(guessRow2, guessCol2)) { //사이즈가 벗어나면   //수정필요요
            printf("This is a wrong guess! Please enter valid coordinates.\n");
            goto second_player; //다시 while문의 처음으로 감감
        }

        // 추측이 전함을 맞췄는지, 실패했는지, 이전에 이미 추측한 위치인지 확인함
        if (board1[guessRow1][guessCol1] == 'S') {
            printf("1p: Congratulations! The battleship has been shot down!\n");
            board1[guessRow1][guessCol1] = 'X';  // 'X'는 맞힌 곳을 나타냄
        } else if (board1[guessRow1][guessCol1] == '~') {
            printf("1p: Failed! Please try again.\n");
            board1[guessRow1][guessCol1] = 'O';  // 'O'는 실패한 곳을 나타냄
        } else {
            printf("1p: The location has already been guessed. Please try again.\n");
        }
        if (board2[guessRow2][guessCol2] == 'S') {
            printf("2p: Congratulations! The battleship has been shot down!\n");
            board2[guessRow2][guessCol2] = 'X';  // 'X'는 맞힌 곳을 나타냄
        } else if (board2[guessRow1][guessCol1] == '~') {
            printf("2p: Failed! Please try again.\n");
            board2[guessRow2][guessCol2] = 'O';  // 'O'는 실패한 곳을 나타냄
        } else {
            printf("2p: The location has already been guessed. Please try again.\n");
        }

        
    }

    // 게임 종료, 최종 보드 상태와 시도 횟수 출력
    printf("\n");
    printf("\n");
    printBoard(board1);
    printf("\n\n\n");
    printBoard(board2);
    
    
    if(hasWon(board1) && hasWon(board2)){
        printf("It's a draw");
    }
    if(hasWon(board1) && !hasWon(board2)){
        printf("p1 wins! congratulations! All battleships have been shot down.");
    }
    if(!hasWon(board1) && hasWon(board2)){
        printf("p2 wins! congratulations! All battleships have been shot down.");
    }

}

