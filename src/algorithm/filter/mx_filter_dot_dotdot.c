//
// Created by Rostyslav Druzhchenko on 25.08.2020.
//

#include <libmx.h>

int mx_filter_dot_dotdot(const struct dirent *dirent) {
    if (mx_strcmp(dirent->d_name, ".") == 0 ||
        mx_strcmp(dirent->d_name, "..") == 0)
        return 0;
    return 1;
}
