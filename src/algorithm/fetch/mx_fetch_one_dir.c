//
// Created by Rostyslav Druzhchenko on 07.09.2020.
//

#include <uls.h>

t_list *mx_fetch_one_dir(const char *dir_name) {
    t_list *dirs = 0;
    mx_scandir(dir_name, &dirs, mx_select_exclude_dot_dirs, mx_alphasort);
    return dirs;
}
