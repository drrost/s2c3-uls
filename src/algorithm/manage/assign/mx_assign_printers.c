//
// Created by Rostyslav Druzhchenko on 11.09.2020.
//

#include <uls.h>
#include <unistd.h>

void mx_assign_printers(t_algorithm *algorithm, t_flags *flags) {
    if (flags->C && !isatty(STDOUT_FILENO))
        algorithm->printer.printer = mx_print_multicolumn_C;
    else if (!isatty(STDOUT_FILENO))
        algorithm->printer.printer = mx_print_single_column;
    else
        algorithm->printer.printer = mx_print_multicolumn;

    if (flags->R)
        algorithm->printer.is_recursive = true;
    if (flags->_1)
        algorithm->printer.printer = mx_print_single_column;
    if (flags->m)
        algorithm->printer.printer = mx_print_dirs_m;
    if (flags->t)
        algorithm->printer.printer = mx_print_multicolumn;
    if (flags->l)
        algorithm->printer.printer = mx_print_long;
    if (flags->o)
        algorithm->printer.printer = mx_print_long_o;
    if (flags->g)
        algorithm->printer.printer = mx_print_long_g;
    if (flags->F)
        algorithm->printer.printer = mx_print_multicolumn_F;
    if (flags->G)
        algorithm->printer.printer = mx_print_multicolumn_color;
    if (flags->p)
        algorithm->printer.printer = mx_print_multicolumn_p;
}
