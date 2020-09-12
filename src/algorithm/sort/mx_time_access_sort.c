//
// Created by Rostyslav Druzhchenko on 12.09.2020.
//

#include <libmx.h>

int mx_time_access_sort(t_dirent *d1, t_dirent *d2) {
    return d1->acc_time < d2->acc_time;
}
