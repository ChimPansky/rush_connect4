#include "connect4.h"
// allowed functions:
// stdlib.h: malloc(), free(), rand(), srand()
// time.h: time()

int main (int argc, char **argv) {
    if (argc != 3) {
        ft_dprintf(STDERR_FILENO, "Error. Usage: %s <lines> <columns>\n", argv[0]);
        return 1;
    }
    t_game game;
    ft_bzero(&game, sizeof(t_game));
    srand(time(NULL));
    if (init_game(&game, ft_atoi(argv[1]), ft_atoi(argv[2])) != 0) {
        return 1;
    }
    while (game.state != PLAYER_WON && game.state != AI_WON && game.state != DRAW) {
        print_game(&game);
        play_game(&game);
    }
    print_game(&game);
    free_board(&game.board);
    return 0;
}