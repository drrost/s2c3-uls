//
// Created by Rostyslav Druzhchenko on 11.09.2020.
//

#include <uls.h>

static void organize_flags(t_flags *flags) {
    if (flags->f)
        flags->a = true;
}

//t_flags *disable_flags(t_flags *flags, const char *argv) {
//    if (flags->flag_1 && flags->flag_m && flags->flag_l) {
//        if (argv[mx_strlen(argv) - 1] == 'm') {
//            flags->flag_1 = false;
//            flags->flag_l = false;
//        }
//        if (argv[mx_strlen(argv) - 1] == '1') {
//            flags->flag_m = false;
//            flags->flag_l = false;
//        }
//        if (argv[mx_strlen(argv) - 1] == 'l') {
//            flags->flag_1 = false;
//            flags->flag_m = false;
//        }
//    }
//    if (flags->flag_1 && flags->flag_m) {
//        if (argv[mx_strlen(argv) - 1] == 'm')
//            flags->flag_1 = false;
//        else
//            flags->flag_m = false;
//    }
//    if (flags->flag_m && flags->flag_l) {
//        if (argv[mx_strlen(argv) - 1] == 'm')
//            flags->flag_l = false;
//        else
//            flags->flag_m = false;
//    }
//    if (flags->flag_l && flags->flag_1) {
//        if (argv[mx_strlen(argv) - 1] == 'l')
//            flags->flag_1 = false;
//        else
//            flags->flag_l = false;
//    }
//
//    return flags;
//}

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

    organize_flags(&flags);

    return flags;
}
