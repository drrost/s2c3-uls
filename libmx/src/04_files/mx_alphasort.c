//
// Created by Rostyslav Druzhchenko on 25.08.2020.
//

#include <libmx.h>

int mx_alphasort(t_dirent *d1, t_dirent *d2) {
    return mx_strcmp(d1->name, d2->name);
}
