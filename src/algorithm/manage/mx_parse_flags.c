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

    flags.A = mx_has_flag(line, 'A');
    flags.C = mx_has_flag(line, 'C');
    flags.G = mx_has_flag(line, 'G');
    flags.F = mx_has_flag(line, 'F');
    flags.R = mx_has_flag(line, 'R');
    flags.S = mx_has_flag(line, 'S');

    flags.a = mx_has_flag(line, 'a');
    flags.c = mx_has_flag(line, 'c');
    flags.f = mx_has_flag(line, 'f');
    flags.g = mx_has_flag(line, 'g');
    flags.i = mx_has_flag(line, 'i');
    flags.l = mx_has_flag(line, 'l');
    flags.m = mx_has_flag(line, 'm');
    flags.o = mx_has_flag(line, 'o');
    flags.p = mx_has_flag(line, 'p');
    flags.r = mx_has_flag(line, 'r');
    flags.t = mx_has_flag(line, 't');
    flags.u = mx_has_flag(line, 'u');

    flags._1 = mx_has_flag(line, '1');
    flags.at = mx_has_flag(line, '@');

    organize_flags(&flags, line);

    return flags;
}
