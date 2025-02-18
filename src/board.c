#include "connect4.h"
#include "utils/libft/libft.h"

const char *get_coin_color(t_field_val val) {
    if (val == PLAYER) {
        return PLAYER_COIN;
    } else if (val == AI) {
        return AI_COIN;
    } else {
        return EMPTY_COIN;
    }
}

void free_board(t_board *board) {
    for (int row = 0; row < board->rows; row++) {
        free(board->fields[row]);
    }
    free(board->fields);
    board->fields = NULL;
}

// how to use:
/*
t_board new_board;
if (copy_board(&new_board, &old_board) != 0) {
    return 1;
}
print_board(&new_board);
free_board(&new_board);
*/
int copy_board(t_board *dst, t_board *src) {
    dst->rows = src->rows;
    dst->cols = src->cols;
    dst->fields = (t_field **)malloc(sizeof(t_field *) * src->rows);
    if (dst->fields == NULL) {
        ft_dprintf(STDERR_FILENO, "Error. Memory allocation failed.\n");
        return 1;
    }
    for (int row = 0; row < src->rows; row++) {
        dst->fields[row] = (t_field *)malloc(sizeof(t_field) * src->cols);
        if (dst->fields[row] == NULL) {
            ft_dprintf(STDERR_FILENO, "Error. Memory allocation failed.\n");
            while (--row) {
                free(dst->fields[row]);
            }
            return 1;
        }
        ft_memcpy(dst->fields[row], src->fields[row], sizeof(t_field) * src->cols);
    }
    return 0;
}

int init_board(t_board *board, int rows, int cols) {
    board->rows = rows;
    board->cols = cols;
    board->fields = (t_field **)malloc(sizeof(t_field *) * rows);
    if (board->fields == NULL) {
        ft_dprintf(STDERR_FILENO, "Error. Memory allocation failed.\n");
        return 1;
    }
    for (int row = 0; row < rows; row++) {
        board->fields[row] = (t_field *)malloc(sizeof(t_field) * cols);
        if (board->fields[row] == NULL) {
            ft_dprintf(STDERR_FILENO, "Error. Memory allocation failed.\n");
            while (--row > 0) {
                free(board->fields[row]);
            }
            free(board->fields);
            return 1;
        }
        ft_bzero(board->fields[row], sizeof(t_field) * cols);
    }
    return 0;
}

bool    check_win(t_board *board, t_field_val player) {
    for (int row = 0; row < board->rows; row++) {
        for (int col = 0; col < board->cols; col++) {
            if (board->fields[row][col].val == player) {
                // check horizontal
                if (col + 3 < board->cols &&
                    board->fields[row][col + 1].val == player &&
                    board->fields[row][col + 2].val == player &&
                    board->fields[row][col + 3].val == player) {
                    return true;
                }
                // check vertical
                if (row + 3 < board->rows &&
                    board->fields[row + 1][col].val == player &&
                    board->fields[row + 2][col].val == player &&
                    board->fields[row + 3][col].val == player) {
                    return true;
                }
                // check diagonal
                if (row + 3 < board->rows && col + 3 < board->cols &&
                    board->fields[row + 1][col + 1].val == player &&
                    board->fields[row + 2][col + 2].val == player &&
                    board->fields[row + 3][col + 3].val == player) {
                    return true;
                }
                if (row + 3 < board->rows && col - 3 >= 0 &&
                    board->fields[row + 1][col - 1].val == player &&
                    board->fields[row + 2][col - 2].val == player &&
                    board->fields[row + 3][col - 3].val == player) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool    check_draw(t_board *board) {
    for (int col = 0; col < board->cols; col++) {
        if (board->fields[board->rows - 1][col].val == EMPTY) {
            return false;
        }
    }
    return true;
}

void print_board(t_board *board) {
    for (int row = board->rows - 1; row >= 0; --row) {
        ft_printf(VERTICAL_BAR);
        for (int col = 0; col < board->cols; col++) {
            const char *coin = get_coin_color(board->fields[row][col].val);
            ft_printf("%s"VERTICAL_BAR, coin);
        }
        ft_printf("\n");
    }

    // Print bottom border
    ft_printf(BOT_LEFT_CORNER);
    for (int col = 0; col < board->cols; col++) {
        if (col < board->cols - 1) {
            ft_printf(HORIZONTAL_BAR HORIZONTAL_BAR HORIZONTAL_BAR);
        } else {
            ft_printf(HORIZONTAL_BAR HORIZONTAL_BAR);
        }
    }
    ft_printf(BOT_RIGHT_CORNER"\n");
    for (int col = 0; col < board->cols; col++) {
        ft_printf("%3d", col + 1);
    }
    ft_printf("\n\n");
}