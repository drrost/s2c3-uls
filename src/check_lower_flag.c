#include <uls.h>


static int check_1st_flag(t_flags *flags, char flag) {
    if (flag == 'l') {
        flags->detail = 1;
        flags->f_1 = 0;
        flags->f_C = 0;
    }
    else if (flag == 'a') {
        flags->def_dots = 1;
        flags->def_file_dots = 1;
    }
    else if (flag == 'c') {
        flags->f_c = 1;
        flags->f_U = 0;
        flags->f_u = 0;
    }
    else
        return 1;
    return 0;
}

static int check_2nd_flag(t_flags *flags, char flag) {
    int fcheck1 = check_1st_flag(flags, flag);

    if (flag == 'f') {
        flags->f_f = 1;
        flags->def_dots = 1;
        flags->def_file_dots = 1;
    }
    else if (flag == 'g') {
        flags->f_g = 1;
        flags->detail = 1;
        flags->f_1 = 0;
        flags->f_C = 0;
        flags->f_m = 0;
    }
    else if (flag == 'h') {
        flags->f_h = 1;
    }
    else
        return fcheck1;
    return 0;
}

static int check_3rd_flag(t_flags *flags, char flag) {
    int fcheck2 = check_2nd_flag(flags, flag);

    if (flag == 'm') {
        flags->f_m = 1;
        flags->detail = 0;
        flags->f_C = 0;
        flags->f_g = 0;
        flags->f_1 = 0;
    }
    else if (flag == 'o') {
        flags->f_o = 1;
        flags->detail = 1;
        flags->f_1 = 0;
        flags->f_C = 0;
        flags->f_m = 0;
    }
    else
        return fcheck2;
    return 0;
}

int mx_check_lower_flag(t_flags *flags, char flag) {
    int fcheck3 = check_3rd_flag(flags, flag);

    if (flag == 'q')
        flags->f_q = 1;
    else if (flag == 'r')
        flags->f_r = 1;
    else if (flag == 's')
        flags->f_s = 1;
    else if (flag == 't')
        flags->f_t = 1;
    else if (flag == 'u') {
        flags->f_u = 1;
        flags->f_U = 0;
        flags->f_c = 0;
    }
    else
        return fcheck3;
    return 0;
}
