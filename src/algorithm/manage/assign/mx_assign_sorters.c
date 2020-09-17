//
// Created by Rostyslav Druzhchenko on 11.09.2020.
//

#include <uls.h>

void mx_assign_sorters(t_algorithm *algorithm, t_flags *flags) {
    algorithm->fetcher.comparator.cmp = mx_alphasort;

    if (flags->r)
        algorithm->fetcher.comparator.reverse = true;
    if (flags->t)
        algorithm->fetcher.comparator.cmp = mx_time_modify_sort;
    if (flags->u)
        algorithm->fetcher.comparator.cmp = mx_time_access_sort;
    if (flags->f)
        algorithm->fetcher.comparator.cmp = mx_no_sort;
}
