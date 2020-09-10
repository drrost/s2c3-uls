#include <uls.h>
#include <stdlib.h>

t_flags *mx_flags_new() {
    t_flags *flags = (t_flags *)malloc(sizeof(t_flags));

    flags->flag_l = false;
    flags->flag_a = false;
    flags->flag_A = false;
    flags->flag_R = false;
    flags->flag_1 = false;
    flags->flag_m = false;
    flags->flag_G = false;
    
    mx_memset(flags, 0, sizeof(t_flags));
    return flags;
}
