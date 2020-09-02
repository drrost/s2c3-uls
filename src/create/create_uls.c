#include <uls.h>
#include <stdlib.h>

t_uls *mx_create_uls() {
    t_uls *uls = (t_uls *)malloc(sizeof(t_uls));

    uls->flags = mx_create_flags();
    uls->files_count = 0;
    uls->files = NULL;
    uls->dirs_count = 0;
    uls->dirs = NULL;
    return uls;
}
