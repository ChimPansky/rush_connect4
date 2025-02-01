#include "connect4.h"
#include "utils/libft/libft.h"
#include "utils/get_next_line/get_next_line.h"

void print_game(t_game *game) {
    ft_dprintf(STDOUT_FILENO, "\n===============\n\n");
    if (game->state == AI_TURN)
        ft_dprintf(STDOUT_FILENO, "  AI'S TURN\n");
    else if (game->state == PLAYER_TURN)
        ft_dprintf(STDOUT_FILENO, "PLAYER'S TURN\n");
    else if (game->state == PLAYER_WON)
        ft_dprintf(STDOUT_FILENO, "  PLAYER WON\n");
    else if (game->state == AI_WON)
        ft_dprintf(STDOUT_FILENO, "   AI WON\n");
    else if (game->state == DRAW)
        ft_dprintf(STDOUT_FILENO, "    DRAW\n");
    print_board(&game->board);
}

int init_game(t_game *game, int rows, int cols) {
    if (rows < MIN_BOARD_ROWS || rows > MAX_BOARD_ROWS || cols < MIN_BOARD_COLS ||
        cols > MAX_BOARD_COLS) {
        ft_dprintf(STDERR_FILENO,
                   "Error. Board size must be between %dx%d and %dx%d.\n",
                   MIN_BOARD_ROWS, MIN_BOARD_COLS, MAX_BOARD_ROWS, MAX_BOARD_COLS);
        return 1;
    }
    game->board.rows = rows;
    game->board.cols = cols;
    game->board.fields = (t_field **)malloc(sizeof(t_field *) * rows);
    if (game->board.fields == NULL) {
        ft_dprintf(STDERR_FILENO, "Error. Memory allocation failed.\n");
        return 1;
    }
    for (int row = 0; row < rows; row++) {
        game->board.fields[row] = (t_field *)malloc(sizeof(t_field) * cols);
        if (game->board.fields[row] == NULL) {
            ft_dprintf(STDERR_FILENO, "Error. Memory allocation failed.\n");
            while (--row) {
                free(game->board.fields[row]);
            }
            return 1;
        }
        ft_bzero(game->board.fields[row], sizeof(t_field) * cols);
    }
    game->state = (rand() % 2 == 0) ? PLAYER_TURN : AI_TURN;
    return 0;
}

int get_player_input() {
    char *col_str = NULL;
    int gnl_error = 0;
    ft_dprintf(STDOUT_FILENO, "Enter column number: ");
    while ((col_str = get_next_line(STDIN_FILENO, &gnl_error)) == NULL) {
        ft_dprintf(STDOUT_FILENO, "Enter column number: ");
    }
    int chosen_col = ft_atoi(col_str);  // replace this with a stricter function. right now even "sdnfkjsdnf" returns 0 and is considered valid input
    free(col_str);
    return (chosen_col);
}

void    update_game_state(t_game *game) {
    if (check_win(&game->board, PLAYER)) {
        game->state = PLAYER_WON;
    } else if (check_win(&game->board, AI)) {
        game->state = AI_WON;
    } else if (check_draw(&game->board)) {
        game->state = DRAW;
    } else if (game->state == PLAYER_TURN) {
        game->state = AI_TURN;
    } else {
        game->state = PLAYER_TURN;
    }
}

static bool validate_move(t_game *game, int col) {
    if (col < 0 || col >= game->board.cols) {
        ft_dprintf(STDOUT_FILENO, "Invalid column number. Try again.\n");
        return false;
    }
    for (int row = 0; row < game->board.rows; row++) {
        if (game->board.fields[row][col].val == EMPTY) {
            return true;
        }
    }
    ft_dprintf(STDOUT_FILENO, "Column is full. Try again.\n");
    return false;
}

static void make_move(t_game *game, int col) {
    for (int row = 0; row < game->board.rows; row++) {
        if (game->board.fields[row][col].val == EMPTY) {
            game->board.fields[row][col].val = (game->state == PLAYER_TURN) ? PLAYER : AI;
            break;
        }
    }
}

void play_game(t_game *game) {
    int chosen_col = -1;
    bool valid_player_move = false;
    if (game->state == AI_TURN) {
        chosen_col = get_ai_move(game);
        ft_dprintf(STDOUT_FILENO, "AI plays: %d\n", chosen_col);
    } else {
        while (!valid_player_move) {
            chosen_col = get_player_input();
            ft_dprintf(STDOUT_FILENO, "Player chose: %d\n", chosen_col);
            valid_player_move = validate_move(game, chosen_col);
        }
    }
    make_move(game, chosen_col);
    update_game_state(game);
}
