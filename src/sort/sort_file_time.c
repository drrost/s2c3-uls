#include <uls.h>

static void sort_files_by_c(t_file **files, unsigned int lenght) {
    for (unsigned int i = 0; i < lenght - 1; i++) {
        if (files[i]->stat.st_ctime < files[i + 1]->stat.st_ctime) {
            mx_swap_files(&files[i], &files[i + 1]);
            for (unsigned int j = i; j > 0; j--) {
                if (files[j]->stat.st_ctime > files[j - 1]->stat.st_ctime)
                    mx_swap_files(&files[j], &files[j - 1]);
                else
                    break;
            }
        }
    }
}

static void sort_files_by_U(t_file **files, unsigned int lenght) {
    for (unsigned int i = 0; i < lenght - 1; i++) {
        if (files[i]->stat.st_birthtime < files[i + 1]->stat.st_birthtime) {
            mx_swap_files(&files[i], &files[i + 1]);
            for (unsigned int j = i; j > 0; j--) {
                if (files[j]->stat.st_birthtime
                    > files[j - 1]->stat.st_birthtime)
                    mx_swap_files(&files[j], &files[j - 1]);
                else
                    break;
            }
        }
    }
}

static void sort_files_by_u(t_file **files, unsigned int lenght) {
    for (unsigned int i = 0; i < lenght - 1; i++) {
        if (files[i]->stat.st_atime < files[i + 1]->stat.st_atime) {
            mx_swap_files(&files[i], &files[i + 1]);
            for (unsigned int j = i; j > 0; j--) {
                if (files[j]->stat.st_atime > files[j - 1]->stat.st_atime)
                    mx_swap_files(&files[j], &files[j - 1]);
                else
                    break;
            }
        }
    }
}

void mx_sort_files_by_time(t_file **files, unsigned int lenght,
                           t_flags *flags) {

    if (flags->f_c)
        sort_files_by_c(files, lenght);
    else if (flags->f_U)
        sort_files_by_U(files, lenght);
    else if (flags->f_u)
        sort_files_by_u(files, lenght);
    else {
        for (unsigned int i = 0; i < lenght - 1; i++) {
            if (files[i]->stat.st_mtime < files[i + 1]->stat.st_mtime) {
                mx_swap_files(&files[i], &files[i + 1]);
                for (unsigned int j = i; j > 0; j--) {
                    if (files[j]->stat.st_mtime > files[j - 1]->stat.st_mtime)
                        mx_swap_files(&files[j], &files[j - 1]);
                    else
                        break;
                }
            }
        }
    }
}
