//
// Created by Rostyslav Druzhchenko on 19.09.2020.
//

#include <uls.h>

int mx_exit_code(int set) {
    static int code = 0;
    if (set == -1)
        return code;
    code = set;
    return code;
}

void mx_print_error_no_such_file(char *name) {
    mx_printerr("uls: ");
    mx_printerr(name);
    mx_printerr(": No such file or directory\n");
    mx_exit_code(1);
}
