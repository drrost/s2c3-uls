//
// Created by Rostyslav Druzhchenko on 07.09.2020.
//

#include <uls.h>

t_list *mx_fetch_one_dir(FETCH_PARAMS) {
    t_list *dirs = 0;
    mx_scandir(dir_name, &dirs, filter, sort_cmp);
    return dirs;
}
