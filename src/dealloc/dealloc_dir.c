#include <uls.h>

void mx_dealloc_dir(t_dir **dir) {
    mx_strdel(&((*dir)->path));
    if ((*dir)->files)
        mx_dealloc_files(&((*dir)->files));
    free(*dir);
    (*dir) = NULL;
}
