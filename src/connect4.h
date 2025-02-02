#ifndef GAME_H
# define GAME_H

#include <stdbool.h>
#include "utils/libft/libft.h"
#include "utils/get_next_line/get_next_line.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_BOARD_ROWS 20
#define MAX_BOARD_COLS 20

#define MIN_BOARD_ROWS 6
#define MIN_BOARD_COLS 7

#define MIN_ALGO_DEPTH 6
#define MAX_ALGO_DEPTH 10

#define PLAYER_COLOR "\033[1;33m"  // Yellow
#define AI_COLOR "\033[1;31m"      // Red
#define BOLD "\033[1m"
#define RESET_FORMAT "\033[0m"      // Reset to default
#define PLAYER_COIN "🟡"
#define AI_COIN "🔴"
#define EMPTY_COIN "⚫"
#define VERTICAL_BAR "┃"
#define HORIZONTAL_BAR "━"
#define BOT_LEFT_CORNER "┗"
#define BOT_RIGHT_CORNER "┛"

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

typedef enum s_ai_algo {
    AI_RANDOM,
    AI_GREEDY,
    AI_MINIMAX,
    AI_MINIMAX_AB,
    AI_MONTE_CARLO
}   t_ai_algo;

typedef enum e_text_align {
    ALIGN_LEFT,
    ALIGN_RIGHT,
    ALIGN_CENTER
}   t_text_align;

// game.c
int     init_game(t_game *game, int rows, int cols);
void    play_game(t_game *game);
void    print_game(t_game *game);

// board.c
int     init_board(t_board *board, int rows, int cols);
int     copy_board(t_board *dst, t_board *src);
void    free_board(t_board *board);
bool    check_win(t_board *board, t_field_val player);
bool    check_draw(t_board *board);
void    print_board(t_board *board);

// ai_move.c
int get_ai_move(t_game *game, t_ai_algo ai_algo);

// minimax.c
int minimax_logic(t_game *game);
int getAvailableRow(t_game *game, int col);
int evaluateBoard(t_game *game, t_field_val player);

// minimax_recursion.c
int get_ai_move_minimax(t_game *game, int searchDepth);

// utils/utils.c
void printf_formatted(const char *text, bool bold, const char *color, t_text_align alignment, int col_width);

#endif // GAME_H