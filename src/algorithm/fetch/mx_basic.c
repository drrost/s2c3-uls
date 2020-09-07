//
// Created by Rostyslav Druzhchenko on 25.08.2020.
//

#include <uls.h>
#include <unistd.h>

void mx_basic(const char *dir_name) {
    t_list *dirs = 0;

    mx_scandir(dir_name, &dirs, mx_select_exclude_dot_dirs, mx_alphasort);
    char *delim = isatty(STDOUT_FILENO) ? "\t\t" : "\n";
    t_dir *dir = (t_dir *)dirs->data;
    mx_print_dir_content(dir->entities, delim);
    mx_printline("");

    while (dirs) {
        t_dir *dir = (t_dir *)dirs->data;
        mx_dirdelete(&dir);
        dirs = dirs->next;
    }
//    mx_delete_dirent_arr(&arr);
}
