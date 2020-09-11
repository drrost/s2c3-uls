//
// Created by Rostyslav Druzhchenko on 11.09.2020.
//

#include <uls.h>

void mx_assign_filters(t_algorithm *algorithm, t_flags *flags) {
    algorithm->fetcher.filter = mx_select_exclude_dot_dirs;

    if (flags->A)
        algorithm->fetcher.filter = mx_select_exclude_dot_dirs;
    if (flags->a)
        algorithm->fetcher.filter = mx_select_all;
}
