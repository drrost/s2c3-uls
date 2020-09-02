#include <uls.h>

unsigned int mx_get_major(t_file *file) {
    unsigned int major = MX_MAJOR(file->stat.st_rdev);

    return major;
}
