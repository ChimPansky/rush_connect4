# Connect 4 (Terminal Game in C)

Rush-Project of the 42 Common Core (written in a team of 2 within 1 weekend)

## Overview

This is a **Connect 4** game implemented in C, playable in the terminal. The game supports a human player against an AI opponent. Players take turns dropping pieces into a grid with a configurable size. The first player to connect four of their pieces vertically, horizontally, or diagonally wins the game.

## Features

* Classic **Connect 4** gameplay
* **AI Opponent** with competitive decision-making
* Configurable grid size (minimum **6 rows x 7 columns**)
* Randomized first turn (either player or AI starts)
* Command-line interface (CLI) for simplicity

## Installation

### Prerequisites

Ensure you have a C compiler installed, such as **cc**.

### Compilation

To compile the game, use the provided **Makefile**:

```
make
```

### Running the Game

After compilation, run the executable with the desired grid size:

```
./connect4 <rows> <columns>
```

Example:

```
./connect4 8 10
```

### Grid Size Rules

* Minimum size: **6 rows x 7 columns**
* If invalid dimensions are provided, the program will display an error and exit.

## How to Play

1. The game randomly selects whether the player or the AI starts.
2. The current state of the grid is displayed before each move.
3. On the player's turn, enter a valid column number to drop a piece.
   * If the move is invalid (column full or out-of-range), the program will prompt again.
4. The AI plays automatically on its turn.
5. The game continues until a player gets **four in a row** (horizontally, vertically, or diagonally) or the board is full (resulting in a draw).
6. The game announces the winner or declares a draw, then exits.

## Controls

* Enter a column number within the allowed range.
* The game will reject invalid inputs and prompt again.

## Example Gameplay

```
  AI'S TURN
+              +
|. . . . . . . |
|. . . . . . . |
|X O . . . . . |
|X O . . . . . |
|O X . X . . . |
|X O . O X O . |
+--------------+
```

## License

This project is licensed under the **MIT License**. See `<span>LICENSE</span>` for details.

## Contributions

Contributions are welcome! Feel free to fork the repository, make improvements, and submit a pull request.

## Author

Developed by ...

## Acknowledgments

* Inspired by the classic **Connect 4** board game.
* Special thanks to the 42 Vienna programming school.
