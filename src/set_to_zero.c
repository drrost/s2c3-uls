#include <uls.h>

void mx_set_to_zero(t_out *out) {
    out->count_link = 0;
    out->count_uname = 0;
    out->count_group = 0;
    out->count_size = 0;
    out->count_blocks = 0;
    out->blocks = 0;
    out->screen_size = 0;
    out->lenght = 0;
    out->count = 0;
    out->i = 0;
    out->j = 0;
    out->rows = 0;
    out->file_amount = 0;
}
