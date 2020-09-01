#include <uls.h>

t_dir *mx_create_dir() {
    t_dir *dir = (t_dir *)malloc(sizeof(t_dir));

    dir->path = NULL;
    dir->lenght = 0;
    dir->permission = 1;
    dir->files = NULL;
    return dir;
}
