#include <uls.h>

static void read_cycle(t_file **files, t_direntry **direntry, char *path,
                       t_out *out) {
    if (out->flags->def_file_dots && out->flags->def_dots) {
        files[out->i] = mx_read_file(path, (*direntry)->d_name, out->flags);
        out->i++;
    }
    else if (out->flags->def_file_dots
            && mx_A_file_condition((*direntry)->d_name)) {
        files[out->i] = mx_read_file(path, (*direntry)->d_name, out->flags);
        out->i++;
    }
    else if ((*direntry)->d_name[0] != '.') {
        files[out->i] = mx_read_file(path, (*direntry)->d_name, out->flags);
        out->i++;
    }
}

t_file **mx_read_files_array(DIR **dr, t_direntry **direntry, char *path,
                             t_out *out) {
    t_file **files = mx_create_files_array(out->lenght);
    out->i = 0;

    if (!files)
        return NULL;
    (*dr) = opendir((const char *)path);
    if (!(*dr)) {
        mx_dealloc_files(&files);
        return NULL;
    }
    while (((*direntry) = readdir((*dr))) != NULL) {
        read_cycle(files, direntry, path, out);
    }
    out->i = 0;
    closedir((*dr));
    return files;
}
