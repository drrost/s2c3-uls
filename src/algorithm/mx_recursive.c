//
// Created by Rostyslav Druzhchenko on 27.08.2020.
//

#include <uls.h>
#include <unistd.h>

static void do_scan(const char *dir_name, t_list **dirs) {

    mx_scandir(dir_name, dirs, mx_select_exclude_dot_dirs, mx_alphasort);

    mx_printstr("");
}

void mx_recursive(const char *dir_name) {
    t_list *dirs = 0;

    do_scan(dir_name, &dirs);

    char *delim = isatty(STDOUT_FILENO) ? "\t\t" : "\n";
    mx_print_dirent_simple(dirs, delim);

}
