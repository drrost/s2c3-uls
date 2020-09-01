#include <uls.h>

void mx_sort_files_by_ascii(t_file **files, unsigned int lenght) {
    for (unsigned int i = 0; i < lenght - 1; i++) {
        if (mx_strcmp_unicode(files[i]->name, files[i + 1]->name) > 0) {
            mx_swap_files(&files[i], &files[i + 1]);
            for (unsigned int j = i; j > 0; j--) {
                if (mx_strcmp_unicode(files[j]->name, files[j - 1]->name) < 0)
                    mx_swap_files(&files[j], &files[j - 1]);
                else
                    break;
            }
        }
    }
}
