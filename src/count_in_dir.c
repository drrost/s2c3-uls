#include <uls.h>

unsigned int mx_count_in_dir(char *path, t_flags *flags) {
    t_direntry *direntry = NULL;
    DIR *dr = NULL;
    unsigned int lenght = 0;

    errno = 0;
    dr = opendir(path);
    if (!dr)
        return 0;
    while ((direntry = readdir(dr)) != NULL) {
        if (flags->def_file_dots && flags->def_dots)
            lenght++;
        else if (flags->def_file_dots && mx_A_file_condition(direntry->d_name))
            lenght++;
        else if (direntry->d_name[0] != '.')
            lenght++;
    }
    closedir(dr);
    return lenght;
}
