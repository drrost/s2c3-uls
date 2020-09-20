//
// Created by Karina Barinova on 15.09.2020.
//

#include <uls.h>

static char mx_get_perms_p(mode_t mode) {

    char c = 0;
    if (MX_ISREG(mode))
        c = '-';
    else if (MX_ISDIR(mode))
        c = 'd';
    else if (MX_ISFIFO(mode))
        c = '|';
    else if (MX_ISSOCK(mode))
        c = 's';
    else if (MX_ISCHR(mode))
        c = 'c';
    else if (MX_ISBLK(mode))
        c = 'b';
    else if (MX_ISLNK(mode))
        c = 'l';

    return c;

}

static void check_flag_p(mode_t mode) {
    char c;
    c = mx_get_perms_p(mode);
    if (c == 'd')
        mx_printstr("/");
}

void mx_print_multicolumn_p(t_list *entities, const char *delim) {
    int longest = mx_get_maxlen(entities);
    int files_count = mx_list_size(entities);
    int lines = mx_lines_count(files_count, longest);
    struct stat buf;

    for (int i = 0; i < lines; i++)
        for (int j = 0; j < files_count; j++)
            if (j == i || (j - i) % lines == 0) {
                char *s = mx_find_index(entities, j);
                mx_printstr(s);
                mx_strdel(&s);
                // TODO: remove this 'lstat' usage
                lstat(mx_find_index(entities, j), &buf);
                check_flag_p(buf.st_mode);
                if (j + lines >= files_count)
                    mx_printstr("\n");
                else
                    mx_count_spaces(entities, longest, j, delim);
            }
}
