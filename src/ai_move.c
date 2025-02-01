#ifndef AI_MOVE_H
# define AI_MOVE_H

#include "connect4.h"
#include <stdlib.h>

int get_ai_move(t_game *game, t_ai_algo ai_algo) {
    if (ai_algo == AI_RANDOM) {
        return rand() % game->board.cols;
    } else if (ai_algo == AI_GREEDY) {
        return 0; // Implement your AI here
    } else if (ai_algo == AI_MINIMAX) {
        return 0; // Implement your AI here
    } else if (ai_algo == AI_MINIMAX_AB) {
        return 0; // Implement your AI here
    } else if (ai_algo == AI_MONTE_CARLO) {
        return 0; // Implement your AI here
    }
    return 0;
}

#endif // AI_MOVE_H