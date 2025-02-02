#include "../connect4.h"

void printf_formatted(const char *text, bool bold, const char *color, t_text_align alignment, int col_width) {
    int text_length = ft_strlen(text);
    int padding_left = 0;
    int padding_right = 0;

    if (alignment == ALIGN_CENTER) {
        padding_left = (col_width - text_length) / 2;
        padding_right = col_width - text_length - padding_left;
    } else if (alignment == ALIGN_RIGHT) {
        padding_left = col_width - text_length;
    }

    if (padding_left < 0) padding_left = 0;
    if (padding_right < 0) padding_right = 0;

    for (int i = 0; i < padding_left; i++) {
        ft_printf(" ");
    }
    if (bold) {
        ft_printf(BOLD);
    }
    if (color) {
        ft_printf("%s", color);
    }
    ft_printf("%s", text);
    ft_printf(RESET_FORMAT);
}