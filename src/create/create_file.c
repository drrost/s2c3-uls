#include <uls.h>

 t_file *mx_create_file() {
    t_file *file = (t_file *)malloc(sizeof(t_file));

    file->name = NULL;
    file->username = NULL;
    file->acl = NULL;
    file->link = NULL;
    file->gid = 0;
    file->blocks = 0;
    file->gr = NULL;
    file->driver = NULL;
    file->time = NULL;
    return file;
}
