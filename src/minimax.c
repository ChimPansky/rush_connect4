#include "connect4.h"

static int evaluateWindow(t_field_val window[4], t_field_val player) {
    int score = 0;
    t_field_val opponent = (player == PLAYER) ? AI : PLAYER;
    int count_ai = 0, countOpponent = 0, countEmpty = 0;
    for (int i = 0; i < 4; i++) {
        if (window[i] == player)
            count_ai++;
        else if (window[i] == opponent)
            countOpponent++;
        else if (window[i] == EMPTY)
            countEmpty++;
    }
    if (count_ai == 4)
        score += 100;
    else if (count_ai == 3 && countEmpty == 1)
        score += 5;
    else if (count_ai == 2 && countEmpty == 2)
        score += 2;
    else if (countOpponent == 3 && countEmpty == 1)
        score -= 100;
    if (countOpponent == 4)
        return -100;
    return score;
}

int evaluateBoard(t_game *game, t_field_val player) {
    int score = 0, rows = game->board.rows, cols = game->board.cols;
    int centerCol = cols / 2, centerCount = 0;
    t_field_val window[4];

    for (int r = 0; r < rows; r++) {
        if (game->board.fields[r][centerCol].val == player)
            centerCount++;
    }
    score += centerCount * 5;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols - 3; c++) {
            window[0] = game->board.fields[r][c].val;
            window[1] = game->board.fields[r][c + 1].val;
            window[2] = game->board.fields[r][c + 2].val;
            window[3] = game->board.fields[r][c + 3].val;
            score += evaluateWindow(window, player);
        }
    }
    for (int c = 0; c < cols; c++) {
        for (int r = 0; r < rows - 3; r++) {
            window[0] = game->board.fields[r][c].val;
            window[1] = game->board.fields[r + 1][c].val;
            window[2] = game->board.fields[r + 2][c].val;
            window[3] = game->board.fields[r + 3][c].val;
            score += evaluateWindow(window, player);
        }
    }
    for (int r = 0; r < rows - 3; r++) {
        for (int c = 0; c < cols - 3; c++) {
            window[0] = game->board.fields[r][c].val;
            window[1] = game->board.fields[r + 1][c + 1].val;
            window[2] = game->board.fields[r + 2][c + 2].val;
            window[3] = game->board.fields[r + 3][c + 3].val;
            score += evaluateWindow(window, player);
        }
    }
    for (int r = 3; r < rows; r++) {
        for (int c = 0; c < cols - 3; c++) {
            window[0] = game->board.fields[r][c].val;
            window[1] = game->board.fields[r - 1][c + 1].val;
            window[2] = game->board.fields[r - 2][c + 2].val;
            window[3] = game->board.fields[r - 3][c + 3].val;
            score += evaluateWindow(window, player);
        }
    }
    return score;
}

int getAvailableRow(t_game *game, int col) {
    for (int r = 0; r < game->board.rows; r++) {
        if (game->board.fields[r][col].val == EMPTY)
            return r;
    }
    return -1;
}
