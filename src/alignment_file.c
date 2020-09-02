#include <uls.h>

void mx_aligment_file(t_file **file, t_out *out) {
    for (int i = 0; file[i]; i++) {
        mx_read_out(file[i], out);
        if (out->count_link < mx_strlen(out->nlink))
            out->count_link = mx_strlen(out->nlink);
        if (out->count_uname < mx_strlen(file[i]->username))
            out->count_uname = mx_strlen(file[i]->username);
        if (file[i]->gr && out->count_group < mx_strlen(file[i]->gr))
            out->count_group = mx_strlen(file[i]->gr);
        else if (out->count_group < mx_strlen(out->gid))
            out->count_group = mx_strlen(out->gid);
        if (out->count_size < (unsigned int)mx_strlen(out->size))
            out->count_size = mx_strlen(out->size);
        if (file[i]->driver && out->count_size < file[i]->driver->size)
            out->count_size = file[i]->driver->size;
        if (out->count_blocks < mx_strlen(out->sblocks))
            out->count_blocks = mx_strlen(out->sblocks);
        out->blocks = out->blocks + file[i]->blocks;
        mx_clear_out(out);
    }
}
