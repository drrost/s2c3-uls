//
// Created by Rostyslav Druzhchenko on 01.09.2020.
//

#include <libmx.h>
#include <stdlib.h>

t_dirent *mx_dirent_new(const char *name, int type) {
    t_dirent *inst = (t_dirent *)malloc(sizeof(t_dirent));
    inst->name = mx_strdup(name);
    inst->type = type;
    return inst;
}
