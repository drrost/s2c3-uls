#include <uls.h>
#include <stdlib.h>

void mx_dealloc_out(t_out *out) {
    mx_clear_out(out);
    free(out);
}
