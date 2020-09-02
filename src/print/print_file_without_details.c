#include <uls.h>

void mx_print_file_without_details(t_file **file, t_flags *flags, t_out *out) {
    out->count = mx_longest_name(file, &out->file_amount, flags);
    out->flags = flags;
    if (flags->f_s)
        mx_aligment_file(file, out);
    out->rows = mx_rows_amount(out->file_amount, out->count, &out->columns, &out);
    mx_print_file_without_details_cycle(file, out);
    mx_set_to_zero(out);
}
