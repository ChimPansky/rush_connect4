#ifndef AI_MOVE_H
# define AI_MOVE_H

#include "game.h"
#include <stdlib.h>

int get_ai_move(t_game *game) {
    (void)game;
    return rand() % game->board.cols;
}

#endif // AI_MOVE_H