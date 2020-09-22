//
// Created by Rostyslav Druzhchenko on 22.09.2020.
//

#include <uls.h>

void mx_print_error_permission_denied(char *name) {
    mx_printerr("uls: ");
    mx_printerr(name);
    mx_printerr(": Permission denied\n");
    mx_exit_code(1);
}