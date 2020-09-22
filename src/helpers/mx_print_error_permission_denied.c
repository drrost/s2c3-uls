//
// Created by Rostyslav Druzhchenko on 22.09.2020.
//

#include <uls.h>

char *path_last_component(char *s) {
    int len = mx_strlen(s);
    for (int i = len - 1; i >= 0; i--) {
        if (s[i] == '/') {
            char *r = &(s[i]) + 1;
            return r;
        }
    }
    return s;
}

void mx_print_error_permission_denied(char *name) {
    mx_printerr("uls: ");
    char *last = path_last_component(name);
    mx_printerr(last);
    mx_printerr(": Permission denied\n");
    mx_exit_code(1);
}
