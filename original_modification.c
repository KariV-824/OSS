//by ?scar Poblete S?enz
#include <stdio.h>
#define BOARD_SIZE 5 // ���� ũ�� ����
#define SHIPS_COUNT 4 // ���� �� ����
void initializeBoard(char board[][BOARD_SIZE]) { // �ʱ�ȭ�� �������� �����ϴ� �Լ�, 2���� ���� �迭�� �Ű������� ����
    int i, j;
    for(i = 0; i < BOARD_SIZE; i++) {
        for(j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = '~'; // �⺻ ���ð��� ���� '~'�� �ʱ�ȭ
        }
    }
}
void printBoard(char board[][BOARD_SIZE]) { // �������� ���¸� ����ϴ� �Լ�
    int i, j;
    for(i = 0; i < BOARD_SIZE; i++) {
        for(j = 0; j < BOARD_SIZE; j++) {
            if(board[i][j] == '~' || board[i][j] == 'O' || board[i][j] == 'X') { 
                printf
                ("%c", board[i][j]); 
            } 
            else{ 
                printf("~ "); // �ش� �ڸ��� S�̸� '~'�� ǥ���ؼ� ����
            }
        }
        printf("\n");
    }
}
void placeShips(char board[][BOARD_SIZE]) {// ���� ���� ��ġ�� �Է¹޴� �Լ�
    int i;
    for(i = 0; i < SHIPS_COUNT; i++) {
        int row, col;
        printf("Enter the coordinates for Ship %d(row column): ", i + 1);
        int result = scanf("%d %d", &row, &col); // 2���� ������ �Է¹޾Ƽ� result�� ����
        if(result == 2) { // 2���� ������ �ԷµǾ������� ����
            if(getchar() != '\n') { // 2���� ���� ���Ŀ� �߰� ���ڰ� ���ۿ� �����ִٸ�
                printf("Too many inputs. Only enter two numbers. Try again.\n"); 
                while(getchar() != '\n'); // ���ۿ� ���� ��� ���ڸ� ������ '\n'�� ���� ������ �ݺ�  
                i--; // i�� ���ҽ��� �̹� �Է��� ��ȿȭ�ϰ�, �Է��� �ٽ� �޵��� ��
                continue; // for ������ ó������ ���ư� �����
            }
            
            if(row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) {
                if(board[row][col] != '~') {
                    printf("There is already a ship at that location. Try again.\n");
                    i--;// �߸��� ��ġ �Է� �� �ٽ� �Է�
                } 
                else{
                    board[row][col] = 'S';
                }
            } 
            else{
                printf("Invalid coordinates. Try again.\n");
                i--;// ���� �� ��ǥ �Է� �� �ٽ� �Է�
            }
        } 
        else{ // �Է¹��� �����Ͱ� 2���� ������ �ƴ϶��
            printf("Invalid input. You need to enter two numbers. Try again.\n");
            while(getchar() != '\n'); // ���ۿ� ���� ��� ���ڸ� ������ '\n'�� ���� ������ �ݺ�
            i--; // i�� ���ҽ��� �̹� �Է��� ��ȿȭ�ϰ�, �Է��� �ٽ� �޵��� ��
        }
    }
}
int isValidGuess(int row, int col) { // ������ ���� ������ ��ȿ������ Ȯ���ϴ� �Լ�, intŸ���� row, col ���ڸ� ����
    return(row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE); // ��ȿ�ϸ� 1, ��ȿ���� ������ 0 ��ȯ
}
int hasWon(char board[][BOARD_SIZE]) { // ��� �谡 ���ߵǾ������� Ȯ���ϴ� �Լ�
    int i, j;
    for(i = 0; i < BOARD_SIZE; i++) {
        for(j = 0; j < BOARD_SIZE; j++) {
            if(board[i][j] == 'S') { 
                return 0; // �����ǿ� �谡 �����ִٸ� 0�� ��ȯ
            }
        }
    }
    return 1; // �����ǿ� �谡 ���ٸ� 1�� ��ȯ(�¸�)
}
int main() { 
    char board[BOARD_SIZE][BOARD_SIZE];
    int guessRow, guessCol;
    int attempts = 0;
    initializeBoard(board); 
    placeShips(board);
    printf("=== Battleship Game ===\n");
    printf("Guess the location of the ships on the board.\n");
    printf("Enter row and column numbers between 0 and 4.\n");
    while(!hasWon(board)) { // hasWon�Լ��� 0�� ��ȯ�ϴ� ����(�����ǿ� �谡 �����ִ� ����) �ݺ�
        printf("\n");
        printBoard(board);
        printf("Enter your guess (row column): ");
        scanf("%d %d", &guessRow, &guessCol);
        if(!isValidGuess(guessRow, guessCol)) { // isValidGuess�Լ��� 0�� ��ȯ�ϸ�
            printf("Invalid guess! Please enter valid coordinates.\n");
            continue; // while���� ó������ �Ѿ
        }
        if(board[guessRow][guessCol] == 'S') {
            printf("Congratulations! You hit a ship!\n");
            board[guessRow][guessCol] = 'O'; // ���߸� 'S'���� 'O'�� ����
        } 
        else if(board[guessRow][guessCol] == '~') {
            printf("Missed! Try again.\n");
            board[guessRow][guessCol] = 'X'; // Ʋ���� '~'���� 'X'�� ����
        } 
        else{
            printf("You've already guessed this location. Try again.\n"); 
        }
        attempts++;
    }
    printf("\n");
    printBoard(board);
    printf("Congratulations! You sunk all the ships in %dattempts.\n", attempts);
    return 0;
}