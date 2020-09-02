#include <uls.h>

void mx_get_group(t_file *file) {
    t_group *group = getgrgid(file->stat.st_gid);

    if (!group)
        file->gr = NULL;
    else
        file->gr = mx_strdup(group->gr_name);
}
