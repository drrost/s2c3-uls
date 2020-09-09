#include <uls.h>
#include <stdlib.h>

t_flags *mx_flags_new() {
    t_flags *flags = (t_flags *)malloc(sizeof(t_flags));
    mx_memset(flags, 0, sizeof(t_flags));
    return flags;
}
