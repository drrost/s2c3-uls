//
// Created by Rostyslav Druzhchenko on 19.09.2020.
//

#include <uls.h>

void mx_print_error_no_such_file(char *name) {
    mx_printerr("uls: ");
    mx_printerr(name);
    mx_printerr(": No such file or directory\n");
}
