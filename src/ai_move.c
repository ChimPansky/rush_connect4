#include "connect4.h"
#include <stdlib.h>

int get_ai_move(t_game *game) {
    (void)game;
    // Implement your AI here
    return rand() % game->board.cols;
}