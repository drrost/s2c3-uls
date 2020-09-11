//
// Created by Rostyslav Druzhchenko on 11.09.2020.
//

#include <uls.h>

t_flags mx_parse_flags(const char *line) {
    t_flags flags;
    mx_memset(&flags, 0, sizeof(t_flags));

    if (mx_has_flag(line, 'A'))
        flags.A = true;
    if (mx_has_flag(line, 'G'))
        flags.G = true;
    if (mx_has_flag(line, 'F'))
        flags.F = true;
    if (mx_has_flag(line, 'R'))
        flags.R = true;

    if (mx_has_flag(line, 'a'))
        flags.a = true;
    if (mx_has_flag(line, 'l'))
        flags.l = true;
    if (mx_has_flag(line, 'm'))
        flags.m = true;
    if (mx_has_flag(line, 'o'))
        flags.o = true;
    if (mx_has_flag(line, 'r'))
        flags.r = true;
    if (mx_has_flag(line, 't'))
        flags.r = true;

    if (mx_has_flag(line, '1'))
        flags._1 = true;
    return flags;
}
