#include <uls.h>

int mx_space_amount(char *str, int size) {
    int lenth = mx_unicode_strlen(str);
    int space_count = 0;

    space_count = size - lenth;
    return space_count;
}
