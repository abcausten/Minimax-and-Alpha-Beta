# Tic-Tac-Toe: Minimax and Alpha-Beta Pruning (C++)

This code was written in Fall 2025 with all six of the function listed below with some changes made in Fall 2026. This implements the **minimax** and **alpha-beta pruning** algorithms to play Tic-Tac-Toe optimally so that the AI will at worst draw. Player 1 (`x`) is the maximizing player, and Player 2 (`o`) is the minimizing player.

## Board Representation

The board is a string of 9 characters, with positions numbered 0 to 8 in row order:

```
 0 | 1 | 2
---+---+---
 3 | 4 | 5
---+---+---
 6 | 7 | 8
```

| Character | Meaning |
|-----------|---------|
| `x` or `X` | Player 1 has moved there |
| `o` or `O` | Player 2 has moved there |
| `.` | Empty square |

For example, `"xx.oo...."` is:

```
 x | x | .
---+---+---
 o | o | .
---+---+---
 . | . | .
```

## Functions

| Function | Purpose |
|----------|---------|
| `int eval(string state)` | Checks whether someone has won |
| `double maxvalue(string state, int &move)` | Minimax value of a state where `x` is to move |
| `double minvalue(string state, int &move)` | Minimax value of a state where `o` is to move |
| `double maxvalueAB(string state, double alpha, double beta, int &move)` | `maxvalue` with alpha-beta pruning |
| `double minvalueAB(string state, double alpha, double beta, int &move)` | `minvalue` with alpha-beta pruning |
| `int minimaxAB(string state, bool xturn)` | Returns the best move (0-8) found with alpha-beta pruning |

All other functions are helper functions to visualize the board and play the game. 

### `eval`

Converts the state to lowercase, then checks all 8 winning lines: 3 rows, 3 columns, and 2 diagonals.

| Return value | Meaning |
|--------------|---------|
| `1` | `x` has three in a row |
| `-1` | `o` has three in a row |
| `0` | no winner yet (the game may or may not be over) |

### `maxvalue` and `minvalue` (Minimax)

The two functions call each other, alternating between the players' turns.

1. **Terminal test:** if `eval` is non-zero or the board has no empty squares, return `eval(state)`. A full board with no winner is a draw (0).
2. **Max player (`x`):** try every empty square, place an `x`, and call `minvalue` on the result. Keep the largest value and remember the square that produced it in `move`.
3. **Min player (`o`):** the same, but place an `o`, call `maxvalue`, and keep the smallest value.

Values are 1 (x wins), 0 (draw), or -1 (o wins) under perfect play. The `move` reference parameter returns the best square for the player to move.

### `minimaxAB` (Alpha-Beta Pruning)

Alpha-beta pruning returns the **same value and best move quality** as minimax, but skips branches that cannot affect the result.

- **alpha** is the best value the maximizer is already guaranteed along the current path.
- **beta** is the best value the minimizer is already guaranteed.
- In `maxvalueAB`, alpha rises as better moves are found, and the search stops (prunes) as soon as `v >= beta`.
- In `minvalueAB`, beta falls as better moves are found, and the search stops as soon as `v <= alpha`.

`minimaxAB(state, xturn)` starts with `alpha = -10000` and `beta = 10000`, then calls `maxvalueAB` if it is `x`'s turn or `minvalueAB` if it is `o`'s. It returns the chosen square.

## Output and Usage

The program starts with an output for running the eval function which will be a board state and the evaluation on wether or not it is a winning state or not. 
The next part of the program will allow the user to play against the models in which the user can input board moves. 

```
      0     1     2

         |     |
0     X  |     |
         |     |
    -----+-----+-----
         |     |
1        |     |
         |     |
    -----+-----+-----
         |     |
2        |     |
         |     |

O-player, enter the coordinates of where you want to play (row then column):
```
The format here would be row column so if you wanted to put an o in row 1 and column 1 it would be 1 1, with the spacing being necessary. 

## Complexity

With branching factor b and depth d:

| Algorithm | Time |
|-----------|------|
| Minimax | O(b^d) |
| Alpha-beta, worst case | O(b^d) |
| Alpha-beta, best move ordering | O(b^(d/2)) |


## Build and Run

```
g++ -std=c++17 -o tictactoe Minimax_and_Alpha_Beta.cpp
./tictactoe (for mac)
.\tictactoe.exe (for windows)
```

## Limitations
- Empty squares must be written as `.`. The assignment also allows `' '`, but this code treats only `.` as empty, so a board with spaces would be treated as full.
