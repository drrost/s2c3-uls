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
    else if (MX_ISXEC(buf.st_mode))
        name = mx_strjoin(name, "*");
    else if (MX_ISLNK(buf.st_mode))
        name = mx_strjoin(name, "@");
    return name;
}

static void mx_print_dir_multicolumn_F(t_list *entities, const char *delim, bool print_hidden) {
    int longest = mx_get_maxlen(entities, print_hidden);
    int files_count = mx_get_num_files(entities, print_hidden);
    int lines = mx_lines_count(files_count, longest);
    struct stat buf;

    for (int i = 0; i < lines; i++)
        for (int j = 0; j < files_count; j++)
            if (j == i || (j - i) % lines == 0) {
                lstat(mx_find_index(entities, j, print_hidden), &buf);
                mx_printstr(mx_get_info_F(mx_find_index(entities, j, print_hidden), buf));
                if (j + lines >= files_count)
                    mx_printstr("\n");
                else
		    mx_count_spaces(entities, longest, j, delim, print_hidden);
            }
}

void mx_print_multicolumn_F(t_list *dirs, const char *delim) {
    //hidden files and dirs are not printed

    t_dir *dir = (t_dir *)dirs->data;
    mx_print_dir_multicolumn_F(dir->entities, delim, false);
}

void mx_print_multicolumn_F_all(t_list *dirs, const char *delim) {
    //hidden files and dirs are not printed

    t_dir *dir = (t_dir *)dirs->data;
    mx_print_dir_multicolumn_F(dir->entities, delim, true);
}
