#include <uls.h>

void join_major(char *res, char *maj) {
    int maj_size = mx_strlen(maj);
    int spaces = 3 - maj_size;
    int i = 0;
    int j = 0;

    for (i = 0; i < spaces; i++)
        res[i] = ' ';
    for (i = spaces; i < maj_size + spaces; i++) {
        res[i] = maj[j];
        j++;
    }
    res[3] = ',';
    res[4] = ' ';
}

void join_minor(char *res, char *min) {
    int min_size = mx_strlen(min);
    int len = 3 - min_size;
    int i = 0;
    int j = 0;

    for (i = 0; i < len; i++)
        res[i + 5] = ' ';
    for (i = len; i < min_size + len; i++) {
        res[i + 5] = min[j];
        j++;
    }
}
void join_minor_hex(char *res, unsigned int min) {
    int i = 0;
    int j = 0;
    char *hex_min = mx_nbr_to_hex(min);
    int min_size = mx_strlen(hex_min);
    char hex[] = "0x00000000";

    for (i = 0; i < 10 - min_size; i++) {
        res[i + 5] = hex[j];
        j++;
    }
    j = 0;
    for (i = 0; i < min_size; i++) {
        res[i + 5 + (10 - min_size)] = hex_min[j];
        j++;
    }
    mx_strdel(&hex_min);
}

void mx_read_driver(t_file *file, t_driver *driver) {
    char *major = mx_itoa(mx_get_major(file));
    char *minor = mx_itoa(mx_get_minor(file));
    char *result = NULL;

    if (mx_get_minor(file) > 255) {
        driver->size = 0;
        result = mx_strnew(15);
        join_major(result, major);
        join_minor_hex(result, mx_get_minor(file));
    }
    else {
        driver->size = 8;
        result = mx_strnew(8);
        join_major(result, major);
        join_minor(result, minor);
    }
    mx_strdel(&major);
    mx_strdel(&minor);
    driver->driver = result;
}
