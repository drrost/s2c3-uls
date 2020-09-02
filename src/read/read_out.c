#include <uls.h>

void mx_read_out(t_file *file, t_out *out) {
    out->nlink = mx_itoa(file->stat.st_nlink);
    if (out->flags->f_h)
        out->size = mx_gen_sizconstr(file->stat.st_size);
    else
        out->size = mx_itoa(file->stat.st_size);
    out->gid = mx_itoa(file->gid);
    out->sblocks = mx_itoa(file->blocks);
}
