//
// Created by Rostyslav Druzhchenko on 11.09.2020.
//

#include <uls.h>

bool mx_has_flag(const char *flags, char ch) {
    return mx_get_char_index(flags, ch) != -1;
}
