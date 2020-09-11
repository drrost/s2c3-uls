//
// Created by Karina Barinova on 09.09.2020.
//


#include <uls.h>

static void mx_print_dir_multicolumn_color(t_list *entities, const char *delim, bool print_hidden) {
    int longest = mx_get_maxlen(entities, print_hidden);
    int files_count = mx_get_num_files(entities, print_hidden);
    int lines = mx_lines_count(files_count, longest);
    struct stat buf;

    for (int i = 0; i < lines; i++)
        for (int j = 0; j < files_count; j++)
            if (j == i || (j - i) % lines == 0) {
                lstat(mx_find_index(entities, j, print_hidden), &buf);;
                mx_color_set(mx_acl_strcol(mx_get_permissions(buf.st_mode)), mx_acl_bkcol(mx_get_permissions(buf.st_mode)));
                mx_printstr(mx_find_index(entities, j, print_hidden));
                mx_color_reset();
                if (j == 0) {
                    mx_printstr(" ");
                }
                else if (j + lines >= files_count)
                    mx_printstr("\n");
                else
            mx_count_spaces(entities, longest, j, delim, print_hidden);
            }
}

void mx_print_multicolumn_color(t_list *dirs, const char *delim) {
    //hidden files and dirs are not printed

    t_dir *dir = (t_dir *)dirs->data;
    mx_print_dir_multicolumn_color(dir->entities, delim, false);
}

void mx_print_multicolumn_color_all(t_list *dirs, const char *delim) {

    t_dir *dir = (t_dir *)dirs->data;
    mx_print_dir_multicolumn_color(dir->entities, delim, true);
}
