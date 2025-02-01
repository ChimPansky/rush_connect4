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
        score += 10000;
    else if (count_ai == 3 && countEmpty == 1)
        score += 5;
    else if (count_ai == 2 && countEmpty == 2)
        score += 2;
    if (countOpponent == 3 && countEmpty == 1)
        score -= 4;
    return score;
}


static int evaluateBoard(t_game *game, t_field_val player) {
    int score = 0, rows = game->board.rows, cols = game->board.cols;
    int centerCol = cols / 2, centerCount = 0;
    t_field_val window[4];

    for (int r = 0; r < rows; r++) {
        if (game->board.fields[r][centerCol].val == player)
            centerCount++;
    }
    score += centerCount * 3;
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

static bool isValidMove(t_game *game, int col) {
    return game->board.fields[game->board.rows - 1][col].val == EMPTY;
}

static int getAvailableRow(t_game *game, int col) {
    for (int r = 0; r < game->board.rows; r++) {
        if (game->board.fields[r][col].val == EMPTY)
            return r;
    }
    return -1;
}

int minimax_logic(t_game *game) {
    int bestScore = -1000000, bestCol = 0;
    for (int col = 0; col < game->board.cols; col++) {
        if (isValidMove(game, col)) {
            int row = getAvailableRow(game, col);
            game->board.fields[row][col].val = AI;
            int score = evaluateBoard(game, AI);
            game->board.fields[row][col].val = EMPTY;
            if (score > bestScore) {
                bestScore = score;
                bestCol = col;
            }
        }
    }
    return bestCol;
}