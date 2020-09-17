//
// Created by Rostyslav Druzhchenko on 17.09.2020.
//

#include <libmx.h>

int mx_time_ctime_sort(t_dirent *d1, t_dirent *d2) {
    if (d1->file_stat.st_ctimespec.tv_sec ==
        d2->file_stat.st_ctimespec.tv_nsec) {
        return mx_strcmp(d1->name, d2->name);
    }

    return d1->file_stat.st_ctimespec.tv_sec <=
           d2->file_stat.st_ctimespec.tv_sec;
}
