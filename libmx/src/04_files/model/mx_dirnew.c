//
// Created by Rostyslav Druzhchenko on 29.08.2020.
//

#include <libmx.h>
#include <stdlib.h>

t_dir *mx_dirnew() {
    int size = sizeof(t_dir);
    t_dir *inst = (t_dir *)malloc(size);
    mx_memset(inst, 0, size);
    return inst;
}
