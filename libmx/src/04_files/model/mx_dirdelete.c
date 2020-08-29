//
// Created by Rostyslav Druzhchenko on 29.08.2020.
//

#include <stdlib.h>
#include <libmx.h>

void mx_dirdelete(t_dir *dir) {
    free(dir->name);
    while (dir->entities) {
        struct dirent *entity = (struct dirent *)dir->entities->data;
        free(entity);
        mx_pop_front(&(dir->entities));
    }
    free(dir);
}
