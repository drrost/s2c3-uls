//
// Created by Karina Barinova on 09.09.2020.
//


#include <uls.h>
#include <sys/types.h>

unsigned char mx_acl_strcol(char *acl) {
    if (acl[0] == 'd' && acl[8] == 'w' && acl[9] == 't')
        return MX_BLACK;
    else if (acl[0] == '-' && acl[9] == 'x')
        return MX_RED;
    else if (acl[0] == 'c' && acl[9] == 'b')
        return MX_BLUE;
    else if (acl[0] == 'd')
        return MX_BLUE;
    else if (acl[0] == 'l')
        return MX_MAGENTA;
    else if (acl[0] == 's')
        return MX_GREEN;
    else if (acl[0] == 'p')
        return MX_RED;
    return MX_DEFAULT;
}

unsigned char mx_acl_bkcol(char *acl) {
    if (acl[0] == 'd' && acl[8] == 'w' && acl[9] == 't')
        return MX_GREEN;
    else if (acl[0] == '-' && acl[9] == 'x')
        return MX_DEFAULT;
    else if (acl[0] == 'b')
        return MX_CYAN;
    else if (acl[0] == 'c')
        return MX_YELLOW;
    else if (acl[0] == 'd')
        return MX_DEFAULT;
    else if (acl[0] == 'l')
        return MX_DEFAULT;
    else if (acl[0] == 's')
        return MX_DEFAULT;
    else if (acl[0] == 'p')
        return MX_DEFAULT;
    return MX_DEFAULT;
}

int mx_color_set(unsigned char a, unsigned char b) {
    char *col = mx_strdup("\x1B[01;01m\0");
    char *a_str = mx_itoa(a + 30);
    char *b_str = mx_itoa(b + 40);
    unsigned int len = mx_strlen(col);

    col[2] = a_str[0];
    col[3] = a_str[1];
    col[5] = b_str[0];
    col[6] = b_str[1];
    mx_printstr(col);
    mx_strdel(&col);
    mx_strdel(&a_str);
    mx_strdel(&b_str);
    return len;
}

int mx_color_reset() {
    int len = 0;

    len += mx_strlen(MX_COLOR_RESET);
    mx_printstr(MX_COLOR_RESET);
    return len;
}
