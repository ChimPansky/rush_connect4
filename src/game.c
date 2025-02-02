#include "connect4.h"
#include "utils/libft/libft.h"
#include "utils/get_next_line/get_next_line.h"

int calculate_depth(int rows, int cols) {
    int min_sum = MIN_BOARD_ROWS + MIN_BOARD_COLS;
    int max_sum = MAX_BOARD_ROWS + MAX_BOARD_COLS;
    int cur_sum = rows + cols;

    if (cur_sum <= min_sum) return MAX_ALGO_DEPTH;
    if (cur_sum >= max_sum) return MIN_ALGO_DEPTH;

    double factor = (double)(cur_sum - min_sum) / (max_sum - min_sum);
    int depth = MAX_ALGO_DEPTH - (int)(factor * (MAX_ALGO_DEPTH - MIN_ALGO_DEPTH));
    return depth;
}

void print_game(t_game *game) {
    for (int i = 0; i < (game->board.cols / 2 + 1); i++) {
        ft_printf(" ");
    }
    int column_width = game->board.cols;
    if (game->state == AI_TURN)
        printf_formatted("AI'S TURN", true, AI_COLOR, ALIGN_CENTER, column_width * 2);
    else if (game->state == PLAYER_TURN)
        printf_formatted("PLAYER'S TURN", true, PLAYER_COLOR, ALIGN_CENTER, column_width * 2);
    else if (game->state == PLAYER_WON)
        printf_formatted("PLAYER WON! 😃", true, PLAYER_COLOR, ALIGN_CENTER, column_width * 2);
    else if (game->state == AI_WON)
        printf_formatted("AI WON! 🤖", true, AI_COLOR, ALIGN_CENTER, column_width * 2);
    else if (game->state == DRAW)
        printf_formatted("DRAW!", true, NULL, ALIGN_CENTER, column_width * 2);
    ft_printf("\n\n");
    print_board(&game->board);
}

int init_game(t_game *game, int rows, int cols) {
    if (rows < MIN_BOARD_ROWS || rows > MAX_BOARD_ROWS || cols < MIN_BOARD_COLS ||
        cols > MAX_BOARD_COLS) {
        ft_dprintf(STDERR_FILENO,
                   "Error. Board size must be between %dx%d and %dx%d.\n",
                   MIN_BOARD_ROWS, MIN_BOARD_COLS, MAX_BOARD_ROWS, MAX_BOARD_COLS);
        return 1;
    }
    if (init_board(&game->board, rows, cols) != 0) {
        return 1;
    }
    game->depth = calculate_depth(game->board.rows, game->board.cols);
    game->state = (rand() % 2 == 0) ? PLAYER_TURN : AI_TURN;
    return 0;
}

int get_player_input() {
    char *col_str = NULL;
    int gnl_error = 0;
    ft_printf(BOLD "Enter column number: " );
    while ((col_str = get_next_line(STDIN_FILENO, &gnl_error)) == NULL) {  }
    ft_printf(RESET_FORMAT "\n");
    int chosen_col = ft_atoi(col_str) - 1;
    free(col_str);
    return (chosen_col);
}

void    update_game_state(t_game *game) {
    if (check_win(&game->board, PLAYER)) {
        game->state = PLAYER_WON;
    } else if (check_win(&game->board, AI)) {
        game->state = AI_WON;
    } else if (check_draw(&game->board)) {
        game->state = DRAW;
    } else if (game->state == PLAYER_TURN) {
        game->state = AI_TURN;
    } else {
        game->state = PLAYER_TURN;
    }
}

bool validate_move(t_game *game, int col) {
    if (col < 0 || col >= game->board.cols) {
        ft_printf("Invalid column number. Try again.\n");
        return false;
    }
    for (int row = 0; row < game->board.rows; row++) {
        if (game->board.fields[row][col].val == EMPTY) {
            return true;
        }
    }
    ft_printf("Column is full. Try again.\n");
    return false;
}

static void make_move(t_game *game, int col) {
    for (int row = 0; row < game->board.rows; row++) {
        if (game->board.fields[row][col].val == EMPTY) {
            game->board.fields[row][col].val = (game->state == PLAYER_TURN) ? PLAYER : AI;
            break;
        }
    }
}

void play_game(t_game *game) {
    int chosen_col = -1;
    bool valid_player_move = false;
    if (game->state == AI_TURN) {
        chosen_col = get_ai_move_minimax(game, game->depth);
    } else {
        while (!valid_player_move) {
            chosen_col = get_player_input();
            valid_player_move = validate_move(game, chosen_col);
        }
    }
    make_move(game, chosen_col);
    update_game_state(game);
}
