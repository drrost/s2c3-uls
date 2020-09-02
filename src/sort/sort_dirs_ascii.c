#include <uls.h>

void mx_sort_dirs_by_ascii(t_dir **dirs, unsigned int lenght) {
    for (unsigned int i = 0; i < lenght - 1; i++) {
        if (mx_unicode_strcmp(dirs[i]->path, dirs[i + 1]->path) > 0) {
            mx_swap_dirs(&dirs[i], &dirs[i + 1]);
            for (unsigned int j = i; j > 0; j--) {
                if (mx_unicode_strcmp(dirs[j]->path, dirs[j - 1]->path) < 0)
                    mx_swap_dirs(&dirs[j], &dirs[j - 1]);
                else
                    break;
            }
        }
    }
}
