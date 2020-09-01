//
// Created by Rostyslav Druzhchenko on 01.09.2020.
//

#include <libmx.h>
#include <stdlib.h>

void mx_dirent_del(t_dirent **dir_ent) {
    mx_strdel(&(*dir_ent)->name);
    free(*dir_ent);
    *dir_ent = 0;
}
