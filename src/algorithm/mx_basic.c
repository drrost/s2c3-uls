//
// Created by Rostyslav Druzhchenko on 25.08.2020.
//

#include <uls.h>
#include <stdlib.h>
#include <unistd.h>

void print_dirent_arr(struct dirent **arr, char *delim) {
    //works as ls -1 for now
    for (int i = 0; arr[i]; i++) {
        if (arr[i]->d_name[0] == '.')
            continue;
        else {
            mx_printstr(arr[i]->d_name);
        }
        if (arr[i + 1] != 0)
            mx_printstr(delim);
    }
    mx_printstr("\n");
}

static void delete_dirent_arr(struct dirent ***arr) {
    free(*arr);
    *arr = 0;
}

void mx_basic(const char *dir_name) {
    struct dirent **arr = 0;

    mx_scandir(dir_name, &arr, mx_select_exclude_dot_dirs, mx_alphasort);
    char *delim = isatty(STDOUT_FILENO) ? "\t\t" : "\n";
    print_dirent_arr(arr, delim);

    delete_dirent_arr(&arr);
}
