//
// Created by Rostyslav Druzhchenko on 25.08.2020.
//

#include <uls.h>
#include <stdlib.h>

void print_dirent_arr(struct dirent **arr, char *delim) {
    for (int i = 0; arr[i]; i++) {
        mx_printstr(arr[i]->d_name);
        mx_printstr(delim);
    }
}

static void delete_dirent_arr(struct dirent ***arr) {
    free(*arr);
    *arr = 0;
}

void mx_basic(const char *dir_name) {
    struct dirent **arr = 0;

    mx_scandir(dir_name, &arr, mx_select_exclude_dot_dirs, mx_alphasort);
    print_dirent_arr(arr, "\n");

    delete_dirent_arr(&arr);
}
