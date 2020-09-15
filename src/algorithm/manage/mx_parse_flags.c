//
// Created by Rostyslav Druzhchenko on 11.09.2020.
//

#include <uls.h>

static void organize_flags(t_flags *flags, const char *line) {
    if (flags->f)
        flags->a = true;
    if (flags->o)
        flags->l = false;

    if (flags->_1 && flags->m && flags->l) {
        if (line[mx_strlen(line) - 1] == 'm') {
            flags->_1 = false;
            flags->l = false;
        }
        if (line[mx_strlen(line) - 1] == '1') {
            flags->m = false;
            flags->l = false;
        }
        if (line[mx_strlen(line) - 1] == 'l') {
            flags->_1 = false;
            flags->m = false;
        }
    }

    if (flags->_1 && flags->m) {
        if (line[mx_strlen(line) - 1] == 'm')
            flags->_1 = false;
        else
            flags->m = false;
    }

    if (flags->m && flags->l) {
        if (line[mx_strlen(line) - 1] == 'm')
            flags->l = false;
        else
            flags->m = false;
   }

    if (flags->l && flags->_1) {
        if (line[mx_strlen(line) - 1] == 'l')
           flags->_1 = false;
        else
           flags->l = false;
    }
}

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
    if (mx_has_flag(line, 'f'))
        flags.f = true;
    if (mx_has_flag(line, 'g'))
        flags.g = true;
    if (mx_has_flag(line, 'l'))
        flags.l = true;
    if (mx_has_flag(line, 'm'))
        flags.m = true;
    if (mx_has_flag(line, 'o'))
        flags.o = true;
    if (mx_has_flag(line, 'p'))
        flags.p = true;
    if (mx_has_flag(line, 'r'))
        flags.r = true;
    if (mx_has_flag(line, 't'))
        flags.t = true;
    if (mx_has_flag(line, 'u'))
        flags.u = true;

    if (mx_has_flag(line, '1'))
        flags._1 = true;

    organize_flags(&flags, line);

    return flags;
}
