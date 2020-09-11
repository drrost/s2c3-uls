//
// Created by Karina Barinova on 11.09.2020.
//

#include <uls.h>

static void mx_invalid_flags(char c) {
    mx_printstr(ILLEGAL_OPTION);
    mx_printchar(c);
    mx_printstr("\n");
    mx_printstr(USAGE);
}

bool check_valid_flags(const char *flags) {
    for (int i = 1; flags[i]; i++) {
        if (!mx_has_flag(FLAGS, flags[i])) {
            mx_invalid_flags(flags[i]);
            return false;
        }
    }
    return true;
}
