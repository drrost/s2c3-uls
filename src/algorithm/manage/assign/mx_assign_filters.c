//
// Created by Rostyslav Druzhchenko on 11.09.2020.
//

#include <uls.h>

void mx_assign_filters(t_algorithm *algorithm, t_flags *flags) {
    algorithm->fetcher.filter.filters[0] = mx_filter_none;
    algorithm->fetcher.filter.filters[1] = mx_filter_dot_dotdot;
    algorithm->fetcher.filter.filters[2] = mx_filter_dots;

    if (flags->a)
        algorithm->fetcher.filter.filters[1] = 0;
    if (flags->A)
        algorithm->fetcher.filter.filters[2] = 0;
}
