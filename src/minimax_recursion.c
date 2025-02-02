#include "connect4.h"

void sort_moves_by_center(int *moves, int size, int centerCol) {
    for (int i = 1; i < size; i++) {
        int key = moves[i];
        int j = i - 1;

        while (j >= 0 && ft_abs(centerCol - moves[j]) > ft_abs(centerCol - key)) {
            moves[j + 1] = moves[j];
            j--;
        }
        moves[j + 1] = key;
    }
}

static bool is_terminal(t_game *game) {
    return (game->state == PLAYER_WON || game->state == AI_WON || game->state == DRAW);
}

int minimax(t_game *game, int depth, int alpha, int beta, bool maximizingPlayer) {
    if (depth == 0 || is_terminal(game))
        return evaluateBoard(game, AI);

    int cols = game->board.cols;

    if (maximizingPlayer) {
        int maxEval = -1000000;
        for (int col = 0; col < cols; col++) {
            if (getAvailableRow(game, col) != -1) {
                int row = getAvailableRow(game, col);
                game->board.fields[row][col].val = AI;
                int eval = minimax(game, depth - 1, alpha, beta, false);
                game->board.fields[row][col].val = EMPTY;

                maxEval = (eval > maxEval) ? eval : maxEval;
                alpha = (alpha > eval) ? alpha : eval;

                if (beta <= alpha)
                    break;
            }
        }
        return maxEval;
    } else {
        int minEval = 1000000;
        for (int col = 0; col < cols; col++) {
            if (getAvailableRow(game, col) != -1) {
                int row = getAvailableRow(game, col);
                game->board.fields[row][col].val = PLAYER;
                int eval = minimax(game, depth - 1, alpha, beta, true);
                game->board.fields[row][col].val = EMPTY;

                minEval = (eval < minEval) ? eval : minEval;
                beta = (beta < eval) ? beta : eval;

                if (beta <= alpha)
                    break;
            }
        }
        return minEval;
    }
}

int get_ai_move_minimax(t_game *game, int searchDepth) {
    int bestScore = -1000000, bestCol = 0;
    int alpha = -1000000, beta = 1000000;
    int cols = game->board.cols;

    int moveOrder[cols];  
    for (int i = 0; i < cols; i++) 
        moveOrder[i] = i;

    int centerCol = cols / 2;
    sort_moves_by_center(moveOrder, cols, centerCol);

    for (int i = 0; i < cols; i++) {
        int col = moveOrder[i];  
        if (getAvailableRow(game, col) != -1) {
            int row = getAvailableRow(game, col);
            game->board.fields[row][col].val = AI;
            int score = minimax(game, searchDepth - 1, alpha, beta, false);
            game->board.fields[row][col].val = EMPTY;

            if (score > bestScore) {
                bestScore = score;
                bestCol = col;
            }
            alpha = (alpha > score) ? alpha : score;
        }
    }

    return bestCol;
}
