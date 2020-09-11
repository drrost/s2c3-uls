//
// Created by Rostyslav Druzhchenko on 11.09.2020.
//

#include <uls.h>

void mx_assign_fetchers(t_algorithm *algorithm, t_flags *flags) {
    if (flags->R)
        algorithm->fetcher.fetch = mx_fetch_recursive;
    else
        algorithm->fetcher.fetch = mx_fetch_one_dir;
}
