#include <uls.h>

void mx_dealloc_files(t_file ***files) {
    unsigned int i = 0;

    if (!(*files))
        return ;
    while ((*files)[i]) {
        mx_dealloc_file(&((*files)[i]));
        i++;
    }
    free(*files);
    (*files) = NULL;
}
