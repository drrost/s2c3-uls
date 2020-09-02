#include <uls.h>

void mx_dealloc_dirs(t_dir ***dirs) {
    unsigned int i = 0;

    if (!(*dirs))
        return ;
    while ((*dirs)[i]) {
        mx_dealloc_dir(&((*dirs)[i]));
        i++;
    }
    free(*dirs);
    (*dirs) = NULL;
}
