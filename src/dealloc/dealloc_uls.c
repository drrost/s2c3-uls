#include <uls.h>

void mx_dealloc_uls(t_uls **uls) {
    free((*uls)->flags);
    mx_dealloc_files(&((*uls)->files));
    mx_dealloc_dirs(&((*uls)->dirs));
    free(*uls);
    (*uls) = NULL;
}
