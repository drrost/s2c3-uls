#include <uls.h>

static void isatty_condition(t_screen *screen, int longest_name, int *columns,
                             t_flags *flags) {
    if (flags->f_m)
        (*screen).ws_col = 79;
    if (flags->f_C == 0)
        flags->f_1 = 1;
    else {
        (*screen).ws_col = 79;
        if (longest_name > 31 && longest_name < 40)
            (*columns) = 2;
        else {
            (*columns) = (*screen).ws_col
            / (longest_name + (8 - longest_name % 8));
        }
    }
}

int mx_rows_amount(int file_amount, int longest_name, int *columns,
                   t_out **out) {
    int rows = 0;
    t_screen screen;

    if (isatty(1) != 0) {
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &screen);
        (*columns) = screen.ws_col / longest_name;
    }
    else if (isatty(1) == 0)
        isatty_condition(&screen, longest_name, columns, (*out)->flags);
    if (screen.ws_col < longest_name || (*out)->flags->f_1 == 1) {
        rows = file_amount;
    }
    else if (file_amount % (*columns) == 0)
        rows = file_amount / (*columns);
    else
        rows = file_amount / (*columns) + 1;
    (*out)->screen_size = screen.ws_col;
    return rows;
}
