#include <uls.h>
#include <stdlib.h>

void mx_dealloc_driver(t_driver **driver) {
    mx_strdel(&((*driver)->driver));
    free(*driver);
    (*driver) = NULL;
}
