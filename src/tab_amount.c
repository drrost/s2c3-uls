#include <uls.h>

int mx_tab_amount(char *str, int size) {
    int lenth = mx_unicode_strlen(str);
    int tab_count = tab_count = size / 8 - lenth / 8;

    return tab_count;
}
