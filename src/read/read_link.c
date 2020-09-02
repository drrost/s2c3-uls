#include <uls.h>

char *mx_read_link(t_file *file, char *path) {
    ssize_t bufsize = file->stat.st_size + 1;
    ssize_t rl = 0;
    char *buf;

    if (file->stat.st_size == 0)
        bufsize = 1023;
    buf = mx_strnew(bufsize);
    rl = readlink(path, buf, bufsize);
    if (rl == -1) {
        mx_strdel(&buf);
        return NULL;
    }
    return buf;
}
