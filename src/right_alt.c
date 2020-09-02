#include <uls.h>

void mx_right_alt(char *str, int count) {
    int len = mx_unicode_strlen(str);

    if (len == count) {
        mx_printchar(' ');
        mx_printstr(str);
        mx_printchar(' ');
    }
    else {
        mx_printchar(' ');
        mx_printstr(str);
        for (int i = count - len; i > 0; i--)
            mx_printchar(' ');
        mx_printchar(' ');
    }
}
