#include "utils/libft/libft.h"
#include "utils/get_next_line/get_next_line.h"
#include "game.h"
#include <stdio.h>

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
    if (init_game(&game, ft_atoi(argv[1]), ft_atoi(argv[2])) != 0) {
        return 1;
    }
    game.board.fields[0][0].val = PLAYER;
    game.board.fields[0][3].val = AI;
    game.board.fields[1][1].val = PLAYER;
    game.board.fields[1][4].val = AI;
    print_board(&game.board);
    free_board(&game.board);

    return 0;
}