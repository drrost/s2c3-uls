//
// Created by Rostyslav Druzhchenko on 19.09.2020.
//

#include <uls.h>

void mx_check_options_e(const char *line) {
    int size = mx_strlen(line);
    char flag[2];
    flag[1] = 0;
    for (int i = 1; i < size; i++)
        if (mx_has_flag(FLAGS, line[i]) == false) {
            flag[0] = line[i];
            mx_print_error_exit(ERROR_ILLEGAL_OPTION, flag);
        }
}
