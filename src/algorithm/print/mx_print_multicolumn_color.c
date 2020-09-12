//
// Created by Karina Barinova on 09.09.2020.
//

#include <uls.h>

void mx_print_multicolumn_color(t_list *entities, const char *delim) {
    int longest = mx_get_maxlen(entities);
    int files_count = mx_list_size(entities);
    int lines = mx_lines_count(files_count, longest);
    struct stat buf;

    for (int i = 0; i < lines; i++)
        for (int j = 0; j < files_count; j++)
            if (j == i || (j - i) % lines == 0) {
                lstat(mx_find_index(entities, j), &buf);;
                mx_color_set(mx_acl_strcol(mx_get_permissions(buf.st_mode)),
                             mx_acl_bkcol(mx_get_permissions(buf.st_mode)));
                mx_printstr(mx_find_index(entities, j));
                mx_color_reset();
                if (j == 0) {
                    mx_printstr(" ");
                }
                else if (j + lines >= files_count)
                    mx_printstr("\n");
                else
                    mx_count_spaces(entities, longest, j, delim);
            }
}
