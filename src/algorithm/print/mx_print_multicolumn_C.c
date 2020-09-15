//
// Created by Karina Barinova on 10.09.2020.
//

#include <uls.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int get_window_size_C(void) {
    int output = !isatty(1);
    if (output == 0) {
        int fd = open("/dev/tty", O_RDWR);
        struct winsize w;
        ioctl(fd, TIOCGWINSZ, &w);
        close(fd);
        return w.ws_col;
    }
    return 80;
}

int mx_lines_count_C(int files_count, int longest) {
    int win_col = get_window_size_C();
    int count = 1;
    int space = mx_get_max_spaces(longest);
    int c_words;
    int add;

    if (files_count * (longest + space) >= win_col) {
        c_words = win_col / (longest + space);
        if (c_words == 0)
            c_words++;
        add = 0;
        if ((files_count % c_words) != 0)
            add++;
        count = (files_count / c_words) + add;
    }
    if (!files_count)
        count = 0;
    return count;
}

void mx_print_multicolumn_C(t_list *entities, const char *delim) {
    int longest = mx_get_maxlen(entities);
    int files_count = mx_list_size(entities);
    int lines = mx_lines_count_C(files_count, longest);

    for (int i = 0; i < lines; i++)
        for (int j = 0; j < files_count; j++)
            if (j == i || (j - i) % lines == 0) {
                mx_printstr(mx_find_index(entities, j));
                if (j + lines >= files_count)
                    mx_printstr("\n");
                else
                    mx_count_spaces(entities, longest, j, delim);
            }
}
