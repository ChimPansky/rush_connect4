#include "connect4.h"

static bool is_terminal(t_game *game) {
    return (game->state == PLAYER_WON || game->state == AI_WON || game->state == DRAW);
}

int minimax(t_game *game, int depth, bool maximizingPlayer) {
    if (depth == 0 || is_terminal(game))
        return evaluateBoard(game, AI);  // Evaluate from AI's perspective

    int cols = game->board.cols;
    if (maximizingPlayer) {
        int maxEval = -1000000;
        for (int col = 0; col < cols; col++) {
            if (isValidMove(game, col)) {
                int row = getAvailableRow(game, col);
                game->board.fields[row][col].val = AI; // simulate AI move
                int eval = minimax(game, depth - 1, false);
                game->board.fields[row][col].val = EMPTY; // undo move
                if (eval > maxEval)
                    maxEval = eval;
            }
        }
        return maxEval;
    } else {
        int minEval = 1000000;
        for (int col = 0; col < cols; col++) {
            if (isValidMove(game, col)) {
                int row = getAvailableRow(game, col);
                game->board.fields[row][col].val = PLAYER; // simulate player move
                int eval = minimax(game, depth - 1, true);
                game->board.fields[row][col].val = EMPTY; // undo move
                if (eval < minEval)
                    minEval = eval;
            }
        }
        return minEval;
    }
}

int get_ai_move_minimax(t_game *game, int searchDepth) {
    int bestScore = -1000000, bestCol = 0;
    for (int col = 0; col < game->board.cols; col++) {
        if (isValidMove(game, col)) {
            int row = getAvailableRow(game, col);
            game->board.fields[row][col].val = AI;
            int score = minimax(game, searchDepth - 1, false);
            game->board.fields[row][col].val = EMPTY;
            if (score > bestScore) {
                bestScore = score;
                bestCol = col;
            }
        }
    }
    return bestCol;
}
