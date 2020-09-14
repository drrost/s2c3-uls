//
// Created by Karina Barinova on 10.09.2020.
//

#include <uls.h>

static char *mx_get_int(int size, char *res) {
    char *hex = mx_strnew(size);
    int len = size - mx_strlen(res);

    for (int i = 0, j = 0; i < size; i++) {
        hex[i] = ' ';
        if (i == 0)
            hex[i] = ',';
        if (i >= len) {
            hex[i] = res[j];
            j++;
        }
    }
    mx_strdel(&res);
    return hex;
}

static char *mx_get_hex(int size, char *res) {
    char *hex = mx_strnew(size);
    int len = size - mx_strlen(res);

    hex[0] = ',';
    hex[1] = ' ';
    for (int i = 2, j = 0; i < size; i++) {
        hex[i] = '0';
        if (i == 3)
            hex[i] = 'x';
        if (i >= len) {
            hex[i] = res[j];
            j++;
        }
    }
    mx_strdel(&res);
    return hex;
}

static char *mx_get_minor(dev_t rdev) {
    if (MX_GETMINOR(rdev) > 255) {
        return mx_get_hex(12, mx_nbr_to_hex(MX_GETMINOR(rdev)));
    }
    char *s = mx_itoa(MX_GETMINOR(rdev));
    char *result = mx_get_int(5, s);
    mx_strdel(&s);
    return result;
}

char *mx_get_size(struct stat buf) {
    char *res_major = NULL;
    char *res_minor = NULL;
    char *res = NULL;

    if (MX_ISBLK(buf.st_mode) || MX_ISCHR(buf.st_mode)) {
        res_major = mx_itoa(MX_GETMAJOR(buf.st_rdev));
        res_minor = mx_get_minor(buf.st_rdev);
        res = mx_strjoin(res_major, res_minor);
        mx_strdel(&res_major);
        mx_strdel(&res_minor);
        return res;
    }
    else
        return mx_itoa(buf.st_size);
}
