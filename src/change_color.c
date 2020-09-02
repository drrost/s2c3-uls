#include <uls.h>

int mx_change_color(unsigned char t, unsigned char b) {
    char *cli = mx_strdup("\x1B[01;01m\0");
    char *t_str = mx_itoa(t + 30);
    char *b_str = mx_itoa(b + 40);
    unsigned int len = mx_strlen(cli);

    cli[2] = t_str[0];
    cli[3] = t_str[1];
    cli[5] = b_str[0];
    cli[6] = b_str[1];
    mx_printstr(cli);
    mx_strdel(&cli);
    mx_strdel(&t_str);
    mx_strdel(&b_str);
    return len;
}
