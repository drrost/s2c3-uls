//
// Created by Rostyslav Druzhchenko on 09.09.2020.
//

#include <libmx.h>

int mx_filter_none(const struct dirent *dirent) {
    dirent++;
    return 1;
}
