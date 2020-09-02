#include <uls.h>

unsigned int mx_get_minor(t_file *file) {
    unsigned int minor = MX_MINOR(file->stat.st_rdev);

    return minor;
}
