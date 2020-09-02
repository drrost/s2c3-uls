#include <uls.h>

void mx_dealloc_time(t_time **time) {
    mx_strdel(&((*time)->mmdd));
    mx_strdel(&((*time)->time));
    mx_strdel(&((*time)->year));
    free(*time);
    (*time) = NULL;
}
