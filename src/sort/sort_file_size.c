#include <uls.h>

void mx_sort_files_by_size(t_file **files, unsigned int lenght) {
    for (unsigned int i = 0; i < lenght - 1; i++) {
        if (files[i]->stat.st_size < files[i + 1]->stat.st_size) {
            mx_swap_files(&files[i], &files[i + 1]);
            for (unsigned int j = i; j > 0; j--) {
                if (files[j]->stat.st_size > files[j - 1]->stat.st_size)
                    mx_swap_files(&files[j], &files[j - 1]);
                else
                    break;
            }
        }
    }
}
