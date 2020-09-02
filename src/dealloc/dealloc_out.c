#include <uls.h>

void mx_dealloc_out(t_out *out) {
    mx_clear_out(out);
    free(out);
}
