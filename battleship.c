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
void singleplay(){ //싱글플레이 함수 
    char board[BOARD_SIZE][BOARD_SIZE];
    int guessRow, guessCol;
    int attempts = 0;
    int a=0;
     // 게임 보드를 초기화하고 전함을 배치함
    initializeBoard(board); //초기화화
    placeShips(board); //배치  -> 랜덤 배치 들어오면 추가해줌.

    // 게임 설명 출력
    printf("=== 전함 게임 ===\n");
    printf("보드 상의 전함 위치를 추측하세요.\n");
    printf("0부터 4까지의 행과 열 번호를 입력하세요.\n");

    // 게임 루프
    while (!hasWon(board)) {  //보드에 전함이 남아있으면
        // 현재 보드 상태 출력
        printf("\n");
        printBoard(board); //군함을 감춰서 출력력

        // 사용자의 다음 수를 입력받음
        printf("추측할 좌표를 입력하세요 (행 열): ");
        scanf("%d %d", &guessRow, &guessCol);  //사용자가 추측하는 군함의 위치치

        // 사용자의 추측을 유효성 검사함
        if (!isValidGuess(guessRow, guessCol)) { //사이즈가 벗어나면
            printf("잘못된 추측입니다! 유효한 좌표를 입력하세요.\n");
            continue; //다시 while문의 처음으로 감감
        }

        // 추측이 전함을 맞췄는지, 실패했는지, 이전에 이미 추측한 위치인지 확인함
        if (board[guessRow][guessCol] == 'S') {
            printf("축하합니다! 전함을 격추했습니다!\n");
            board[guessRow][guessCol] = 'X';  // 'X'는 맞힌 곳을 나타냄
        } else if (board[guessRow][guessCol] == '~') {
            printf("실패했습니다! 다시 시도하세요.\n");
            board[guessRow][guessCol] = 'O';  // 'O'는 실패한 곳을 나타냄
        } else {
            printf("이미 추측한 위치입니다. 다시 시도하세요.\n");
        }

        attempts++; //시도 횟수 증가
    }

    // 게임 종료, 최종 보드 상태와 시도 횟수 출력
    printf("\n");
    printBoard(board);
    printf("축하합니다! 모든 전함을 격추했습니다. 시도 횟수: %d\n", attempts);
    
    rank_input(attempts);
    printf("랭킹표를 확인하시겠습니까 ? 1: O 2: X ");
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


void multplay(){ //멀티플레이 함수 
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
    printf("=== 전함 게임 ===\n");
    printf("보드 상의 전함 위치를 추측하세요.\n");
    printf("0부터 4까지의 행과 열 번호를 입력하세요.\n");

    // 게임 루프
    while (!hasWon(board1) && !hasWon(board2)) {  //보드에 전함이 남아있으면
        // 현재 보드 상태 출력
        printf("\n");
        printBoard(board1); //군함을 감춰서 출력력
        printf("\n\n\n");
        printBoard(board2);
        
        
first_player:
        // 사용자의 다음 수를 입력받음
        printf("1플레이어: 추측할 좌표를 입력하세요 (행 열): ");
        scanf("%d %d", &guessRow1, &guessCol1);  //사용자가 추측하는 군함의 위치치
        if (!isValidGuess(guessRow1, guessCol1)) { //사이즈가 벗어나면
            printf("잘못된 추측입니다! 유효한 좌표를 입력하세요.\n");
            goto first_player; //다시 while문의 처음으로 감감
        }
second_player:
        printf("2플레이어: 추측할 좌표를 입력하세요 (행 열): ");
        scanf("%d %d", &guessRow2, &guessCol2);
        // 사용자의 추측을 유효성 검사함
        if (!isValidGuess(guessRow2, guessCol2)) { //사이즈가 벗어나면   //수정필요요
            printf("잘못된 추측입니다! 유효한 좌표를 입력하세요.\n");
            goto second_player; //다시 while문의 처음으로 감감
        }

        // 추측이 전함을 맞췄는지, 실패했는지, 이전에 이미 추측한 위치인지 확인함
        if (board1[guessRow1][guessCol1] == 'S') {
            printf("1p: 축하합니다! 전함을 격추했습니다!\n");
            board1[guessRow1][guessCol1] = 'X';  // 'X'는 맞힌 곳을 나타냄
        } else if (board1[guessRow1][guessCol1] == '~') {
            printf("1p: 실패했습니다! 다시 시도하세요.\n");
            board1[guessRow1][guessCol1] = 'O';  // 'O'는 실패한 곳을 나타냄
        } else {
            printf("1p: 이미 추측한 위치입니다. 다시 시도하세요.\n");
        }
        if (board2[guessRow2][guessCol2] == 'S') {
            printf("2p: 축하합니다! 전함을 격추했습니다!\n");
            board2[guessRow2][guessCol2] = 'X';  // 'X'는 맞힌 곳을 나타냄
        } else if (board2[guessRow1][guessCol1] == '~') {
            printf("2p: 실패했습니다! 다시 시도하세요.\n");
            board2[guessRow2][guessCol2] = 'O';  // 'O'는 실패한 곳을 나타냄
        } else {
            printf("2p: 이미 추측한 위치입니다. 다시 시도하세요.\n");
        }

        
    }

    // 게임 종료, 최종 보드 상태와 시도 횟수 출력
    printf("\n");
    printf("\n");
    printBoard(board1);
    printf("\n\n\n");
    printBoard(board2);
    
    
    if(hasWon(board1) && hasWon(board2)){
        printf("무승부 입니다");
    }
    if(hasWon(board1) && !hasWon(board2)){
        printf("p1 승리 ! 축하합니다! 모든 전함을 격추했습니다.");
    }
    if(!hasWon(board1) && hasWon(board2)){
        printf("p2 승리 ! 축하합니다! 모든 전함을 격추했습니다.");
    }

}

//싱글 플레이와 멀티 플레이를 선택하는 함수
void gamemode(){
    int n;
    printf("모드를 선택하세요 \n");
    printf("1: 싱글모드 2:멀티모드 ");
    scanf("%d",&n);
    if(n==1){
        singleplay();
    }
    else if(n==2){
        multplay();
    }
    else{
        printf("잘못 입력하셨습니다.\n");
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
        printf("전함 %d의 좌표를 입력하세요 (행 열): ", i + 1); //전함 1 2 3 4의 좌표 입력 -> 출력에 (i+1)과 같은 형태는 좋지 않음 (개선 필요)
        scanf("%d %d", &row, &col); // 행, 열 입력 받음음

        if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) { //보드 사이즈 안에 있는 행과 열이면면
            if (board[row][col] != '~') { //이미 전함이 있으면 
                printf("해당 위치에 이미 전함이 있습니다. 다시 입력하세요.\n");
                i--;
            } else { 
                board[row][col] = 'S';  // 'S'는 전함을 나타냄
            }
        } else {  // 보드 사이즈를 넘어서면 
            printf("잘못된 좌표입니다. 다시 입력하세요.\n");
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
// 플레이어 정보 입력 함수
void rank_input(int score) {
    char player_name[50];

    printf("게임오버 이름입력: ");
    scanf("%s", player_name);

    // 메모장 열기
    FILE* file = fopen("Rank_list.txt", "a");
    if (file == NULL) {
        printf("파일 열기 오류\n");
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
        printf("파일 열기 오류\n");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "Player Name: %49s\tScore: %d\n", players[count].name, &players[count].score) == 2) {
        count++;
        if (count >= max_players) {
            break;
        }
    }

    fclose(file);
    return count;
}

// 점수를 기준으로 내림차순 정렬하는 함수
int compare_scores(const void* a, const void* b) {
    Player* playerA = (Player*)a;
    Player* playerB = (Player*)b;
    return playerA->score - playerB->score; // 내림차순 정렬
}

// 정렬된 결과 출력 함수
void print_sorted_scores(Player players[], int count) {
    printf("\n=== Sorted Scores ===\n");
    for (int i = 0; i < count; i++) {
        printf("%d Player Name: %s\tScore: %d\n",i+1, players[i].name, players[i].score);
    }
}

void showRanking() {
    // 입력받기 (필요시 주석 해제)
    // rank_input();

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

