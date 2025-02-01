#include "connect4.h"
#include "utils/libft/libft.h"

void free_board(t_board *board) {
    for (int row = 0; row < board->rows; row++) {
        free(board->fields[row]);
    }
    free(board->fields);
    board->fields = NULL;
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
    // Print top border
    ft_putchar_fd('+', STDOUT_FILENO);
    for (int col = 0; col < board->cols; col++) {
        ft_putchar_fd(' ', STDOUT_FILENO);
        ft_putchar_fd(' ', STDOUT_FILENO);
    }
    ft_putchar_fd('+', STDOUT_FILENO);
    ft_putchar_fd('\n', STDOUT_FILENO);

    for (int row = board->rows - 1; row >= 0; --row) {
        ft_putchar_fd('|', STDOUT_FILENO); // Left border
        for (int col = 0; col < board->cols; col++) {
            char c = board->fields[row][col].val;
            c = (c == EMPTY) ? '.' : c;
            ft_putchar_fd(c, STDOUT_FILENO);
            ft_putchar_fd(' ', STDOUT_FILENO);
        }
        ft_putchar_fd('|', STDOUT_FILENO); // Right border
        ft_putchar_fd('\n', STDOUT_FILENO);
    }

    // Print bottom border
    ft_putchar_fd('+', STDOUT_FILENO);
    for (int col = 0; col < board->cols; col++) {
        ft_putchar_fd('-', STDOUT_FILENO);
        ft_putchar_fd('-', STDOUT_FILENO);
    }
    ft_putchar_fd('+', STDOUT_FILENO);
    ft_putchar_fd('\n', STDOUT_FILENO);
}