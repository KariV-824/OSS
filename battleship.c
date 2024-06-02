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

<<<<<<< Updated upstream
typedef struct { // 플레이어 정보 구조체 정의
=======
typedef struct { // �÷��̾� ���� ����ü ����
>>>>>>> Stashed changes
    char name[50];
    int attempt;
} Player;

int boardSize = 0;
int shipsCount = 0;
int attempts = 0;
int remainships1 = 0;
int remainships2 = 0;
int findshipcnt1 = 0;
int findshipcnt2 = 0;

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
<<<<<<< Updated upstream
    gameMode(); // 게임 모드 설정
=======
    gameMode(); // ���� ��� ����
>>>>>>> Stashed changes
    return 0;
}

void printHeadUI() {
    printf("\033[0;37m");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("@        BATTLESHIP        @\n");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
}

void printTailUI(int attempts, int remain, int find) {
    printf("\033[0;37m");
<<<<<<< Updated upstream
    printf("@ @ @ @ @ @ @ @ @ @ @\n");
    printf("@   Attempts : %d   @\n", attempts);
    printf("@ @ @ @ @ @ @ @ @ @ @\n");
=======
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("@             Attempts : %d               @\n", attempts);
    printf("@              Remain : %d                @\n", remain);
    printf("@              Found :  %d                @\n", find);
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
>>>>>>> Stashed changes
}

void printMultiUI(int attempts, int remain1, int remain2, int find1, int find2) {
    printf("\033[0;37m");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("@              Attempts : %d               @\n", attempts);
    printf("@ P1 Remain : %d             P2 Remain : %d @\n", remain1,remain2);
    printf("@ P1  Found : %d             P2 Found : %d  @\n", find1,find2);
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
}

void processGuess(char board[][boardSize], int boardSize, int player) {
    int guessRow, guessCol;
<<<<<<< Updated upstream
    char cell = board[guessRow][guessCol];

    printBoard(board, boardSize);
    printTailUI(attempts);

=======
    printBoard(board, boardSize);
    printf("\033[0;37m");
    printf("Player %d, enter your guess (row column): ", player);
>>>>>>> Stashed changes
    while (scanf("%d %d", &guessRow, &guessCol) != 2 || !isValidGuess(guessRow, guessCol, boardSize)) {
        while (getchar() != '\n');
        printf("Invalid guess! Please enter valid coordinates.\n");
        printf("Player %d, enter your guess(row column): ", player);
    }

    if (cell == 'S') {
        printf("Player %d hit a ship!\n", player);
        Beep(_B,100);
        board[guessRow][guessCol] = 'H';
    } else if (cell == 'H') {
        printf("Player %d, congratulations! You destroyed a ship!\n", player);
        if (player == 0)
        {
            findshipcnt1++;
            remainships1--;
        }
        else if(player == 1)
        {
            findshipcnt1++;
            remainships2--;
        }
        else
        {
            findshipcnt2++;
            remainships1--;
        }
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

void selectDifficulty(int *boardSize, int *shipsCount) {
    char difficulty;

<<<<<<< Updated upstream
    printf("Select Difficulty");
    printf("1: Easy  2: Hard  --> ");
    scanf("%c", &difficulty);
    while (getchar() != '\n');  // 입력 버퍼 비우기
=======
    printf("Select Difficulty\n");
    printf("1: Easy  2: Hard  -->  ");
    scanf("%d", &difficulty);
    while (getchar() != '\n');  // �Է� ���� ����
>>>>>>> Stashed changes

    if (difficulty == '1') {
        *boardSize = EASY_BOARD_SIZE;
        *shipsCount = EASY_SHIPS_COUNT;
<<<<<<< Updated upstream
    } else if (difficulty == '2') {
=======
        remainships1 = EASY_SHIPS_COUNT;
        remainships2 = EASY_SHIPS_COUNT;
    } else if (difficulty == 2) {
>>>>>>> Stashed changes
        *boardSize = HARD_BOARD_SIZE;
        *shipsCount = HARD_SHIPS_COUNT;
        remainships1 = HARD_SHIPS_COUNT;
        remainships2 = HARD_SHIPS_COUNT;
    } else {
        printf("Invalid input value!\n");
        exit(1);
    }
}

void singlePlay(int boardSize, int shipsCount) {
    char board[boardSize][boardSize];
    int guessRow, guessCol;
<<<<<<< Updated upstream
    int a = 0;
    time_t start, end; // 시간 측정을 위한 변수

    initializeBoard(board, boardSize); // 초기화
    placeShipsRandom(board, boardSize, shipsCount); // 랜덤 배치
    printHeadUI();

    time(&start); // 게임 시작 시간 기록
    // 게임 루프
    while (!hasWon(board, boardSize)) {  // 보드에 전함이 남아있으면
        processGuess(board, boardSize, 1);
        attempts++; //시도 횟수 증가
    }

    time(&end); // 게임 종료 시간 기록
    int time_taken = difftime(end, start); // 걸린 시간 계산

    // 게임 종료, 최종 보드 상태와 시도 횟수 출력
    printf("\n");
    printBoard(board, boardSize);
    printf("Congratulations! All battleships have been shot down. Attempts: %d\n", attempts);
    printf("Time taken: %d seconds\n", time_taken); // 총 소요 시간 출력
=======


    int a = 0;
    time_t start, end; // �ð� ������ ���� ����

    initializeBoard(board, boardSize); // �ʱ�ȭ
    placeShipsRandom(board, boardSize, shipsCount); // ���� ��ġ
    printHeadUI();

    time(&start); // ���� ���� �ð� ���
    // ���� ����
    while (!hasWon(board, boardSize)) {  // ���忡 ������ ����������
        processGuess(board, boardSize, 0);
        attempts++; //�õ� Ƚ�� ����
        printTailUI(attempts,remainships1,findshipcnt1);
    }

    time(&end); // ���� ���� �ð� ���
    int time_taken = difftime(end, start); // �ɸ� �ð� ���

    // ���� ����, ���� ���� ���¿� �õ� Ƚ�� ���
    printf("\n");
    printBoard(board, boardSize);
    printf("Congratulations! All battleships have been shot down. Attempts: %d\n", attempts);
    printf("Time taken: %d seconds\n", time_taken); // �� �ҿ� �ð� ���
>>>>>>> Stashed changes
    
    if (boardSize == 5) {
        rank_input_E(attempts);
    } else {
        rank_input_H(attempts);
    }

    printf("Would you like to check the ranking table? 1: Yes  2: No  --> ");
    scanf("%d", &a);
    if (a == 1) {
        showRanking(boardSize);
    } else if ( a == 2) {
        return;
    }
}

void multiPlay(int boardSize, int shipsCount) {
<<<<<<< Updated upstream
    char board1[boardSize][boardSize]; // 1플레이어 보드
    char board2[boardSize][boardSize]; // 2플레이어 보드 
    int guessRow1, guessCol1;
    int guessRow2, guessCol2;
    int mode1, mode2; // 각 플레이어의 배치 모드

    // 플레이어 1의 배치 모드 선택
    printf("Player 1: Choose ship placement mode(1: Manual  2: Random)  --> ");
=======
    char board1[boardSize][boardSize]; // 1�÷��̾� ����
    char board2[boardSize][boardSize]; // 2�÷��̾� ���� 
    int guessRow1, guessCol1;
    int guessRow2, guessCol2;
    int mode1, mode2; // �� �÷��̾��� ��ġ ���

    // �÷��̾� 1�� ��ġ ��� ����
    printf("Player 1: Choose ship placement mode(1: Manual  2: Random)  -->  ");
>>>>>>> Stashed changes
    scanf("%d", &mode1);
    initializeBoard(board1, boardSize);

    if (mode1 == 1) {
        placeShips(board1, boardSize, shipsCount);
    } else {
        placeShipsRandom(board1, boardSize, shipsCount);
    }

<<<<<<< Updated upstream
    // 플레이어 2의 배치 모드 선택
    printf("Player 2: Choose ship placement mode(1: Manual  2: Random)  --> ");
=======
    // �÷��̾� 2�� ��ġ ��� ����
    printf("Player 2: Choose ship placement mode(1: Manual  2: Random)  -->  ");
>>>>>>> Stashed changes
    scanf("%d", &mode2);
    initializeBoard(board2, boardSize);

    if (mode2 == 1) {
        placeShips(board2, boardSize, shipsCount);
    } else {
        placeShipsRandom(board2, boardSize, shipsCount);
    }

<<<<<<< Updated upstream
    // 게임 설명 출력
    printf("=== Battleship Game ===\n");
    printf("Guess the location of the battleship on the board.\n");
    printf("Enter row and column numbers from 0 to %d.\n", boardSize - 1);

    int turn = 1;
    // 게임 루프
    while (!hasWon(board1, boardSize) && !hasWon(board2, boardSize)) {  // 보드에 전함이 남아있으면
=======
    // ���� ���� ���
    printHeadUI();
    printf("Guess the location of the battleship on the board\n");
    printf("Enter row and column numbers from 0 to %d\n", boardSize - 1);

    int turn = 1;
    // ���� ����
    while (!hasWon(board1, boardSize) && !hasWon(board2, boardSize)) {
        printMultiUI(attempts,remainships1,remainships2,findshipcnt1,findshipcnt2);  // ���忡 ������ ����������
>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
    // 게임 종료, 최종 보드 상태 출력 
=======
    // ���� ����, ���� ���� ���� ��� 
>>>>>>> Stashed changes
    printf("\n");
    printf("\n");
    printBoard(board1, boardSize);
    printf("\n\n\n");
    printBoard(board2, boardSize);
}

void gameMode() {
    int n;
    
    printf("Select Mode\n");
    printf("1: SinglePlay  2: MultiPlay  --> ");
    scanf("%d", &n);
    selectDifficulty(&boardSize, &shipsCount);

    if (n == 1) {
        singlePlay(boardSize, shipsCount);
    } else if (n == 2) {
        multiPlay(boardSize, shipsCount);
    } else {
<<<<<<< Updated upstream
        printf("wrong!\n");
        gameMode(); // 잘못 입력시 다시 모드 선택하도록 함.
    }
}

// 보드를 빈 칸으로 초기화하는 함수
void initializeBoard(char board[][boardSize], int boardSize) { // 모두 '~'로 출력함함
    int i, j;
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardSize; j++) {
            board[i][j] = '~'; // '~'는 빈 칸을 나타냄
=======
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
>>>>>>> Stashed changes
        }
    }
}

<<<<<<< Updated upstream
// 전함 위치를 감추고 보드를 출력하는 함수
=======
// ���� ��ġ�� ���߰� ���带 ����ϴ� �Լ�
>>>>>>> Stashed changes
void printBoard(char board[][boardSize], int boardSize) {
    int i, j;
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardSize; j++) {
            char cell = board[i][j];
            if (cell == '~') {
                printf("\033[0;34m");
                printf("%c ", cell);
<<<<<<< Updated upstream
=======
            } else if (cell == 'H') {
                printf("\033[0;33m"); // �����
                printf("%c ", cell);
>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
// 전함을 보드에 배치하는 함수
=======
// ������ ���忡 ��ġ�ϴ� �Լ�
>>>>>>> Stashed changes
void placeShips(char board[][boardSize], int boardSize, int shipsCount) {
    int i;
    for (i = 0; i < shipsCount; i++) {
        int row, col;
        printf("Enter the coordinates for Ship %d(row column): ", i + 1);
<<<<<<< Updated upstream
        int result = scanf("%d %d", &row, &col); // 2개의 정수를 입력받아서 result에 저장
        if (result == 2) { // 2개의 정수가 입력되었을 때만 실행
            if (getchar() != '\n') { // 2개의 정수 이후에 추가 문자가 버퍼에 남아있다면
                printf("Too many inputs. Only enter two numbers. Try again.\n");
                while (getchar() != '\n'); // 버퍼에 남은 모든 문자를 버리며 '\n'를 만날 때까지 반복
                i--; // i를 감소시켜 이번 입력을 무효화하고, 입력을 다시 받도록 함
                continue; // for 루프의 처음으로 돌아가 재시작
=======
        int result = scanf("%d %d", &row, &col); // 2���� ������ �Է¹޾Ƽ� result�� ����
        if (result == 2) { // 2���� ������ �ԷµǾ��� ���� ����
            if (getchar() != '\n') { // 2���� ���� ���Ŀ� �߰� ���ڰ� ���ۿ� �����ִٸ�
                printf("Too many inputs. Only enter two numbers. Try again\n");
                while (getchar() != '\n'); // ���ۿ� ���� ��� ���ڸ� ������ '\n'�� ���� ������ �ݺ�
                i--; // i�� ���ҽ��� �̹� �Է��� ��ȿȭ�ϰ�, �Է��� �ٽ� �޵��� ��
                continue; // for ������ ó������ ���ư� �����
>>>>>>> Stashed changes
            }

            if (row >= 0 && row < boardSize && col >= 0 && col < boardSize) {
                if (board[row][col] != '~') {
<<<<<<< Updated upstream
                    printf("There is already a ship at that location. Try again.\n");
                    i--; // 잘못된 위치 입력 시 다시 입력
=======
                    printf("There is already a ship at that location. Try again\n");
                    i--; // �߸��� ��ġ �Է� �� �ٽ� �Է�
>>>>>>> Stashed changes
                } else {
                    board[row][col] = 'S';
                }
            } else {
<<<<<<< Updated upstream
                printf("Invalid coordinates. Try again.\n");
                i--; // 범위 밖 좌표 입력 시 다시 입력
            }
        } else { // 입력받은 데이터가 2개의 정수가 아니라면
            printf("Invalid input. You need to enter only two numbers. Try again.\n");
            while (getchar() != '\n'); // 버퍼에 남은 모든 문자를 버리며 '\n'를 만날 때까지 반복
            i--; // i를 감소시켜 이번 입력을 무효화하고, 입력을 다시 받도록 함
=======
                printf("Invalid coordinates. Try again\n");
                i--; // ���� �� ��ǥ �Է� �� �ٽ� �Է�
            }
        } else { // �Է¹��� �����Ͱ� 2���� ������ �ƴ϶��
            printf("Invalid input. You need to enter only two numbers. Try again\n");
            while (getchar() != '\n'); // ���ۿ� ���� ��� ���ڸ� ������ '\n'�� ���� ������ �ݺ�
            i--; // i�� ���ҽ��� �̹� �Է��� ��ȿȭ�ϰ�, �Է��� �ٽ� �޵��� ��
>>>>>>> Stashed changes
        }
    }
}

<<<<<<< Updated upstream
// 전함을 보드에 랜덤으로 배치하는 함수
void placeShipsRandom(char board[][boardSize], int boardSize, int shipsCount) {
    int i;
    srand(time(0)); // 시드 설정: rand() 함수를 통한 랜덤 값을 생성하기 위해 현재 시간을 시드로 사용
=======
// ������ ���忡 �������� ��ġ�ϴ� �Լ�
void placeShipsRandom(char board[][boardSize], int boardSize, int shipsCount) {
    int i;
    srand(time(0)); // �õ� ����: rand() �Լ��� ���� ���� ���� �����ϱ� ���� ���� �ð��� �õ�� ���
>>>>>>> Stashed changes

    for (i = 0; i < shipsCount; i++) {
        int row, col;
        do {
<<<<<<< Updated upstream
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
=======
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
>>>>>>> Stashed changes
int hasWon(char board[][boardSize], int boardSize) {
    int i, j;
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardSize; j++) {
            if (board[i][j] == 'S' || board[i][j] == 'H') {
<<<<<<< Updated upstream
                return 0; // 아직 격추되지 않은 전함이 하나 이상 남아있음
            }
        }
    }
    return 1; // 모든 전함이 격추됨
}

// Easy 모드 플레이어 정보 입력 함수
=======
                return 0; // ���� ���ߵ��� ���� ������ �ϳ� �̻� ��������
            }
        }
    }
    return 1; // ��� ������ ���ߵ�
}

// Easy ��� �÷��̾� ���� �Է� �Լ�
>>>>>>> Stashed changes
void rank_input_E(int attempt) {
    char player_name[50];

    printf("Game Over. Enter name: ");
    scanf("%s", player_name);

<<<<<<< Updated upstream
    // 메모장 열기
=======
    // �޸��� ����
>>>>>>> Stashed changes
    FILE* file = fopen("Rank_list_E.txt", "a");
    if (file == NULL) {
        printf("File open error\n");
        return;
    }

<<<<<<< Updated upstream
    // 이름과 점수 파일에 입력
=======
    // �̸��� ���� ���Ͽ� �Է�
>>>>>>> Stashed changes
    fprintf(file, "Player Name: %s\tattempt: %d\n", player_name, attempt);
    fclose(file);
}

<<<<<<< Updated upstream
// Easy 모드 플레이어 정보 파일에서 읽기
=======
// Easy ��� �÷��̾� ���� ���Ͽ��� �б�
>>>>>>> Stashed changes
int read_attempt_E(Player players[], int max_players) {
    FILE* file = fopen("Rank_list_E.txt", "r");
    if (file == NULL) {
        printf("File open error\n");
        return 0;
    }

    int count = 0;
<<<<<<< Updated upstream
    while (fscanf(file, "Player Name: %49s\tattempt: %d\n", players[count].name, &players[count].attempt) == 2) { // fscanf의 반환값이 2이면 2가지 값 모두 잘 가져왔단 의미 
=======
    while (fscanf(file, "Player Name: %49s\tattempt: %d\n", players[count].name, &players[count].attempt) == 2) { // fscanf�� ��ȯ���� 2�̸� 2���� �� ��� �� �����Դ� �ǹ� 
>>>>>>> Stashed changes
        count++;
        if (count >= max_players) {
            break;
        }
    }

    fclose(file);
    return count;
}

<<<<<<< Updated upstream
// Hard 모드 플레이어 정보 입력 함수
=======
// Hard ��� �÷��̾� ���� �Է� �Լ�
>>>>>>> Stashed changes
void rank_input_H(int attempt) {
    char player_name[50];

    printf("Game Over. Enter name: ");
    scanf("%s", player_name);

<<<<<<< Updated upstream
    // 메모장 열기
=======
    // �޸��� ����
>>>>>>> Stashed changes
    FILE* file = fopen("Rank_list_H.txt", "a");
    if (file == NULL) {
        printf("File open error\n");
        return;
    }

<<<<<<< Updated upstream
    // 이름과 점수 파일에 입력
=======
    // �̸��� ���� ���Ͽ� �Է�
>>>>>>> Stashed changes
    fprintf(file, "Player Name: %s\tattempt: %d\n", player_name, attempt);
    fclose(file);
}

<<<<<<< Updated upstream
// 플레이어 정보 파일에서 읽기
=======
// �÷��̾� ���� ���Ͽ��� �б�
>>>>>>> Stashed changes
int read_attempt_H(Player players[], int max_players) {
    FILE* file = fopen("Rank_list_H.txt", "r");
    if (file == NULL) {
        printf("File open error\n");
        return 0;
    }

    int count = 0;
<<<<<<< Updated upstream
    while (fscanf(file, "Player Name: %49s\tattempt: %d\n", players[count].name, &players[count].attempt) == 2) { // fscanf의 반환값이 2이면 2가지 값 모두 잘 가져왔단 의미 
=======
    while (fscanf(file, "Player Name: %49s\tattempt: %d\n", players[count].name, &players[count].attempt) == 2) { // fscanf�� ��ȯ���� 2�̸� 2���� �� ��� �� �����Դ� �ǹ� 
>>>>>>> Stashed changes
        count++;
        if (count >= max_players) {
            break;
        }
    }

    fclose(file);
    return count;
}

<<<<<<< Updated upstream
// 점수를 기준으로 오름차순 정렬하는 함수
int compare_attempt(const void* a, const void* b) {
    Player* playerA = (Player*)a;
    Player* playerB = (Player*)b;
    return playerA->attempt - playerB->attempt; // 오름차순 정렬
}

// 정렬된 결과 출력 함수
=======
// ������ �������� �������� �����ϴ� �Լ�
int compare_attempt(const void* a, const void* b) {
    Player* playerA = (Player*)a;
    Player* playerB = (Player*)b;
    return playerA->attempt - playerB->attempt; // �������� ����
}

// ���ĵ� ��� ��� �Լ�
>>>>>>> Stashed changes
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
    
<<<<<<< Updated upstream
    qsort(players, player_count, sizeof(Player), compare_attempt); // 점수 기준으로 정렬
    print_sorted_attempt(players, player_count); // 정렬된 결과 출력
=======
    qsort(players, player_count, sizeof(Player), compare_attempt); // ���� �������� ����
    print_sorted_attempt(players, player_count); // ���ĵ� ��� ���
>>>>>>> Stashed changes
}