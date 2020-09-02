#include <uls.h>

void mx_print_file_detail(t_file **file, t_flags *flags, t_out *out) {
    time_t this_time = time(NULL);

    out->flags = flags;
    flags->print_empty_lines = 1;
    mx_aligment_file(file, out);
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
