#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // 시간 관련 함수들을 사용하기 위한 라이브러리

#define EASY_BOARD_SIZE 5   //게임 보드의 크기 정의
#define EASY_SHIPS_COUNT 4  //게임의 전함 수 정의
#define HARD_BOARD_SIZE 6
#define HARD_SHIPS_COUNT 7

// 플레이어 정보 구조체 정의
typedef struct {
    char name[50];
    int score;
} Player;
int boardSize = 0;
int shipsCount = 0;

void processGuess(char board[][boardSize], int boardSize, int player);
void selectDifficulty(int* boardSize, int* shipsCount);
void singleplay(int boardSize, int shipsCount);
void multplay();
void gamemode();
void initializeBoard(char board[][boardSize], int boardSize);
void printBoard(char board[][boardSize], int boardSize);
void placeShips(char board[][boardSize],int boardSize, int shipsCount);
int isValidGuess(int row, int col, int boardSize);
int hasWon(char board[][boardSize], int boardSize);
void rank_input(int score);
int compare_scores(const void* a, const void* b);
int read_scores(Player players[], int max_players);
void print_sorted_scores(Player players[], int count);
void showRanking();

int main() {
     //게임 모드 설정
    gamemode();

    return 0;
}


void processGuess(char board[][boardSize], int boardSize, int player) {
    int guessRow, guessCol;
    printBoard(board, boardSize);
    printf("Player %d, enter your guess (row column): ", player);
    while (scanf("%d %d", &guessRow, &guessCol) != 2 || !isValidGuess(guessRow, guessCol, boardSize)) {
        while (getchar() != '\n');
        printf("Invalid guess! Please enter valid coordinates.\n");
    }

    if (board[guessRow][guessCol] == 'S') {
        printf("Player %d hit a ship!\n", player);
        board[guessRow][guessCol] = 'H';
    } else if (board[guessRow][guessCol] == 'H') {
        printf("Player %d, congratulations! You destroyed a ship!\n", player);
        board[guessRow][guessCol] = 'X';
    } else if (board[guessRow][guessCol] == '~') {
        printf("Player %d missed! Try again.\n", player);
        board[guessRow][guessCol] = 'O';
    } else {
        printf("Player %d, you've already guessed this location. Try again.\n", player);
    }
}


void selectDifficulty(int *boardSize, int *shipsCount) {
    char difficulty;
    printf("Select difficulty (e for easy, h for hard): ");
    scanf(" %c", &difficulty);
    while(getchar() != '\n');  // 입력 버퍼 비우기

    if (difficulty == 'h') {
        *boardSize = HARD_BOARD_SIZE;
        *shipsCount = HARD_SHIPS_COUNT;
    } else if (difficulty == 'e') {
        *boardSize = EASY_BOARD_SIZE;
        *shipsCount = EASY_SHIPS_COUNT;
    } else {
        printf("Invalid input value!\n");
        exit(1);
    }
}

void singleplay(){
     char board[BOARD_SIZE][BOARD_SIZE];
    int guessRow, guessCol;
    int attempts = 0;
    int a=0;
    time_t start, end; // 시간 측정을 위한 변수
     // 게임 보드를 초기화하고 전함을 배치함
    initializeBoard(board); //초기화화
    placeShips(board); //배치  -> 랜덤 배치 들어오면 추가해줌.


    // 게임 설명 출력
    printf("=== Battleship Game ===\n");
    printf("Guess the location of the battleship on the board.\n");
    printf("Enter row and col numbers from 0 to 4.\n");

    time(&start); // 게임 시작 시간 기록
    // 게임 루프
    while (!hasWon(board, boardSize)) {  //보드에 전함이 남아있으면
        processGuess(board, boardSize, player);
        attempts++; //시도 횟수 증가
    }
  
    time(&end); // 게임 종료 시간 기록
    double time_taken = difftime(end, start); // 걸린 시간 계산

    // 게임 종료, 최종 보드 상태와 시도 횟수 출력
    printf("\n");
    printBoard(board,boardSize);
    printf("congratulations! All battleships have been shot down. attempts: %d\n", attempts);

    
    rank_input(attempts);
    printf("Would you like to check the ranking table? 1: O else: X ");
    scanf("%d",&a);
    if(a==1){
        showRanking();
    }
    else{
        return;
    } 

}
void multplay(){

    char board1[boardSize][boardSize]; //1플레이어 보드
    char board2[boardSize][boardSize]; //2플레이어 보드 

    
    int guessRow1, guessCol1;
    int guessRow2, guessCol2;
     // 게임 보드를 초기화하고 전함을 배치함

    initializeBoard(board1,boardSize); //초기화
    placeShips(board1,boardSize,shipsCount); //배치  -> 랜덤 배치 들어오면 추가해줌.
    initializeBoard(board2,boardSize); //초기화
    placeShips(board2,boardSize,shipsCount);


    // 게임 설명 출력
    printf("=== Battleship Game ===\n");
    printf("Guess the location of the battleship on the board.\n");
    printf("Enter row and col numbers from 0 to 4.\n");

    int turn = 1;
    // 게임 루프
    while (!hasWon(board1, boardSize) && !hasWon(board2, boardSize)) {  //보드에 전함이 남아있으면
        if (turn == 1) {
            printf("Player 1's turn:\n");
            processGuess(board1, boardSize, 1);
            if (hasWon(board1, boardSize)) {
                printf("Player 1 wins!\n");
                break;
            }
            turn = 2;
        } else {
            printf("Player 2's turn:\n");
            processGuess(board2, boardSize, 2);
            if (hasWon(board2, boardSize)) {
                printf("Player 2 wins!\n");
                break;
            }
            turn = 1;
        }
    }
    


    // 게임 종료, 최종 보드 상태출력 
    printf("\n");
    printf("\n");

    printBoard(board1,boardSize);
    printf("\n\n\n");
    printBoard(board2,boardSize);
    
    
/*  if(hasWon(board1, boardSize) && hasWon(board2, boardSize)){
        printf("It's a draw");
    }
    if(hasWon(board1, boardSize) && !hasWon(board2, boardSize)){
        printf("p1 wins! congratulations! All battleships have been shot down.");
    }
    if(!hasWon(board1, boardSize) && hasWon(board2, boardSize)){
        printf("p2 wins! congratulations! All battleships have been shot down.");
    }
*/

}

//싱글 플레이와 멀티 플레이를 선택하는 함수
void gamemode(){
    int n;
    printf("Select Mode \n");
    printf("1: SiglePlay 2:MultiPlay ");
    scanf("%d",&n);

    selectDifficulty(&boardSize,&shipsCount);
    if(n==1){
        singleplay(boardSize, shipsCount);
    }
    else if(n==2){
        multplay(boardSize, shipsCount);

    }
    else{
        printf("wrong!\n");
        gamemode(); //잘못입력시 다시 모드 선택하도록 함.
    }
    
}
 
// 보드를 빈 칸으로 초기화하는 함수

void initializeBoard(char board[][boardSize],int boardSize) { // 모두 '~'로 출력함함
    int i, j;
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardSize; j++) {

            board[i][j] = '~';  // '~'는 빈 칸을 나타냄
        }
    }
}

// 전함 위치를 감추고 보드를 출력하는 함수

void printBoard(char board[][boardSize], int boardSize) {
    int i, j;
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardSize; j++) {

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
void placeShips(char board[][boardSize],int boardSize, int shipsCount) {
    int i;
    for(i = 0; i < shipsCount; i++) {

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
            if(row >= 0 && row < boardSize && col >= 0 && col < boardSize) {

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

// 유효한 추측인지 확인하는 함수

int isValidGuess(int row, int col, int boardSize) {
    return (row >= 0 && row < boardSize && col >= 0 && col < boardSize);  //보드 사이즈 안에있으면 T리턴 아니면 F리턴
}

// 모든 전함이 격추되었는지 확인하는 함수
int hasWon(char board[][boardSize], int boardSize) {
    int i, j;
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardSize; j++) {
            if (board[i][j] == 'S' || board[i][j] == 'H') {  

                return 0;  // 아직 격추되지 않은 전함이 하나 이상 남아있음
            }
        }
    }
    return 1;  // 모든 전함이 격추됨
}

// 플레이어 정보 입력 함수
void rank_input(int score) {
    char player_name[50];

    printf("Game Over Enter name: ");
    scanf("%s", player_name);

    // 메모장 열기
    FILE* file = fopen("Rank_list.txt", "a");
    if (file == NULL) {
        printf("File open error\n");
        return;
    }

    // 이름과 점수 파일에 입력
    fprintf(file, "Player Name: %s\tScore: %d\n", player_name, score);

    fclose(file);
}

// 플레이어 정보 파일에서 읽기
int read_scores(Player players[], int max_players) {
    FILE* file = fopen("Rank_list.txt", "r");
    if (file == NULL) {
        printf("File open error\n");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "Player Name: %49s\tScore: %d\n", players[count].name, &players[count].score) == 2) { //fscanf의 반환값이 2이면  2가지 값 모두 잘 가져왔단 의미 
        count++;
        if (count >= max_players) {
            break;
        }
    }

    fclose(file);
    return count;
}

// 점수를 기준으로 오름차순 정렬하는 함수
int compare_scores(const void* a, const void* b) {
    Player* playerA = (Player*)a;
    Player* playerB = (Player*)b;
    return playerA->score - playerB->score; // 오름차순 정렬
}

// 정렬된 결과 출력 함수
void print_sorted_scores(Player players[], int count) {
    printf("\n=== Sorted Scores ===\n");
    for (int i = 0; i < count; i++) {
        printf("%d Player Name: %s\tScore: %d\n",i+1, players[i].name, players[i].score);
    }
}

void showRanking() {
    

    // 최대 플레이어 수 정의
    const int MAX_PLAYERS = 100;
    Player players[MAX_PLAYERS];

    // 파일에서 플레이어 정보 읽기
    int player_count = read_scores(players, MAX_PLAYERS);

    // 점수 기준으로 정렬
    qsort(players, player_count, sizeof(Player), compare_scores);

    // 정렬된 결과 출력
    print_sorted_scores(players, player_count);

}
