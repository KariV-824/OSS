# Battleship Game

Simple implementation of the classic game Battleship written in C. The game allows players to guess the location of hidden ships on a game board.

## How to Play

1. The game board is a square grid with a size of 5x5.
2. The objective of the game is to sink all the ships hidden on the board.
3. At the beginning of the game, the board is empty and all cells are represented by the symbol '~'.
4. The player will be prompted to enter the coordinates (row and column) for each ship they want to place on the board.
5. The player can place up to 4 ships on the board.
6. Once all the ships are placed, the game begins.
7. The player is prompted to guess the location of the ships by entering the coordinates (row and column) of a cell on the board.
8. If the guess is valid (within the bounds of the board), the game checks if the guessed cell contains a ship or not.
   - If a ship is present, the player scores a hit and the cell is marked with an 'X'.
   - If no ship is present, the player misses and the cell is marked with an 'O'.
   - If the player guesses the same cell again, they are prompted to try again.
9. The player continues making guesses until all ships have been sunk.
10. The game ends when all ships have been sunk, and the player is informed of their success along with the number of attempts made.

## Implementation Details

The game is implemented using the C programming language and consists of the following functions:

- **initializeBoard**: Initializes the game board by setting all cells to the empty symbol '~'.
- **printBoard**: Prints the current state of the game board, hiding ship locations with '~'.
- **placeShips**: Allows the player to place ships on the board by entering the coordinates (row and column) for each ship.
- **isValidGuess**: Checks if a guess is valid by verifying if the coordinates are within the bounds of the board.
- **hasWon**: Checks if all the ships have been sunk, indicating whether the player has won the game.
- **main**: The main function that controls the flow of the game. It initializes the board, places the ships, and handles the player's guesses until the game is won.

## Compilation and Execution

To compile the program, save the code into a file named `battleship.c` and use a C compiler to compile it, for example:

`gcc battleship.c -o battleship`

To run the compiled program, execute the following command:

`./battleship`

Follow the prompts on the screen to play the game.

Enjoy playing Battleship!



