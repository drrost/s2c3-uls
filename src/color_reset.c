#include <uls.h>

int mx_color_reset() {
    int len = 0;

    len += mx_strlen(MX_RESET);
    mx_printstr(MX_RESET);
    return len;
}
