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

// ������ ����� ���� ���谪 ����
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
    gameMode();  // ���� ��� ����
    return 0;
}

// ���� �̸��� ����ϴ� �Լ�
void printHeadUI() {
    printf("\033[0;37m");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("@      BATTLESHIP GAME!    @\n");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
}

// �̱��÷��� ��忡�� �õ� Ƚ��, ���� �� ����, ã�� �� ������ ����ϴ� �Լ�
void printSingleTailUI(int attempts, int remain, int find) { 
    printf("\033[0;37m");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("               Attempts : %d               \n", attempts);
    printf("                Remain : %d                \n", remain);
    printf("                 Find :  %d                \n", find);
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
}

// ��Ƽ�÷��� ��忡�� Player�� �õ� Ƚ��, ���� �� ����, ã�� �� ������ ����ϴ� �Լ�
void printMultiTailUI(int attempts1, int attempts2, int remain1, int remain2, int find1, int find2) {
    printf("\033[0;37m");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("   P1 Attempts : %d    P2 Attempts : %d   \n", attempts1, attempts2);
    printf("    P1 Remain : %d       P2 Remain : %d    \n", remain1, remain2);
    printf("     P1 Find : %d         P2 Find : %d     \n", find1, find2);
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
}

// Player�� ������ ó���ϴ� �Լ�
void processGuess(char board[][boardSize], int boardSize, int player) {
    int guessRow, guessCol;
    
    printBoard(board, boardSize); // ������ ���
    
    printf("Player %d, enter your guess! (row column): ", player);
    while (scanf("%d %d", &guessRow, &guessCol) != 2 || !isValidGuess(guessRow, guessCol, boardSize) || getchar() != '\n') { // ��ȿ���� �ʴ� �Է��� ������ ���۸� ���� �۾�
        while (getchar() != '\n'); 
        printf("Invalid guess! Please enter valid coordinates\n");
        printf("Player %d, enter your guess! (row column): ", player);
    }

    char cell = board[guessRow][guessCol]; 
    if (cell == 'S') { // cell�� ���� ���
        printf("Player %d hit a ship!\n", player);
        Beep(_B,100);
        board[guessRow][guessCol] = 'H'; // cell�� 'H'�� �����Ͽ� �踦 �������� ǥ��
    } else if (cell == 'H') { // cell�� �̹� ���� ���� ���
        printf("Player %d, Congratulations! You destroyed a ship!\n", player);
        if (player == 0) { // Player0�� �踦 ã����(�̱��÷��� ���)
            findShipcnt1++;
            remainShips1--;
        } else if(player == 1) { // Player1�� �踦 ã����(��Ƽ�÷��� ���)
            findShipcnt1++; // Player1�� ã�� �� ���� +1
            remainShips2--; // Player2�� ���� �� ���� -1
        } else { // Player2�� �踦 ã����(��Ƽ�÷��� ���)
            findShipcnt2++; // Player2�� ã�� �� ���� +1 
            remainShips1--; // Player1�� ���� �� ���� -1
        }
        Beep(_B,100);
        board[guessRow][guessCol] = 'O'; // cell�� 'O'�� �����Ͽ� �踦 �ı������� ǥ��
    } else if (cell == '~') { // cell�� �� ĭ�� ���
        printf("Player %d missed! Try again!\n", player);
        Beep(_F,100);
        board[guessRow][guessCol] = 'X'; // cell�� 'X'�� �����Ͽ� Ʋ������ ǥ��
    } else { // �̹� ������ ��ġ�� ���
        printf("Player %d, you've already guessed this location. Try again!\n", player);
    }
}

// ���� ���̵��� �����ϴ� �Լ�
void selectDifficulty(int *boardSize, int *shipsCount) {
    int difficulty;

    printf("Select Difficulty\n");
    printf("1: Easy  2: Hard  -->  ");
    scanf("%d", &difficulty);
    while (getchar() != '\n'); 

    if (difficulty == 1) { // Easy ���̵��� ������ ���
        *boardSize = EASY_BOARD_SIZE;
        *shipsCount = EASY_SHIPS_COUNT;
        remainShips1 = EASY_SHIPS_COUNT;
        remainShips2 = EASY_SHIPS_COUNT;
    } else if (difficulty == 2) { // Hard ���̵��� ������ ���
        *boardSize = HARD_BOARD_SIZE;
        *shipsCount = HARD_SHIPS_COUNT;
        remainShips1 = HARD_SHIPS_COUNT;
        remainShips2 = HARD_SHIPS_COUNT;
    } else {
        printf("Invalid input value!\n");
        selectDifficulty(boardSize, shipsCount); // �Լ� ��ȣ��� ���̵� �缱��
    }
}

// �̱��÷��� ��� �Լ�
void singlePlay(int boardSize, int shipsCount) {
    char board[boardSize][boardSize];
    int guessRow, guessCol;
    int a = 0;
    time_t start, end; 

    initializeBoard(board, boardSize); // ���� �ʱ�ȭ �۾�
    placeShipsRandom(board, boardSize, shipsCount); // �� ������ġ �۾�
    printHeadUI(); // HeadUI ���

    time(&start); // ���� ���� �ð� ���
    
    while (!hasWon(board, boardSize)) {  // ���忡 �谡 �������� ���� ������
        processGuess(board, boardSize, 0); // ���� ��ġ�� ����
        attempts++; 
        printSingleTailUI(attempts, remainShips1, findShipcnt1); // �ѹ� �����Ҷ����� TailUI ���
    }

    time(&end); // ���� ���� �ð� ���
    int time_taken = difftime(end, start); // �ɸ� �ð� ���

    printf("\n");
    printBoard(board, boardSize); // ������ ���
    printf("Congratulations! All battleships have been shot down. Attempts: %d\n", attempts);
    printf("Time taken: %d seconds\n", time_taken); 
    if (boardSize == 5) { // �������� ���� ���� �ٸ� ��ŷǥ�� ǥ��
        rank_input_E(attempts); // Easy��� ��ŷǥ
    } else {
        rank_input_H(attempts); // Hard��� ��ŷǥ
    } 

    while (1) {
        printf("Would you like to check the ranking table?(1: Yes  2: No)  -->  ");
        scanf("%d", &a);
        while(getchar() != '\n');
        if (a == 1) {
            showRanking(boardSize); // ��ŷ ���
            break;
        } else if (a == 2) {
            return;
        } else {
            printf("Invalid Select. Try again!\n");
        }
    }
}

// ��Ƽ�÷��� ��� �Լ�
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

        initializeBoard(board1, boardSize); // ����1 �ʱ�ȭ �۾�

        if (mode1 == 1) { // Player1�� ���� ��ġ�� ���� �����ϴ� ���
            placeShips(board1, boardSize, shipsCount); // Player1�� �� ������ġ �۾�
            break;
        } else if (mode1 == 2) { // �ڵ����� ���� ��ġ�� �����ϴ� ���
            placeShipsRandom(board1, boardSize, shipsCount); // ����1�� �� ������ġ �۾�
            break;
        } else {
            printf("Invalid input value! Please try again!\n");
        }
    }

    while (1) {
        printf("Player 2: Choose ship placement mode(1: Manual  2: Random)  -->  ");
        scanf("%d", &mode2);
        while(getchar() != '\n'); 

        initializeBoard(board2, boardSize); // ����2 �ʱ�ȭ �۾�

        if (mode2 == 1) { // Player2�� ���� ��ġ�� ���� �����ϴ� ���
            placeShips(board2, boardSize, shipsCount); // Player2�� �� ������ġ �۾�
            break;
        } else if (mode2 == 2) { // �ڵ����� ���� ��ġ�� �����ϴ� ���
            placeShipsRandom(board2, boardSize, shipsCount); // ����2�� �� ������ġ �۾�
            break;
        } else {
            printf("Invalid input value! Please try again!\n");
        }
    }

    printHeadUI(); // HeadUI ���
    printf("Guess the location of the battleship on the board!\n");
    printf("Enter row and column numbers from 0 to %d\n", boardSize - 1);

    int turn = 1;

    while (!hasWon(board1, boardSize) && !hasWon(board2, boardSize)) {  // �� ���� �� ��� ���ʿ����� �¸� ������ �������� ���� ������
        if (turn == 1) {
            printf("Player 1's turn: \n");
            processGuess(board1, boardSize, 1); // ����1�� �� ��ġ�� ����
            attempts1++; 
            printMultiTailUI(attempts1, attempts2, remainShips1, remainShips2, findShipcnt1, findShipcnt2); // �ѹ� �����Ҷ����� TailUI ���
            if (hasWon(board1, boardSize)) { // ���� Player1�� �踦 ��� ã�Ҵٸ�
                printf("Player 1 wins!\n");
                break;
            }
            turn = 2; 
        } else {
            printf("Player 2's turn: \n");
            processGuess(board2, boardSize, 2); // ����2�� �� ��ġ�� ����
            attempts2++; 
            printMultiTailUI(attempts1, attempts2, remainShips1, remainShips2, findShipcnt1, findShipcnt2); // �ѹ� �����Ҷ����� TailUI ���
            if (hasWon(board2, boardSize)) { // ���� Player2�� �踦 ��� ã�Ҵٸ�
                printf("Player 2 wins!\n");
                break;
            }
            turn = 1;
        }
    }
 
    printf("\n");
    printf("\n");
    printBoard(board1, boardSize); // ������1 ���
    printf("\n\n\n");
    printBoard(board2, boardSize); // ������2 ���
}

// ���� ��带 �����ϴ� �Լ�
void gameMode() {
    int n;
    
    printf("Select Mode\n");
    printf("1: SinglePlay  2: MultiPlay  -->  ");
    scanf("%d", &n);
    while(getchar() != '\n');

    if (n == 1) { // �̱��÷��� ��� ���ý�
        selectDifficulty(&boardSize, &shipsCount); // ���̵� ����
        singlePlay(boardSize, shipsCount); // �̱��÷��� ��� ����
    } else if (n == 2) { // ��Ƽ�÷��� ��� ���ý�
        selectDifficulty(&boardSize, &shipsCount); // ���̵� ����
        multiPlay(boardSize, shipsCount); // ��Ƽ�÷��� ��� ����
    } else { 
        printf("Invalid Select. Try again!\n");
        gameMode(); // �Լ� ��ȣ��� ���� ��� �缱��
    }
}

// ���带 �ʱ�ȭ�ϴ� �Լ�
void initializeBoard(char board[][boardSize], int boardSize) {
    int i, j;
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardSize; j++) {
            board[i][j] = '~'; // ��� ����ĭ�� �ʱ�ȭ
        }
    }
}

// ���带 ����ϴ� �Լ�
void printBoard(char board[][boardSize], int boardSize) {
    int i, j;
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardSize; j++) {
            char cell = board[i][j];
            if (cell == '~') { // cell�� �� ĭ�� ���
                printf("\033[0;34m"); // �Ķ���
                printf("%c ", cell);
                printf("\033[0;37m"); // �⺻��
            } else if (cell == 'H') { // cell�� �̹� ���� ���� ���
                printf("\033[0;33m"); // �����
                printf("%c ", cell);
                printf("\033[0;37m"); // �⺻��
            } else if (cell == 'O') { // cell�� ���� ���
                printf("\033[0;31m"); // ������
                printf("%c ", cell);
                printf("\033[0;37m"); // �⺻��
            } else if (cell == 'X') { // cell�� ��� ���� ���
                printf("\033[0;36m"); // �ʷϻ�
                printf("%c ", cell);
                printf("\033[0;37m"); // �⺻��
            } else {
                printf("\033[0;34m"); // �Ķ���
                printf("~ ");
                printf("\033[0;37m"); // �⺻��
            }
        }
        printf("\n");
    }
}

// �踦 ���忡 ��ġ�ϴ� �Լ�
void placeShips(char board[][boardSize], int boardSize, int shipsCount) {
    int i;
    for (i = 0; i < shipsCount; i++) {
        int row, col;
        printf("Enter the coordinates for Ship %d(row column): ", i + 1);
        int result = scanf("%d %d", &row, &col); 
        if (result == 2) { // 2���� ������ �ԷµǾ��� ���� ����
            if (getchar() != '\n') { 
                printf("Too many inputs. Only enter two numbers. Try again!\n");
                while (getchar() != '\n'); 
                i--; // �̹� �Է��� ��ȿȭ�ϰ�, �Է��� �ٽ� �޵��� ��
                continue; 
            }

            if (row >= 0 && row < boardSize && col >= 0 && col < boardSize) {
                if (board[row][col] != '~') {
                    printf("There is already a ship at that location. Try again!\n");
                    i--; // �߸��� ��ġ �Է� ��, �Է��� �ٽ� �޵��� ��
                } else {
                    board[row][col] = 'S';
                }
            } else {
                printf("Invalid coordinates. Try again!\n");
                i--; // ���� ���� ��ǥ �Է� ��, �Է��� �ٽ� �޵��� ��
            }
        } else { // �Է¹��� �����Ͱ� 2���� ������ �ƴ϶��
            printf("Invalid input. You need to enter two numbers. Try again!\n");
            while (getchar() != '\n'); 
            i--; // �̹� �Է��� ��ȿȭ�ϰ�, �Է��� �ٽ� �޵��� ��
        }
    }
}

// �踦 ���忡 �������� ��ġ�ϴ� �Լ�
void placeShipsRandom(char board[][boardSize], int boardSize, int shipsCount) {
    int i;
    srand(time(0)); // rand() �Լ��� ���� ������ ���� ���� �ð��� �õ�� ����

    for (i = 0; i < shipsCount; i++) {
        int row, col;
        do {
            row = rand() % boardSize; // ���� '��' ����
            col = rand() % boardSize; // ���� '��' ����
        } while (board[row][col] != '~'); 
        board[row][col] = 'S'; // �� ��ġ
    }
}

// ������ ���� ������ ��ȿ������ Ȯ���ϴ� �Լ�
int isValidGuess(int row, int col, int boardSize) {
    return (row >= 0 && row < boardSize && col >= 0 && col < boardSize); // ��ȿ�ϸ� 1, ��ȿ���� ������ 0 ��ȯ
}

// ��� �谡 ���ߵǾ������� Ȯ���ϴ� �Լ�
int hasWon(char board[][boardSize], int boardSize) {
    int i, j;
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardSize; j++) {
            if (board[i][j] == 'S' || board[i][j] == 'H') {
                return 0; // �����ǿ� �谡 �����ִٸ� 0�� ��ȯ
            }
        }
    }
    return 1; // �����ǿ� �谡 ���ٸ� 1�� ��ȯ(�¸�)
}

// Easy����� ��ŷǥ �Է� �Լ�
void rank_input_E(int attempt) {
    char player_name[50];

    printf("Game Over. Enter name: ");
    scanf("%s", player_name);


    FILE* file = fopen("Rank_list_E.txt", "a"); // Rank_list_E.txt�� ���� �������� open
    if (file == NULL) {
        printf("File open error\n");
        return;
    }

    fprintf(file, "Player Name: %s\tattempt: %d\n", player_name, attempt); // Player �̸��� �õ� Ƚ���� ���Ͽ� ����
    fclose(file); 
}

// Easy��� ������ �о ����ü �迭�� �����ϴ� �Լ�
int read_attempt_E(Player players[], int max_players) {
    FILE* file = fopen("Rank_list_E.txt", "r");  // Rank_list_E.txt�� �б� �������� open
    if (file == NULL) {
        printf("File open error\n");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "Player Name: %49s\tattempt: %d\n", players[count].name, &players[count].attempt) == 2) { // fscanf�� ���� ���� ��� �о���� ���� 2���̹Ƿ� 2�� ��ȯ
        count++; // �迭�� ���� �ε����� �Ѿ
        if (count >= max_players) {
            break;
        }
    }

    fclose(file);
    return count;
}

// Hard����� ��ŷǥ �Է� �Լ�
void rank_input_H(int attempt) {
    char player_name[50];

    printf("Game Over! Enter name: ");
    scanf("%s", player_name);

    FILE* file = fopen("Rank_list_H.txt", "a"); // Rank_list_H.txt�� ���� �������� open
    if (file == NULL) {
        printf("File open error\n");
        return;
    }

    fprintf(file, "Player Name: %s\tattempt: %d\n", player_name, attempt); // Player �̸��� �õ� Ƚ���� ���Ͽ� ����
    fclose(file);
}

// Hard��� ������ �о ����ü �迭�� �����ϴ� �Լ�
int read_attempt_H(Player players[], int max_players) {
    FILE* file = fopen("Rank_list_H.txt", "r"); // Rank_list_H.txt�� �б� �������� open
    if (file == NULL) {
        printf("File open error\n");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "Player Name: %49s\tattempt: %d\n", players[count].name, &players[count].attempt) == 2) { // fscanf�� ���� ���� ��� �о���� ���� 2���̹Ƿ� 2�� ��ȯ
        count++; // �迭�� ���� �ε����� �Ѿ
        if (count >= max_players) {
            break;
        }
    }

    fclose(file);
    return count;
}

// ������������ �����ϱ� ���� �� �Լ�
int compare_attempt(const void* a, const void* b) {
    Player* playerA = (Player*)a; // ù ��° �Ű������� Player ����ü �����ͷ� �� ��ȯ
    Player* playerB = (Player*)b; // �� ��° �Ű������� Player ����ü �����ͷ� �� ��ȯ
    return playerA->attempt - playerB->attempt; // �� Player�� �õ� Ƚ�� ���̸� ��ȯ
}

// ��ŷǥ ��� �Լ�
void print_sorted_attempt(Player players[], int count) {
    int i;
    printf("\n======= Sorted attempt =======\n");
    for (i = 0; i < count; i++) {
        printf("%d Player Name: %s\tattempt: %d\n", i + 1, players[i].name, players[i].attempt);
    }
}

// ��ŷ�� �����ֱ� ���� �Լ�
void showRanking(int boardSize) {
    const int MAX_PLAYERS = 100;
    Player players[MAX_PLAYERS];
    int player_count;

    if (boardSize == 5) { // ���� ����� ���� ���̵��� �´� ������ ���� ��ŷǥ ���
        player_count = read_attempt_E(players, MAX_PLAYERS); // Easy��� ��ŷǥ
    } else {
        player_count = read_attempt_H(players, MAX_PLAYERS); // Hard��� ��ŷǥ
    }
    
    qsort(players, player_count, sizeof(Player), compare_attempt); // players �迭�� compare_attempt �� �Լ��� ����Ͽ� ������������ ����
    print_sorted_attempt(players, player_count); // ���ĵ� ��ŷǥ�� ���
}