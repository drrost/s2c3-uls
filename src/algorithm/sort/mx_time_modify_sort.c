//
// Created by Rostyslav Druzhchenko on 11.09.2020.
//

#include <libmx.h>

int mx_time_modify_sort(t_dirent *d1, t_dirent *d2) {
    return d1->mod_time < d2->mod_time;
}
