//
// Created by Rostyslav Druzhchenko on 07.09.2020.
//

#include <uls.h>

t_list *mx_fetch_one_dir(const char *dir_name, t_fetch_params params) {
    t_list *dirs = 0;
    mx_scandir(dir_name, &dirs, params.filter, params.sort_cmp);
    return dirs;
}
