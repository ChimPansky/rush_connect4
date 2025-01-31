#include "game.h"
#include "utils/libft/libft.h"

void    print_board(t_board *board) {

    ft_putchar_fd('\n', STDOUT_FILENO);
    for (int row = board->rows - 1; row >= 0; --row) {
        for (int col = 0; col < board->cols; col++) {
            char c = board->fields[row][col].val;
            c = (c == EMPTY) ? '.' : c;
            ft_putchar_fd(c, STDOUT_FILENO);
            ft_putchar_fd(' ', STDOUT_FILENO);
        }
        ft_putchar_fd('\n', STDOUT_FILENO);
    }
    ft_dprintf(STDOUT_FILENO, "\n\n");
}

void    free_board(t_board *board) {
    for (int row = 0; row < board->rows; row++) {
        free(board->fields[row]);
    }
    free(board->fields);
    board->fields = NULL;
}

int init_game(t_game *game, int rows, int cols) {
    if (rows < MIN_BOARD_ROWS || rows > MAX_BOARD_ROWS || cols < MIN_BOARD_COLS || cols > MAX_BOARD_COLS) {
        ft_dprintf(STDERR_FILENO, "Error. Board size must be between %dx%d and %dx%d.\n", MIN_BOARD_ROWS, MIN_BOARD_COLS, MAX_BOARD_ROWS, MAX_BOARD_COLS);
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
    return 0;
}