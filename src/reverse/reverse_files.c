#include <uls.h>

static void swap_files(t_file **file1, t_file **file2) {
    t_file *buf;

    buf = *file1;
    *file1 = *file2;
    *file2 = buf;
}

void mx_reverse_files(t_file **files, unsigned int lenght) {
    unsigned int i = 0;
    unsigned int j = lenght - 1;

    if (files == NULL)
        return;
    while (i < j) {
        swap_files(&files[i], &files[j]);
        i++;
        j--;
    }
}
