#ifndef GAME_H
# define GAME_H

# include <stdbool.h>

# define MAX_BOARD_ROWS 10
# define MAX_BOARD_COLS 10

# define MIN_BOARD_ROWS 6
# define MIN_BOARD_COLS 7

#include "utils/libft/libft.h"
#include "utils/get_next_line/get_next_line.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef enum e_field_val {
    EMPTY = 0,
    PLAYER = 'X',
    AI = 'O'
}   t_field_val;

typedef struct s_field {
    t_field_val	val;
}			t_field;

typedef struct s_board {
    t_field **fields;
    int		rows;
    int		cols;
}			t_board;

typedef enum e_game_state {
    NOT_STARTED = 0,
    PLAYER_TURN,
    AI_TURN,
    PLAYER_WON,
    AI_WON,
    DRAW
}   t_game_state;

typedef struct s_game {
    t_board	board;
    t_game_state    state;
    int		depth;
}			t_game;

// game.c
int     init_game(t_game *game, int rows, int cols);
void    play_game(t_game *game);
void    print_game(t_game *game);

// board.c
void    free_board(t_board *board);
bool    check_win(t_board *board, t_field_val player);
bool    check_draw(t_board *board);
void    print_board(t_board *board);

// ai_move.c
int     get_ai_move(t_game *game);

#endif // GAME_H