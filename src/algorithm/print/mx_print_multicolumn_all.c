//
// Created by Karina Barinova on 09.09.2020.
//

#include <uls.h>



void mx_print_dir_multicolumn_all(t_list *entities, const char *delim) {
    int longest = mx_get_maxlen_all(entities);
    int files_count = mx_get_num_files_all(entities);
    int lines = mx_lines_count(files_count, longest);

    for (int i = 0; i < lines; i++)
        for (int j = 0; j < files_count; j++)
            if (j == i || (j - i) % lines == 0) {
                mx_printstr(mx_find_index_all(entities, j));
                if (j + lines >= files_count)
                    mx_printstr("\n");
                else
		    mx_count_spaces_all(entities, longest, j, delim);
            }
}

void mx_print_multicolumn_all(t_list *dirs, const char *delim) {

    t_dir *dir = (t_dir *)dirs->data;
    mx_print_dir_multicolumn_all(dir->entities, delim);
}
