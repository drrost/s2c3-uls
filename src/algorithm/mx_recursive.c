//
// Created by Rostyslav Druzhchenko on 27.08.2020.
//

#include <uls.h>

void mx_recursive(const char *dir_name) {
    struct dirent **arr = 0;

    mx_scandir(dir_name, &arr, mx_select_exclude_dot_dirs, mx_alphasort);
    char *delim = isatty(STDOUT_FILENO) ? "\t\t" : "\n";
    print_dirent_arr(arr, delim);

    delete_dirent_arr(&arr);
}
