#include <uls.h>

void mx_sort_dirs_by_size(t_dir **dirs, unsigned int lenght) {
    for (unsigned int i = 0; i < lenght - 1; i++) {
        if (dirs[i]->stat.st_size < dirs[i + 1]->stat.st_size) {
            mx_swap_dirs(&dirs[i], &dirs[i + 1]);
            for (unsigned int j = i; j > 0; j--) {
                if (dirs[j]->stat.st_size > dirs[j - 1]->stat.st_size)
                    mx_swap_dirs(&dirs[j], &dirs[j - 1]);
                else
                    break;
            }
        }
    }
}
