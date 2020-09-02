#include <uls.h>
#include <stdlib.h>

t_out *mx_create_out() {
    t_out *out = (t_out *)malloc(sizeof(t_out));

    if (out) {
        out->i = out->j = out->k = 0;
        out->count = out->count_group = 0;
        out->count_link = out->count_uname = 0;
        out->file_amount = out->argc = 0;
        out->columns = 0;
        out->rows = 0;
        out->screen_size = 0;
        out->count_blocks = 0;
        out->count_size = out->lenght = 0;
        out->blocks = 0;
        out->name = NULL;
        out->nlink = NULL;
        out->size = NULL;
        out->gid = NULL;
        out->flags = NULL;
    }
    return out;
}
