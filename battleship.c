#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BOARD_SIZE 5 // 게임 보드의 크기 정의
#define SHIPS_COUNT 4 // 게임의 전함 수 정의

// 플레이어 정보 구조체 정의
typedef struct {
    char name[50];
    int score;
} Player;


void singleplay();
void multplay();
void gamemode();
void initializeBoard(char board[][BOARD_SIZE]);
void printBoard(char board[][BOARD_SIZE]);
void placeShips(char board[][BOARD_SIZE]);
int isValidGuess(int row, int col);
int hasWon(char board[][BOARD_SIZE]);
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
        scanf("%d %d", &guessRow, &guessCol);  //사용자가 추측하는 군함의 위치

        // 사용자의 추측을 유효성 검사함
        if (!isValidGuess(guessRow, guessCol)) { //사이즈가 벗어나면
            printf("This is a wrong guess! Please enter valid coordinates.\n");
            continue; //다시 while문의 처음으로 감
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
        scanf("%d %d", &guessRow1, &guessCol1);  //사용자가 추측하는 군함의 위치
        if (!isValidGuess(guessRow1, guessCol1)) { //사이즈가 벗어나면
            printf("This is a wrong guess! Please enter valid coordinates.\n");
            goto first_player; //first_player: 이 부분으로 가서 플레이어 1의 입력을 다시 받음 
        }
second_player:
        printf("Player 2: Enter the coordinates you want to guess (row col): ");
        scanf("%d %d", &guessRow2, &guessCol2);
        // 사용자의 추측을 유효성 검사함
        if (!isValidGuess(guessRow2, guessCol2)) { //사이즈가 벗어나면 
            printf("This is a wrong guess! Please enter valid coordinates.\n");
            goto second_player; //second_player: 이부분으로 가서 플레이어 2의 입력을 다시 받음
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

    // 게임 종료, 최종 보드 상태출력 
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
        gamemode(); //잘못입력시 다시 모드 선택하도록 함.
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

// 숨길 배의 위치를 입력받는 함수
void placeShips(char board[][BOARD_SIZE]) {
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

// 유효한 추측인지 확인하는 함수
int isValidGuess(int row, int col) {
    return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE);  //보드 사이즈 안에있으면 T리턴 아니면 F리턴
}

// 모든 전함이 격추되었는지 확인하는 함수
int hasWon(char board[][BOARD_SIZE]) {
    int i, j;    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 'S') {  
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
