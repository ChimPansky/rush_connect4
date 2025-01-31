#ifndef GAME_H
# define GAME_H

# define MAX_BOARD_ROWS 10
# define MAX_BOARD_COLS 10

# define MIN_BOARD_ROWS 6
# define MIN_BOARD_COLS 7

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

void    print_game(t_game *game);
void    print_board(t_board *board);
void    free_board(t_board *board);
int     init_game(t_game *game, int rows, int cols);
void    play_game(t_game *game);

int     get_ai_move();

#endif // GAME_H