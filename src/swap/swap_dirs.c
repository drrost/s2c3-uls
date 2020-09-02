#include <uls.h>

void mx_swap_dirs(t_dir **dir1, t_dir **dir2) {
    t_dir *buf = NULL;

    buf = *dir1;
    *dir1 = *dir2;
    *dir2 = buf;
}
