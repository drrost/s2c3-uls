#include <uls.h>

static void sort_dirs_by_c(t_dir **dirs, unsigned int lenght) {
    for (unsigned int i = 0; i < lenght - 1; i++) {
        if (dirs[i]->stat.st_ctime < dirs[i + 1]->stat.st_ctime) {
            mx_swap_dirs(&dirs[i], &dirs[i + 1]);
            for (unsigned int j = i; j > 0; j--) {
                if (dirs[j]->stat.st_ctime > dirs[j - 1]->stat.st_ctime)
                    mx_swap_dirs(&dirs[j], &dirs[j - 1]);
                else
                    break;
            }
        }
    }
}

static void sort_dirs_by_U(t_dir **dirs, unsigned int lenght) {
    for (unsigned int i = 0; i < lenght - 1; i++) {
        if (dirs[i]->stat.st_birthtime < dirs[i + 1]->stat.st_birthtime) {
            mx_swap_dirs(&dirs[i], &dirs[i + 1]);
            for (unsigned int j = i; j > 0; j--) {
                if (dirs[j]->stat.st_birthtime
                    > dirs[j - 1]->stat.st_birthtime)
                    mx_swap_dirs(&dirs[j], &dirs[j - 1]);
                else
                    break;
            }
        }
    }
}

static void sort_dirs_by_u(t_dir **dirs, unsigned int lenght) {
    for (unsigned int i = 0; i < lenght - 1; i++) {
        if (dirs[i]->stat.st_atime < dirs[i + 1]->stat.st_atime) {
            mx_swap_dirs(&dirs[i], &dirs[i + 1]);
            for (unsigned int j = i; j > 0; j--) {
                if (dirs[j]->stat.st_atime > dirs[j - 1]->stat.st_atime)
                    mx_swap_dirs(&dirs[j], &dirs[j - 1]);
                else
                    break;
            }
        }
    }
}

void mx_sort_dirs_by_time(t_dir **dirs, unsigned int lenght, t_flags *flags) {
    if (flags->f_c)
        sort_dirs_by_c(dirs, lenght);
    else if (flags->f_U)
        sort_dirs_by_U(dirs, lenght);
    else if (flags->f_u)
        sort_dirs_by_u(dirs, lenght);
    else
        for (unsigned int i = 0; i < lenght - 1; i++) {
            if (dirs[i]->stat.st_mtime < dirs[i + 1]->stat.st_mtime) {
                mx_swap_dirs(&dirs[i], &dirs[i + 1]);
                for (unsigned int j = i; j > 0; j--) {
                    if (dirs[j]->stat.st_mtime > dirs[j - 1]->stat.st_mtime)
                        mx_swap_dirs(&dirs[j], &dirs[j - 1]);
                    else
                        break;
                }
            }
        }
}
