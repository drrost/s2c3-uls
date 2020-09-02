#include <uls.h>

static void swap_dirs(t_dir **dir1, t_dir **dir2) {
    t_dir *buf;

    buf = *dir1;
    *dir1 = *dir2;
    *dir2 = buf;
}

void mx_reverse_dirs(t_dir **dirs, unsigned int lenght) {
    unsigned int i = 0;
    unsigned int j = lenght - 1;

    if (dirs == NULL)
        return;
    while (i < j) {
        swap_dirs(&dirs[i], &dirs[j]);
        i++;
        j--;
    }
}
