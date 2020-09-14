//
// Created by Rostyslav Druzhchenko on 11.09.2020.
//

#include <libmx.h>

int mx_time_modify_sort(t_dirent *d1, t_dirent *d2) {
    return d1->file_stat.st_mtimespec.tv_nsec <
           d2->file_stat.st_mtimespec.tv_nsec;
}
