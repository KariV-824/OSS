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

#define _C 1046.502
#define _D 1108.731
#define _E 1318.510
#define _F 1396.913
#define _G 1567.982
#define _A 1760.000
#define _B 1975.533

typedef struct { // �÷��̾� ���� ����ü ����
    char name[50];
    int attempt;
} Player;

int boardSize = 0;
int shipsCount = 0;
int attempts = 0;

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
    gameMode(); // ���� ��� ����
    return 0;
}

void printHeadUI() {
    printf("\033[0;37m");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("@     BATTLESHIP GAME!     @\n");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
}

void printTailUI(int attempts) {
    printf("\033[0;37m");
    printf("Attempts : %d\n", attempts);
}


void processGuess(char board[][boardSize], int boardSize, int player) {
    int guessRow, guessCol;
    
    printBoard(board, boardSize);
    
    printf("Player %d, enter your guess (row column): ", player);
    while (scanf("%d %d", &guessRow, &guessCol) != 2 || !isValidGuess(guessRow, guessCol, boardSize)) {
        while (getchar() != '\n'); 
        printf("Invalid guess! Please enter valid coordinates\n");
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
        printf("Player %d missed! Try again\n", player);
        Beep(_F,100);
        board[guessRow][guessCol] = 'X';
    } else {
        printf("Player %d, you've already guessed this location. Try again\n", player);
    }
}

void selectDifficulty(int *boardSize, int *shipsCount) {
    int difficulty;

    printf("Select Difficulty\n");
    printf("1: Easy  2: Hard  -->  ");
    scanf("%d", &difficulty);
    while (getchar() != '\n');  // �Է� ���� ����

    if (difficulty == 1) {
        *boardSize = EASY_BOARD_SIZE;
        *shipsCount = EASY_SHIPS_COUNT;
    } else if (difficulty == 2) {
        *boardSize = HARD_BOARD_SIZE;
        *shipsCount = HARD_SHIPS_COUNT;
    } else {
        printf("Invalid input value!\n");
        selectDifficulty(boardSize, shipsCount);
    }
}

void singlePlay(int boardSize, int shipsCount) {
    char board[boardSize][boardSize];
    int guessRow, guessCol;
    int a = 0;
    time_t start, end; // �ð� ������ ���� ����

    initializeBoard(board, boardSize); // �ʱ�ȭ
    placeShipsRandom(board, boardSize, shipsCount); // ���� ��ġ
    printHeadUI();

    time(&start); // ���� ���� �ð� ���
    // ���� ����
    while (!hasWon(board, boardSize)) {  // ���忡 ������ ����������
        processGuess(board, boardSize, 1);
        attempts++; //�õ� Ƚ�� ����
        printTailUI(attempts);
    }

    time(&end); // ���� ���� �ð� ���
    int time_taken = difftime(end, start); // �ɸ� �ð� ���

    // ���� ����, ���� ���� ���¿� �õ� Ƚ�� ���
    printf("\n");
    printBoard(board, boardSize);
    printf("Congratulations! All battleships have been shot down. Attempts: %d\n", attempts);
    printf("Time taken: %d seconds\n", time_taken); // �� �ҿ� �ð� ���
    
    if (boardSize == 5) {
        rank_input_E(attempts);
    } else {
        rank_input_H(attempts);
    }

    printf("Would you like to check the ranking table?(1: Yes  2: No)  -->  ");
    scanf("%d", &a);
    if (a == 1) {
        showRanking(boardSize);
    } else if ( a == 2) {
        return;
    }
}

void multiPlay(int boardSize, int shipsCount) {
    char board1[boardSize][boardSize]; // 1�÷��̾� ����
    char board2[boardSize][boardSize]; // 2�÷��̾� ���� 
    int guessRow1, guessCol1;
    int guessRow2, guessCol2;
    int mode1, mode2; // �� �÷��̾��� ��ġ ���

    // �÷��̾� 1�� ��ġ ��� ����
    printf("Player 1: Choose ship placement mode(1: Manual  2: Random)  -->  ");
    scanf("%d", &mode1);
    initializeBoard(board1, boardSize);

    if (mode1 == 1) {
        placeShips(board1, boardSize, shipsCount);
    } else if (mode1 == 2) {
        placeShipsRandom(board1, boardSize, shipsCount);
    } else {
        printf("Invalid input value!\n");
        multiPlay(boardSize, shipsCount);
    }

    // �÷��̾� 2�� ��ġ ��� ����
    printf("Player 2: Choose ship placement mode(1: Manual  2: Random)  -->  ");
    scanf("%d", &mode2);
    initializeBoard(board2, boardSize);

    if (mode2 == 1) {
        placeShips(board2, boardSize, shipsCount);
    } else if (mode2 == 2) {
        placeShipsRandom(board2, boardSize, shipsCount);
    } else {
        printf("Invalid input value!\n");
        multiPlay(boardSize, shipsCount);       
    }

    // ���� ���� ���
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("@        BATTLESHIP        @\n");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("Guess the location of the battleship on the board\n");
    printf("Enter row and column numbers from 0 to %d\n", boardSize - 1);

    int turn = 1;
    // ���� ����
    while (!hasWon(board1, boardSize) && !hasWon(board2, boardSize)) {  // ���忡 ������ ����������
        if (turn == 1) {
            printf("Player 1's turn: \n");
            processGuess(board1, boardSize, 1);
            if (hasWon(board1, boardSize)) {
                printf("Player 1 wins!\n");
                break;
            }
            turn = 2;
        } else {
            printf("Player 2's turn: \n");
            processGuess(board2, boardSize, 2);
            if (hasWon(board2, boardSize)) {
                printf("Player 2 wins!\n");
                break;
            }
            turn = 1;
        }
    }

    // ���� ����, ���� ���� ���� ��� 
    printf("\n");
    printf("\n");
    printBoard(board1, boardSize);
    printf("\n\n\n");
    printBoard(board2, boardSize);
}

void gameMode() {
    int n;
    
    printf("Select Mode\n");
    printf("1: SinglePlay  2: MultiPlay  -->  ");
    scanf("%d", &n);

    if (n == 1) {
        selectDifficulty(&boardSize, &shipsCount);
        singlePlay(boardSize, shipsCount);
    } else if (n == 2) {
        selectDifficulty(&boardSize, &shipsCount);
        multiPlay(boardSize, shipsCount);
    } else {
        printf("Invaild Select! Try again\n");
        gameMode(); // �߸� �Է½� �ٽ� ��� �����ϵ��� ��.
    }
}

// ���带 �� ĭ���� �ʱ�ȭ�ϴ� �Լ�
void initializeBoard(char board[][boardSize], int boardSize) { // ��� '~'�� �������
    int i, j;
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardSize; j++) {
            board[i][j] = '~'; // '~'�� �� ĭ�� ��Ÿ��
        }
    }
}

// ���� ��ġ�� ���߰� ���带 ����ϴ� �Լ�
void printBoard(char board[][boardSize], int boardSize) {
    int i, j;
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardSize; j++) {
            char cell = board[i][j];
            if (cell == '~') {
                printf("\033[0;34m");
                printf("%c ", cell);
            } else if (cell == 'H') {
                printf("\033[0;33m"); // �����
                printf("%c ", cell);
            } else if (cell == 'O') {
                printf("\033[0;31m");
                printf("%c ", cell);
            } else if (cell == 'X') {
                printf("\033[0;36m");
                printf("%c ", cell);
            } else {
                printf("\033[0;34m");
                printf("~ "); 
            }
        }
        printf("\n");
    }
}

// ������ ���忡 ��ġ�ϴ� �Լ�
void placeShips(char board[][boardSize], int boardSize, int shipsCount) {
    int i;
    for (i = 0; i < shipsCount; i++) {
        int row, col;
        printf("Enter the coordinates for Ship %d(row column): ", i + 1);
        int result = scanf("%d %d", &row, &col); // 2���� ������ �Է¹޾Ƽ� result�� ����
        if (result == 2) { // 2���� ������ �ԷµǾ��� ���� ����
            if (getchar() != '\n') { // 2���� ���� ���Ŀ� �߰� ���ڰ� ���ۿ� �����ִٸ�
                printf("Too many inputs. Only enter two numbers. Try again\n");
                while (getchar() != '\n'); // ���ۿ� ���� ��� ���ڸ� ������ '\n'�� ���� ������ �ݺ�
                i--; // i�� ���ҽ��� �̹� �Է��� ��ȿȭ�ϰ�, �Է��� �ٽ� �޵��� ��
                continue; // for ������ ó������ ���ư� �����
            }

            if (row >= 0 && row < boardSize && col >= 0 && col < boardSize) {
                if (board[row][col] != '~') {
                    printf("There is already a ship at that location. Try again\n");
                    i--; // �߸��� ��ġ �Է� �� �ٽ� �Է�
                } else {
                    board[row][col] = 'S';
                }
            } else {
                printf("Invalid coordinates. Try again\n");
                i--; // ���� �� ��ǥ �Է� �� �ٽ� �Է�
            }
        } else { // �Է¹��� �����Ͱ� 2���� ������ �ƴ϶��
            printf("Invalid input. You need to enter only two numbers. Try again\n");
            while (getchar() != '\n'); // ���ۿ� ���� ��� ���ڸ� ������ '\n'�� ���� ������ �ݺ�
            i--; // i�� ���ҽ��� �̹� �Է��� ��ȿȭ�ϰ�, �Է��� �ٽ� �޵��� ��
        }
    }
}

// ������ ���忡 �������� ��ġ�ϴ� �Լ�
void placeShipsRandom(char board[][boardSize], int boardSize, int shipsCount) {
    int i;
    srand(time(0)); // �õ� ����: rand() �Լ��� ���� ���� ���� �����ϱ� ���� ���� �ð��� �õ�� ���

    for (i = 0; i < shipsCount; i++) {
        int row, col;
        do {
            row = rand() % boardSize; // 0���� boardSize-1 ������ ���� �� �� ����
            col = rand() % boardSize; // 0���� boardSize-1 ������ ���� �� �� ����
        } while (board[row][col] != '~'); // �谡 �̹� �ִ��� Ȯ���ϰ�, �� �ڸ�(~)�� ������ �ݺ�
        board[row][col] = 'S'; // �� ��ġ
    }
}

// ��ȿ�� �������� Ȯ���ϴ� �Լ�
int isValidGuess(int row, int col, int boardSize) {
    return (row >= 0 && row < boardSize && col >= 0 && col < boardSize); // ���� ������ �ȿ� ������ T���� �ƴϸ� F����
}

// ��� ������ ���ߵǾ����� Ȯ���ϴ� �Լ�
int hasWon(char board[][boardSize], int boardSize) {
    int i, j;
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardSize; j++) {
            if (board[i][j] == 'S' || board[i][j] == 'H') {
                return 0; // ���� ���ߵ��� ���� ������ �ϳ� �̻� ��������
            }
        }
    }
    return 1; // ��� ������ ���ߵ�
}

// Easy ��� �÷��̾� ���� �Է� �Լ�
void rank_input_E(int attempt) {
    char player_name[50];

    printf("Game Over. Enter name: ");
    scanf("%s", player_name);

    // �޸��� ����
    FILE* file = fopen("Rank_list_E.txt", "a");
    if (file == NULL) {
        printf("File open error\n");
        return;
    }

    // �̸��� ���� ���Ͽ� �Է�
    fprintf(file, "Player Name: %s\tattempt: %d\n", player_name, attempt);
    fclose(file);
}

// Easy ��� �÷��̾� ���� ���Ͽ��� �б�
int read_attempt_E(Player players[], int max_players) {
    FILE* file = fopen("Rank_list_E.txt", "r");
    if (file == NULL) {
        printf("File open error\n");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "Player Name: %49s\tattempt: %d\n", players[count].name, &players[count].attempt) == 2) { // fscanf�� ��ȯ���� 2�̸� 2���� �� ��� �� �����Դ� �ǹ� 
        count++;
        if (count >= max_players) {
            break;
        }
    }

    fclose(file);
    return count;
}

// Hard ��� �÷��̾� ���� �Է� �Լ�
void rank_input_H(int attempt) {
    char player_name[50];

    printf("Game Over. Enter name: ");
    scanf("%s", player_name);

    // �޸��� ����
    FILE* file = fopen("Rank_list_H.txt", "a");
    if (file == NULL) {
        printf("File open error\n");
        return;
    }

    // �̸��� ���� ���Ͽ� �Է�
    fprintf(file, "Player Name: %s\tattempt: %d\n", player_name, attempt);
    fclose(file);
}

// �÷��̾� ���� ���Ͽ��� �б�
int read_attempt_H(Player players[], int max_players) {
    FILE* file = fopen("Rank_list_H.txt", "r");
    if (file == NULL) {
        printf("File open error\n");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "Player Name: %49s\tattempt: %d\n", players[count].name, &players[count].attempt) == 2) { // fscanf�� ��ȯ���� 2�̸� 2���� �� ��� �� �����Դ� �ǹ� 
        count++;
        if (count >= max_players) {
            break;
        }
    }

    fclose(file);
    return count;
}

// ������ �������� �������� �����ϴ� �Լ�
int compare_attempt(const void* a, const void* b) {
    Player* playerA = (Player*)a;
    Player* playerB = (Player*)b;
    return playerA->attempt - playerB->attempt; // �������� ����
}

// ���ĵ� ��� ��� �Լ�
void print_sorted_attempt(Player players[], int count) {
    int i;
    printf("\n=== Sorted attempt ===\n");
    for (i = 0; i < count; i++) {
        printf("%d Player Name: %s\tattempt: %d\n", i + 1, players[i].name, players[i].attempt);
    }
}

void showRanking(int boardSize) {
    const int MAX_PLAYERS = 100;
    Player players[MAX_PLAYERS];
    int player_count;

    if (boardSize == 5) {
        player_count = read_attempt_E(players, MAX_PLAYERS);
    } else {
        player_count = read_attempt_H(players, MAX_PLAYERS);
    }
    
    qsort(players, player_count, sizeof(Player), compare_attempt); // ���� �������� ����
    print_sorted_attempt(players, player_count); // ���ĵ� ��� ���
}