//
// Created by Karina Barinova on 10.09.2020.
//

#include <uls.h>

static void mx_print_dir_multicolumn(t_list *entities, const char *delim, bool print_hidden) {
    int longest = mx_get_maxlen(entities, print_hidden);
    int files_count = mx_get_num_files(entities, print_hidden);
    int lines = mx_lines_count(files_count, longest);

    for (int i = 0; i < lines; i++)
        for (int j = 0; j < files_count; j++)
            if (j == i || (j - i) % lines == 0) {
                mx_printstr(mx_find_index(entities, j, print_hidden));
                if (j + lines >= files_count)
                    mx_printstr("\n");
                else
		    mx_count_spaces(entities, longest, j, delim, print_hidden);
            }
}

void mx_print_multicolumn(t_list *dirs, const char *delim) {
    //hidden files and dirs are not printed

    t_dir *dir = (t_dir *)dirs->data;
    mx_print_dir_multicolumn(dir->entities, delim, false);
}
void mx_print_multicolumn_all(t_list *dirs, const char *delim) {

    t_dir *dir = (t_dir *)dirs->data;
    mx_print_dir_multicolumn(dir->entities, delim, true);
}
