#include <uls.h>

static int check_flag(t_flags *flags, char flag) {
    if (mx_isupper(flag) || flag == '1')
        return mx_check_upper_flag(flags, flag);
    else if (mx_islower(flag))
        return mx_check_lower_flag(flags, flag);
    return 1;
}

void mx_read_flags(t_uls *uls, char *arg) {
    t_flags *flags = uls->flags;
    unsigned int len = 0;
    char err[2] = " \0";

    len = mx_strlen(arg);
    for (unsigned int i = 1; i < len; i++) {
        if (check_flag(flags, arg[i])) {
            err[0] = arg[i];
            mx_print_warning(MX_ERR_OPTION, err, "\n");
            mx_print_error(MX_ERR_USAGE, NULL, NULL);
        }
    }
}
