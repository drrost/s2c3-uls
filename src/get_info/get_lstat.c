#include <uls.h>

void mx_get_lstat(t_file *file, char *file_path) {
    lstat(file_path, &(file->stat));
}
