//
// Created by Karina Barinova on 10.09.2020.
//

#include <uls.h>

static void do_print(t_list *entities, const char *delim) {
    int longest = mx_get_maxlen(entities);
    int files_count = mx_list_size(entities);
    int lines = mx_lines_count(files_count, longest);

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

void mx_print_multicolumn(t_list *dirs, const char *delim) {
    mx_print_dirs(dirs, delim, do_print);
}
