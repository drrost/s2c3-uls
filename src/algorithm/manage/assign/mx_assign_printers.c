//
// Created by Rostyslav Druzhchenko on 11.09.2020.
//

#include <uls.h>

void mx_assign_printers(t_algorithm *algorithm, t_flags *flags) {
    algorithm->printer = mx_print_single_column;

    if (flags->R)
        algorithm->printer = mx_print_dirs_recursive;

    if (flags->_1) {
        if (flags->a || flags->A) {
            algorithm->printer = mx_print_single_column_all;
        }
        else {
            algorithm->printer = mx_print_single_column;
        }
    }

    if (flags->m) {
        if (flags->a || flags->A) {
            algorithm->printer = mx_print_dirs_m_all;
        }
        else {
            algorithm->printer = mx_print_dirs_m;
        }
    }
    if (flags->a && algorithm->printer == 0) {
        algorithm->printer = mx_print_multicolumn_all;
    }
    if (flags->A && algorithm->printer == 0) {
        algorithm->printer = mx_print_multicolumn_all;
    }
    if (flags->l) {
        algorithm->printer = mx_print_long;
    }
    if (flags->o) {
        algorithm->printer = mx_print_long_o;
    }
    if (flags->F) {
        algorithm->printer = mx_print_multicolumn_F;
    }
    if (flags->G) {
        algorithm->printer = mx_print_multicolumn_color;
    }

//    if (argc == 1) {
//        if (!isatty(STDOUT_FILENO)) {
//            algorithm->printer = mx_print_single_column;
//        }
//        else {
//            algorithm->printer = mx_print_multicolumn;
//        }
//    }
}
