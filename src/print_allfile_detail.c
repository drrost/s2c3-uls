#include <uls.h>

void mx_print_allfile_detail(t_file **file, t_flags *flags, t_out *out) {
    time_t this_time = time(NULL);

    out->flags = flags;
    mx_aligment_file(file, out);
    mx_print_blocks(out->blocks);
    for (int i = 0; file[i]; i++) {
        mx_read_out(file[i], out);
        if (flags->f_s) {
            mx_left_s_aligment(out->sblocks, out->count_blocks);
            mx_printchar(' ');
        }
        mx_printstr(file[i]->acl);
        mx_left_aligment(out->nlink, out->count_link);
        mx_print_time_name_color(file[i], this_time, flags, out);
        mx_clear_out(out);
    }
    mx_set_to_zero(out);
}
