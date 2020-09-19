//
// Created by Karina Barinova on 10.09.2020.
//

#include <uls.h>

static char *mx_get_info_F(char *name, struct stat buf) {
    if (MX_ISDIR(buf.st_mode))
        name = mx_strjoin(name, "/");
    else if (MX_ISSOCK(buf.st_mode))
        name = mx_strjoin(name, "=");
    else if (MX_ISFIFO(buf.st_mode))
        name = mx_strjoin(name, "|");
    else if (MX_ISLNK(buf.st_mode))
        name = mx_strjoin(name, "@");
    else if (MX_ISXEC(buf.st_mode))
        name = mx_strjoin(name, "*");
    return name;
}

void mx_print_multicolumn_F(t_list *entities, const char *delim) {
    int longest = mx_get_maxlen(entities);
    int files_count = mx_list_size(entities);
    int lines = mx_lines_count(files_count, longest);
    struct stat buf;
    t_dirent *custom_dirent = (t_dirent *)entities->data;

    for (int i = 0; i < lines; i++)
        for (int j = 0; j < files_count; j++)
            if (j == i || (j - i) % lines == 0) {
                // TODO: remove this 'lstat' usage
                char *my_path = get_path(custom_dirent->path, mx_find_index(entities, j));
                lstat(my_path, &buf);
                char *info = mx_get_info_F(mx_find_index(entities, j), buf);
                mx_printstr(info);
                if (j + lines >= files_count)
                    mx_printstr("\n");
                else
                    mx_count_spaces(entities, longest, j, delim);
                mx_strdel(&info);
                mx_strdel(&my_path);
            }
}
