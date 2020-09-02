#include <uls.h>

void mx_dealloc_file(t_file **file) {
    mx_strdel(&((*file)->name));
    mx_strdel(&((*file)->username));
    mx_strdel(&((*file)->acl));
    if ((*file)->gr != NULL)
        mx_strdel(&((*file)->gr));
    if ((*file)->link != NULL)
        mx_strdel(&((*file)->link));
    if ((*file)->driver != NULL)
        mx_dealloc_driver(&((*file)->driver));
    mx_dealloc_time(&((*file)->time));
    free(*file);
    (*file) = NULL;
}
