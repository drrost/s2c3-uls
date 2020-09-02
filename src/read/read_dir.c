#include <uls.h>

static void dir_sort_condition(t_dir *dir, t_flags *flags) {
    if (!flags->f_f) {
        mx_sort_files_by_ascii(dir->files, dir->lenght);
        if (flags->f_S)
            mx_sort_files_by_size(dir->files, dir->lenght);
        else if (flags->f_t)
            mx_sort_files_by_time(dir->files, dir->lenght, flags);
        if (flags->f_r)
            mx_reverse_files(dir->files, dir->lenght);
    }
}

t_file **dir_file_creation(DIR **dr, t_direntry **direntry,
                           char *path, t_out *out) {
    t_file **files = NULL;

    files = mx_read_files_array(dr, direntry, path, out);
    return files;
}

t_dir *mx_read_dir(t_flags *flags, char *path, t_out *out) {
    t_dir *dir = mx_create_dir();
    t_direntry *direntry = NULL;
    DIR *dr = NULL;

    dir->path = mx_strdup(path);
    dir->lenght = mx_count_in_dir(path, flags);
    (flags->f_S || flags->f_t) ? lstat(dir->path, &(dir->stat)) : 0;
    out->lenght = dir->lenght;
    out->flags = flags;
    dir->files = dir_file_creation(&dr, &direntry, path, out);
    if (!dir->files) {
        dir->permission = 0;
        return dir;
    }
    dir_sort_condition(dir, flags);
    mx_set_to_zero(out);
    return dir;
}
