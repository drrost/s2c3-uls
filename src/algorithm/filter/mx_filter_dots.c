//
// Created by Rostyslav Druzhchenko on 11.09.2020.
//

#include <libmx.h>

int mx_filter_dots(const struct dirent *dirent) {
    return dirent->d_name[0] != '.';
}
