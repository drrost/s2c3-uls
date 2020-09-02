#include <uls.h>

int mx_check_is_folder(char *path) {
    t_stat stat;

    if (lstat(path, &stat) == -1)
        return -1;
    if (MX_ISDIR(stat.st_mode))
        return 1;
    else
        return 0;
}
