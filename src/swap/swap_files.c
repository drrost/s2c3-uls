#include <uls.h>

void mx_swap_files(t_file **file1, t_file **file2) {
    t_file *buf = NULL;

    buf = *file1;
    *file1 = *file2;
    *file2 = buf;
}
