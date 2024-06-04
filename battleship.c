#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <mmsystem.h>
#include <string.h>
#include <time.h>
#pragma comment (lib, "winmm.lib")

#define EASY_BOARD_SIZE 5   
#define EASY_SHIPS_COUNT 4 
#define HARD_BOARD_SIZE 6
#define HARD_SHIPS_COUNT 7

// ºñÇÁÀ½ Àç»ýÀ» À§ÇÑ À½°è°ª Á¤ÀÇ
#define _C 1046.502
#define _D 1108.731
#define _E 1318.510
#define _F 1396.913
#define _G 1567.982
#define _A 1760.000
#define _B 1975.533

typedef struct {
    char name[50];
    int attempt;
} Player;

int boardSize = 0;
int shipsCount = 0;
int attempts = 0;
int attempts1 = 0;
int attempts2 = 0;
int remainShips1 = 0;
int remainShips2 = 0;
int findShipcnt1 = 0;
int findShipcnt2 = 0;

void printHeadUI();
void printSingleTailUI(int attempts, int remain, int find);
void printMultiTailUI(int attempts1, int attempts2, int remain1, int remain2, int find1, int find2);
void processGuess(char board[][boardSize], int boardSize, int player);
void selectDifficulty(int* boardSize, int* shipsCount);
void singlePlay(int boardSize, int shipsCount);
void multiPlay(int boardSize, int shipsCount);
void gameMode();
void initializeBoard(char board[][boardSize], int boardSize);
void printBoard(char board[][boardSize], int boardSize);
void placeShips(char board[][boardSize], int boardSize, int shipsCount);
void placeShipsRandom(char board[][boardSize], int boardSize, int shipsCount);
int isValidGuess(int row, int col, int boardSize);
int hasWon(char board[][boardSize], int boardSize);
void rank_input_E(int attempt);
int read_attempt_E(Player players[], int max_players);
void rank_input_H(int attempt);
int read_attempt_H(Player players[], int max_players);
int compare_attempt(const void* a, const void* b);
void print_sorted_attempt(Player players[], int count);
void showRanking(int boardSize);

int main() {
    gameMode(); // °ÔÀÓ ¸ðµå ¼±ÅÃ
    return 0;
}

// °ÔÀÓ ÀÌ¸§À» Ãâ·ÂÇÏ´Â ÇÔ¼ö
void printHeadUI() {
    printf("\033[0;37m");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("@      BATTLESHIP GAME!    @\n");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
}

// ½Ì±ÛÇÃ·¹ÀÌ ¸ðµå¿¡¼­ ½Ãµµ È½¼ö, ³²Àº ¹è °³¼ö, Ã£Àº ¹è °³¼ö¸¦ Ãâ·ÂÇÏ´Â ÇÔ¼ö
void printSingleTailUI(int attempts, int remain, int find) { 
    printf("\033[0;37m");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("               Attempts : %d               \n", attempts);
    printf("                Remain : %d                \n", remain);
    printf("                 Find :  %d                \n", find);
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
}

// ¸ÖÆ¼ÇÃ·¹ÀÌ ¸ðµå¿¡¼­ Playerº° ½Ãµµ È½¼ö, ³²Àº ¹è °³¼ö, Ã£Àº ¹è °³¼ö¸¦ Ãâ·ÂÇÏ´Â ÇÔ¼ö
void printMultiTailUI(int attempts1, int attempts2, int remain1, int remain2, int find1, int find2) {
    printf("\033[0;37m");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("   P1 Attempts : %d    P2 Attempts : %d   \n", attempts1, attempts2);
    printf("    P1 Remain : %d       P2 Remain : %d    \n", remain1, remain2);
    printf("     P1 Find : %d         P2 Find : %d     \n", find1, find2);
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
}

// PlayerÀÇ ÃßÃøÀ» Ã³¸®ÇÏ´Â ÇÔ¼ö
void processGuess(char board[][boardSize], int boardSize, int player) {
    int guessRow, guessCol;
    
    printBoard(board, boardSize); // º¸µåÆÇ Ãâ·Â
    
    printf("Player %d, enter your guess! (row column): ", player);
    while (scanf("%d %d", &guessRow, &guessCol) != 2 || !isValidGuess(guessRow, guessCol, boardSize) || getchar() != '\n') { // À¯È¿ÇÏÁö ¾Ê´Â ÀÔ·ÂÀ» ¹ÞÀ¸¸é ¹öÆÛ¸¦ ºñ¿ì´Â ÀÛ¾÷
        while (getchar() != '\n'); 
        printf("Invalid guess! Please enter valid coordinates\n");
        printf("Player %d, enter your guess! (row column): ", player);
    }

    char cell = board[guessRow][guessCol]; 
    if (cell == 'S') { // cellÀÌ ¹èÀÏ °æ¿ì
        printf("Player %d hit a ship!\n", player);
        Beep(_B,100);
        board[guessRow][guessCol] = 'H'; // cellÀ» 'H'·Î º¯°æÇÏ¿© ¹è¸¦ ¸ÂÃèÀ½À» Ç¥½Ã
    } else if (cell == 'H') { // cellÀÌ ÀÌ¹Ì ¸ÂÃá ¹èÀÏ °æ¿ì
        printf("Player %d, Congratulations! You destroyed a ship!\n", player);
        if (player == 0) { // Player0ÀÌ ¹è¸¦ Ã£À¸¸é(½Ì±ÛÇÃ·¹ÀÌ ¸ðµå)
            findShipcnt1++;
            remainShips1--;
        } else if(player == 1) { // Player1ÀÌ ¹è¸¦ Ã£À¸¸é(¸ÖÆ¼ÇÃ·¹ÀÌ ¸ðµå)
            findShipcnt1++; // Player1ÀÌ Ã£Àº ¹è °³¼ö +1
            remainShips2--; // Player2ÀÇ ³²Àº ¹è °³¼ö -1
        } else { // Player2°¡ ¹è¸¦ Ã£À¸¸é(¸ÖÆ¼ÇÃ·¹ÀÌ ¸ðµå)
            findShipcnt2++; // Player2°¡ Ã£Àº ¹è °³¼ö +1 
            remainShips1--; // Player1ÀÇ ³²Àº ¹è °³¼ö -1
        }
        Beep(_B,100);
        board[guessRow][guessCol] = 'O'; // cellÀ» 'O'·Î º¯°æÇÏ¿© ¹è¸¦ ÆÄ±«ÇßÀ½À» Ç¥½Ã
    } else if (cell == '~') { // cellÀÌ ºó Ä­ÀÏ °æ¿ì
        printf("Player %d missed! Try again!\n", player);
        Beep(_F,100);
        board[guessRow][guessCol] = 'X'; // cellÀ» 'X'·Î º¯°æÇÏ¿© Æ²·ÈÀ½À» Ç¥½Ã
    } else { // ÀÌ¹Ì ÃßÃøÇÑ À§Ä¡ÀÏ °æ¿ì
        printf("Player %d, you've already guessed this location. Try again!\n", player);
    }
}

// °ÔÀÓ ³­ÀÌµµ¸¦ ¼±ÅÃÇÏ´Â ÇÔ¼ö
void selectDifficulty(int *boardSize, int *shipsCount) {
    int difficulty;

    printf("Select Difficulty\n");
    printf("1: Easy  2: Hard  -->  ");
    scanf("%d", &difficulty);
    while (getchar() != '\n'); 

    if (difficulty == 1) { // Easy ³­ÀÌµµ¸¦ ¼±ÅÃÇÑ °æ¿ì
        *boardSize = EASY_BOARD_SIZE;
        *shipsCount = EASY_SHIPS_COUNT;
        remainShips1 = EASY_SHIPS_COUNT;
        remainShips2 = EASY_SHIPS_COUNT;
    } else if (difficulty == 2) { // Hard ³­ÀÌµµ¸¦ ¼±ÅÃÇÑ °æ¿ì
        *boardSize = HARD_BOARD_SIZE;
        *shipsCount = HARD_SHIPS_COUNT;
        remainShips1 = HARD_SHIPS_COUNT;
        remainShips2 = HARD_SHIPS_COUNT;
    } else {
        printf("Invalid input value!\n");
        selectDifficulty(boardSize, shipsCount); // ÇÔ¼ö ÀçÈ£Ãâ·Î ³­ÀÌµµ Àç¼±ÅÃ
    }
}

// ½Ì±ÛÇÃ·¹ÀÌ ¸ðµå ÇÔ¼ö
void singlePlay(int boardSize, int shipsCount) {
    char board[boardSize][boardSize];
    int guessRow, guessCol;
    int a = 0;
    time_t start, end; 

    initializeBoard(board, boardSize); // º¸µå ÃÊ±âÈ­ ÀÛ¾÷
    placeShipsRandom(board, boardSize, shipsCount); // ¹è ·£´ý¹èÄ¡ ÀÛ¾÷
    printHeadUI(); // HeadUI Ãâ·Â

    time(&start); // °ÔÀÓ ½ÃÀÛ ½Ã°£ ±â·Ï
    
    while (!hasWon(board, boardSize)) {  // º¸µå¿¡ ¹è°¡ ³²¾ÆÀÖÁö ¾ÊÀ» ¶§±îÁö
        processGuess(board, boardSize, 0); // ¹èÀÇ À§Ä¡¸¦ ÃßÃø
        attempts++; 
        printSingleTailUI(attempts, remainShips1, findShipcnt1); // ÇÑ¹ø ÃßÃøÇÒ¶§¸¶´Ù TailUI Ãâ·Â
    }

    time(&end); // °ÔÀÓ Á¾·á ½Ã°£ ±â·Ï
    int time_taken = difftime(end, start); // °É¸° ½Ã°£ °è»ê

    printf("\n");
    printBoard(board, boardSize); // º¸µåÆÇ Ãâ·Â
    printf("Congratulations! All battleships have been shot down. Attempts: %d\n", attempts);
    printf("Time taken: %d seconds\n", time_taken); 
    if (boardSize == 5) { // º¸µå»çÀÌÁî¿¡ µû¶ó °¢°¢ ´Ù¸¥ ·©Å·Ç¥¸¦ Ç¥½Ã
        rank_input_E(attempts); // Easy¸ðµå ·©Å·Ç¥
    } else {
        rank_input_H(attempts); // Hard¸ðµå ·©Å·Ç¥
    } 

    while (1) {
        printf("Would you like to check the ranking table?(1: Yes  2: No)  -->  ");
        scanf("%d", &a);
        while(getchar() != '\n');
        if (a == 1) {
            showRanking(boardSize); // ·©Å· Ãâ·Â
            break;
        } else if (a == 2) {
            return;
        } else {
            printf("Invalid Select. Try again!\n");
        }
    }
}

// ¸ÖÆ¼ÇÃ·¹ÀÌ ¸ðµå ÇÔ¼ö
void multiPlay(int boardSize, int shipsCount) {
    char board1[boardSize][boardSize];
    char board2[boardSize][boardSize];
    int guessRow1, guessCol1;
    int guessRow2, guessCol2;
    int mode1, mode2; 

    while (1) {
        printf("Player 1: Choose ship placement mode(1: Manual  2: Random)  -->  "); 
        scanf("%d", &mode1);
        while(getchar() != '\n');

        initializeBoard(board1, boardSize); // º¸µå1 ÃÊ±âÈ­ ÀÛ¾÷

        if (mode1 == 1) { // Player1ÀÌ ¹èÀÇ À§Ä¡¸¦ Á÷Á¢ ¼±ÅÃÇÏ´Â °æ¿ì
            placeShips(board1, boardSize, shipsCount); // Player1ÀÇ ¹è ¼öµ¿¹èÄ¡ ÀÛ¾÷
            break;
        } else if (mode1 == 2) { // ÀÚµ¿À¸·Î ¹èÀÇ À§Ä¡¸¦ ¼±ÅÃÇÏ´Â °æ¿ì
            placeShipsRandom(board1, boardSize, shipsCount); // º¸µå1ÀÇ ¹è ·£´ý¹èÄ¡ ÀÛ¾÷
            break;
        } else {
            printf("Invalid input value! Please try again!\n");
        }
    }

    while (1) {
        printf("Player 2: Choose ship placement mode(1: Manual  2: Random)  -->  ");
        scanf("%d", &mode2);
        while(getchar() != '\n'); 

        initializeBoard(board2, boardSize); // º¸µå2 ÃÊ±âÈ­ ÀÛ¾÷

        if (mode2 == 1) { // Player2°¡ ¹èÀÇ À§Ä¡¸¦ Á÷Á¢ ¼±ÅÃÇÏ´Â °æ¿ì
            placeShips(board2, boardSize, shipsCount); // Player2ÀÇ ¹è ¼öµ¿¹èÄ¡ ÀÛ¾÷
            break;
        } else if (mode2 == 2) { // ÀÚµ¿À¸·Î ¹èÀÇ À§Ä¡¸¦ ¼±ÅÃÇÏ´Â °æ¿ì
            placeShipsRandom(board2, boardSize, shipsCount); // º¸µå2ÀÇ ¹è ·£´ý¹èÄ¡ ÀÛ¾÷
            break;
        } else {
            printf("Invalid input value! Please try again!\n");
        }
    }

    printHeadUI(); // HeadUI Ãâ·Â
    printf("Guess the location of the battleship on the board!\n");
    printf("Enter row and column numbers from 0 to %d\n", boardSize - 1);

    int turn = 1;

    while (!hasWon(board1, boardSize) && !hasWon(board2, boardSize)) {  // µÎ º¸µå Áß ¾î´À ÇÑÂÊ¿¡¼­µµ ½Â¸® Á¶°ÇÀÌ ¸¸Á·µÇÁö ¾ÊÀ» ¶§±îÁö
        if (turn == 1) {
            printf("Player 1's turn: \n");
            processGuess(board1, boardSize, 1); // º¸µå1ÀÇ ¹è À§Ä¡¸¦ ÃßÃø
            attempts1++; 
            printMultiTailUI(attempts1, attempts2, remainShips1, remainShips2, findShipcnt1, findShipcnt2); // ÇÑ¹ø ÃßÃøÇÒ¶§¸¶´Ù TailUI Ãâ·Â
            if (hasWon(board1, boardSize)) { // ¸¸¾à Player1ÀÌ ¹è¸¦ ¸ðµÎ Ã£¾Ò´Ù¸é
                printf("Player 1 wins!\n");
                break;
            }
            turn = 2; 
        } else {
            printf("Player 2's turn: \n");
            processGuess(board2, boardSize, 2); // º¸µå2ÀÇ ¹è À§Ä¡¸¦ ÃßÃø
            attempts2++; 
            printMultiTailUI(attempts1, attempts2, remainShips1, remainShips2, findShipcnt1, findShipcnt2); // ÇÑ¹ø ÃßÃøÇÒ¶§¸¶´Ù TailUI Ãâ·Â
            if (hasWon(board2, boardSize)) { // ¸¸¾à Player2°¡ ¹è¸¦ ¸ðµÎ Ã£¾Ò´Ù¸é
                printf("Player 2 wins!\n");
                break;
            }
            turn = 1;
        }
    }
 
    printf("\n");
    printf("\n");
    printBoard(board1, boardSize); // º¸µåÆÇ1 Ãâ·Â
    printf("\n\n\n");
    printBoard(board2, boardSize); // º¸µåÆÇ2 Ãâ·Â
}

// °ÔÀÓ ¸ðµå¸¦ ¼±ÅÃÇÏ´Â ÇÔ¼ö
void gameMode() {
    int n;
    
    printf("Select Mode\n");
    printf("1: SinglePlay  2: MultiPlay  -->  ");
    scanf("%d", &n);
    while(getchar() != '\n');

<<<<<<< HEAD
    
    if (n == 1) {
        selectDifficulty(&boardSize, &shipsCount);
        singleplay(boardSize, shipsCount);
    } else if (n == 2) {
        selectDifficulty(&boardSize, &shipsCount);
        multplay(boardSize, shipsCount);
    } else {
        printf("wrong!\n");
        gamemode(); // ìž˜ëª» ìž…ë ¥ì‹œ ë‹¤ì‹œ ëª¨ë“œ ì„ íƒí•˜ë„ë¡ í•¨.
=======
    if (n == 1) { // ½Ì±ÛÇÃ·¹ÀÌ ¸ðµå ¼±ÅÃ½Ã
        selectDifficulty(&boardSize, &shipsCount); // ³­ÀÌµµ ¼±ÅÃ
        singlePlay(boardSize, shipsCount); // ½Ì±ÛÇÃ·¹ÀÌ ¸ðµå ½ÃÀÛ
    } else if (n == 2) { // ¸ÖÆ¼ÇÃ·¹ÀÌ ¸ðµå ¼±ÅÃ½Ã
        selectDifficulty(&boardSize, &shipsCount); // ³­ÀÌµµ ¼±ÅÃ
        multiPlay(boardSize, shipsCount); // ¸ÖÆ¼ÇÃ·¹ÀÌ ¸ðµå ½ÃÀÛ
    } else { 
        printf("Invalid Select. Try again!\n");
        gameMode(); // ÇÔ¼ö ÀçÈ£Ãâ·Î °ÔÀÓ ¸ðµå Àç¼±ÅÃ
>>>>>>> 5ec28dbd355eab9e17897992cfbd79251e7f31f2
    }
}

// º¸µå¸¦ ÃÊ±âÈ­ÇÏ´Â ÇÔ¼ö
void initializeBoard(char board[][boardSize], int boardSize) {
    int i, j;
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardSize; j++) {
            board[i][j] = '~'; // ¸ðµç º¸µåÄ­À» ÃÊ±âÈ­
        }
    }
}

// º¸µå¸¦ Ãâ·ÂÇÏ´Â ÇÔ¼ö
void printBoard(char board[][boardSize], int boardSize) {
    int i, j;
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardSize; j++) {
            char cell = board[i][j];
            if (cell == '~') { // cellÀÌ ºó Ä­ÀÏ °æ¿ì
                printf("\033[0;34m"); // ÆÄ¶õ»ö
                printf("%c ", cell);
                printf("\033[0;37m"); // ±âº»»ö
            } else if (cell == 'H') { // cellÀÌ ÀÌ¹Ì ¸ÂÃá ¹èÀÏ °æ¿ì
                printf("\033[0;33m"); // ³ë¶õ»ö
                printf("%c ", cell);
                printf("\033[0;37m"); // ±âº»»ö
            } else if (cell == 'O') { // cellÀÌ ¹èÀÏ °æ¿ì
                printf("\033[0;31m"); // »¡°£»ö
                printf("%c ", cell);
                printf("\033[0;37m"); // ±âº»»ö
            } else if (cell == 'X') { // cellÀÌ ºñ¾î ÀÖÀ» °æ¿ì
                printf("\033[0;36m"); // ÃÊ·Ï»ö
                printf("%c ", cell);
                printf("\033[0;37m"); // ±âº»»ö
            } else {
                printf("\033[0;34m"); // ÆÄ¶õ»ö
                printf("~ ");
                printf("\033[0;37m"); // ±âº»»ö
            }
        }
        printf("\n");
    }
}

// ¹è¸¦ º¸µå¿¡ ¹èÄ¡ÇÏ´Â ÇÔ¼ö
void placeShips(char board[][boardSize], int boardSize, int shipsCount) {
    int i;
    for (i = 0; i < shipsCount; i++) {
        int row, col;
        printf("Enter the coordinates for Ship %d(row column): ", i + 1);
        int result = scanf("%d %d", &row, &col); 
        if (result == 2) { // 2°³ÀÇ Á¤¼ö°¡ ÀÔ·ÂµÇ¾úÀ» ¶§¸¸ ½ÇÇà
            if (getchar() != '\n') { 
                printf("Too many inputs. Only enter two numbers. Try again!\n");
                while (getchar() != '\n'); 
                i--; // ÀÌ¹ø ÀÔ·ÂÀ» ¹«È¿È­ÇÏ°í, ÀÔ·ÂÀ» ´Ù½Ã ¹Þµµ·Ï ÇÔ
                continue; 
            }

            if (row >= 0 && row < boardSize && col >= 0 && col < boardSize) {
                if (board[row][col] != '~') {
                    printf("There is already a ship at that location. Try again!\n");
                    i--; // Àß¸øµÈ À§Ä¡ ÀÔ·Â ½Ã, ÀÔ·ÂÀ» ´Ù½Ã ¹Þµµ·Ï ÇÔ
                } else {
                    board[row][col] = 'S';
                }
            } else {
                printf("Invalid coordinates. Try again!\n");
                i--; // ¹üÀ§ ¹ÛÀÇ ÁÂÇ¥ ÀÔ·Â ½Ã, ÀÔ·ÂÀ» ´Ù½Ã ¹Þµµ·Ï ÇÔ
            }
        } else { // ÀÔ·Â¹ÞÀº µ¥ÀÌÅÍ°¡ 2°³ÀÇ Á¤¼ö°¡ ¾Æ´Ï¶ó¸é
            printf("Invalid input. You need to enter two numbers. Try again!\n");
            while (getchar() != '\n'); 
            i--; // ÀÌ¹ø ÀÔ·ÂÀ» ¹«È¿È­ÇÏ°í, ÀÔ·ÂÀ» ´Ù½Ã ¹Þµµ·Ï ÇÔ
        }
    }
}

// ¹è¸¦ º¸µå¿¡ ·£´ýÀ¸·Î ¹èÄ¡ÇÏ´Â ÇÔ¼ö
void placeShipsRandom(char board[][boardSize], int boardSize, int shipsCount) {
    int i;
    srand(time(0)); // rand() ÇÔ¼öÀÇ ³­¼ö »ý¼ºÀ» À§ÇØ ÇöÀç ½Ã°£À» ½Ãµå·Î ¼³Á¤

    for (i = 0; i < shipsCount; i++) {
        int row, col;
        do {
            row = rand() % boardSize; // ·£´ý 'Çà' »ý¼º
            col = rand() % boardSize; // ·£´ý '¿­' »ý¼º
        } while (board[row][col] != '~'); 
        board[row][col] = 'S'; // ¹è ¹èÄ¡
    }
}

// ÃßÃøÇÑ ¹èÀÇ ¹üÀ§°¡ À¯È¿ÇÑÁö¸¦ È®ÀÎÇÏ´Â ÇÔ¼ö
int isValidGuess(int row, int col, int boardSize) {
    return (row >= 0 && row < boardSize && col >= 0 && col < boardSize); // À¯È¿ÇÏ¸é 1, À¯È¿ÇÏÁö ¾ÊÀ¸¸é 0 ¹ÝÈ¯
}

// ¸ðµç ¹è°¡ °ÝÃßµÇ¾ú´ÂÁö¸¦ È®ÀÎÇÏ´Â ÇÔ¼ö
int hasWon(char board[][boardSize], int boardSize) {
    int i, j;
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardSize; j++) {
            if (board[i][j] == 'S' || board[i][j] == 'H') {
                return 0; // º¸µåÆÇ¿¡ ¹è°¡ ³²¾ÆÀÖ´Ù¸é 0À» ¹ÝÈ¯
            }
        }
    }
    return 1; // º¸µåÆÇ¿¡ ¹è°¡ ¾ø´Ù¸é 1À» ¹ÝÈ¯(½Â¸®)
}

// Easy¸ðµåÀÇ ·©Å·Ç¥ ÀÔ·Â ÇÔ¼ö
void rank_input_E(int attempt) {
    char player_name[50];

    printf("Game Over. Enter name: ");
    scanf("%s", player_name);


    FILE* file = fopen("Rank_list_E.txt", "a"); // Rank_list_E.txt¸¦ ¾²±â Àü¿ëÀ¸·Î open
    if (file == NULL) {
        printf("File open error\n");
        return;
    }

    fprintf(file, "Player Name: %s\tattempt: %d\n", player_name, attempt); // Player ÀÌ¸§°ú ½Ãµµ È½¼ö¸¦ ÆÄÀÏ¿¡ ÀúÀå
    fclose(file); 
}

// Easy¸ðµå ÆÄÀÏÀ» ÀÐ¾î¼­ ±¸Á¶Ã¼ ¹è¿­¿¡ ÀúÀåÇÏ´Â ÇÔ¼ö
int read_attempt_E(Player players[], int max_players) {
    FILE* file = fopen("Rank_list_E.txt", "r");  // Rank_list_E.txt¸¦ ÀÐ±â Àü¿ëÀ¸·Î open
    if (file == NULL) {
        printf("File open error\n");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "Player Name: %49s\tattempt: %d\n", players[count].name, &players[count].attempt) == 2) { // fscanf¸¦ ÅëÇØ °ªÀ» ¸ðµÎ ÀÐ¾î¿À¸é °ªÀÌ 2°³ÀÌ¹Ç·Î 2¸¦ ¹ÝÈ¯
        count++; // ¹è¿­ÀÇ ´ÙÀ½ ÀÎµ¦½º·Î ³Ñ¾î°¨
        if (count >= max_players) {
            break;
        }
    }

    fclose(file);
    return count;
}

// Hard¸ðµåÀÇ ·©Å·Ç¥ ÀÔ·Â ÇÔ¼ö
void rank_input_H(int attempt) {
    char player_name[50];

    printf("Game Over! Enter name: ");
    scanf("%s", player_name);

    FILE* file = fopen("Rank_list_H.txt", "a"); // Rank_list_H.txt¸¦ ¾²±â Àü¿ëÀ¸·Î open
    if (file == NULL) {
        printf("File open error\n");
        return;
    }

    fprintf(file, "Player Name: %s\tattempt: %d\n", player_name, attempt); // Player ÀÌ¸§°ú ½Ãµµ È½¼ö¸¦ ÆÄÀÏ¿¡ ÀúÀå
    fclose(file);
}

// Hard¸ðµå ÆÄÀÏÀ» ÀÐ¾î¼­ ±¸Á¶Ã¼ ¹è¿­¿¡ ÀúÀåÇÏ´Â ÇÔ¼ö
int read_attempt_H(Player players[], int max_players) {
    FILE* file = fopen("Rank_list_H.txt", "r"); // Rank_list_H.txt¸¦ ÀÐ±â Àü¿ëÀ¸·Î open
    if (file == NULL) {
        printf("File open error\n");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "Player Name: %49s\tattempt: %d\n", players[count].name, &players[count].attempt) == 2) { // fscanf¸¦ ÅëÇØ °ªÀ» ¸ðµÎ ÀÐ¾î¿À¸é °ªÀÌ 2°³ÀÌ¹Ç·Î 2¸¦ ¹ÝÈ¯
        count++; // ¹è¿­ÀÇ ´ÙÀ½ ÀÎµ¦½º·Î ³Ñ¾î°¨
        if (count >= max_players) {
            break;
        }
    }

    fclose(file);
    return count;
}

// ¿À¸§Â÷¼øÀ¸·Î Á¤·ÄÇÏ±â À§ÇÑ ºñ±³ ÇÔ¼ö
int compare_attempt(const void* a, const void* b) {
    Player* playerA = (Player*)a; // Ã¹ ¹øÂ° ¸Å°³º¯¼ö¸¦ Player ±¸Á¶Ã¼ Æ÷ÀÎÅÍ·Î Çü º¯È¯
    Player* playerB = (Player*)b; // µÎ ¹øÂ° ¸Å°³º¯¼ö¸¦ Player ±¸Á¶Ã¼ Æ÷ÀÎÅÍ·Î Çü º¯È¯
    return playerA->attempt - playerB->attempt; // µÎ PlayerÀÇ ½Ãµµ È½¼ö Â÷ÀÌ¸¦ ¹ÝÈ¯
}

// ·©Å·Ç¥ Ãâ·Â ÇÔ¼ö
void print_sorted_attempt(Player players[], int count) {
    int i;
    printf("\n======= Sorted attempt =======\n");
    for (i = 0; i < count; i++) {
        printf("%d Player Name: %s\tattempt: %d\n", i + 1, players[i].name, players[i].attempt);
    }
}

// ·©Å·À» º¸¿©ÁÖ±â À§ÇÑ ÇÔ¼ö
void showRanking(int boardSize) {
    const int MAX_PLAYERS = 100;
    Player players[MAX_PLAYERS];
    int player_count;

    if (boardSize == 5) { // º¸µå »çÀÌÁî¿¡ µû¶ó ³­ÀÌµµ¿¡ ¸Â´Â ÆÄÀÏÀ» ¿­¾î ·©Å·Ç¥ Ãâ·Â
        player_count = read_attempt_E(players, MAX_PLAYERS); // Easy¸ðµå ·©Å·Ç¥
    } else {
        player_count = read_attempt_H(players, MAX_PLAYERS); // Hard¸ðµå ·©Å·Ç¥
    }
    
    qsort(players, player_count, sizeof(Player), compare_attempt); // players ¹è¿­À» compare_attempt ºñ±³ ÇÔ¼ö¸¦ »ç¿ëÇÏ¿© ¿À¸§Â÷¼øÀ¸·Î Á¤·Ä
    print_sorted_attempt(players, player_count); // Á¤·ÄµÈ ·©Å·Ç¥¸¦ Ãâ·Â
}