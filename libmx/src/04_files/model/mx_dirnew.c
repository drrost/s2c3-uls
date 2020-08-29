//
// Created by Rostyslav Druzhchenko on 29.08.2020.
//

#include <libmx.h>
#include <stdlib.h>

t_dir *mx_dirnew() {
    return (t_dir *)malloc(sizeof(t_dir));
}
