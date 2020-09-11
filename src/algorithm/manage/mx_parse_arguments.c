//
// Created by Rostyslav Druzhchenko on 07.09.2020.
//

#include <uls.h>
#include <unistd.h>
#include <stdlib.h>

static char *delim(t_flags *flags) {
    char *delim;
    if (flags->flag_m)
        delim = ", ";
    else if (flags->flag_1)
        delim = "\n";
    else if (flags->flag_l)
        delim = "  ";
    else if (flags->flag_o || flags->flag_G)
        delim = " ";
    else
        delim = isatty(STDOUT_FILENO) ? "\t" : "\n";
    return mx_strdup(delim);
}

static void set_defaults(t_algorithm *algorithm) {
    if (algorithm->paths == 0)
        mx_push_back(&(algorithm->paths), mx_strdup("."));

    if (algorithm->fetcher.filter == 0)
        algorithm->fetcher.filter = mx_select_exclude_dot_dirs;

    if (algorithm->fetcher.fetch == 0)
        algorithm->fetcher.fetch = mx_fetch_one_dir;

    if (algorithm->fetcher.comparator.cmp == 0) {
        algorithm->fetcher.comparator.cmp = mx_alphasort;
    }

    if (algorithm->printer == 0)
        algorithm->printer = mx_print_single_column;
}

bool has_flag(const char *flags, char ch) {
    return mx_get_char_index(flags, ch) != -1;
}

t_flags *set_flags(t_flags *flags, const char *argv) {
    if (has_flag(argv, 'm'))
        flags->flag_m = true;
    if (has_flag(argv, 'R'))
        flags->flag_R = true;
    if (has_flag(argv, 'r'))
        flags->flag_r = true;
    if (has_flag(argv, '1'))
        flags->flag_1 = true;
    if (has_flag(argv, 'o'))
        flags->flag_o = true;
    if (has_flag(argv, 'F'))
        flags->flag_F = true;
    if (has_flag(argv, 'G'))
        flags->flag_G = true;
    if (has_flag(argv, 'a'))
        flags->flag_a = true;
    if (has_flag(argv, 'A'))
        flags->flag_A = true;
    if (has_flag(argv, 'r'))
        flags->flag_r = true;
    if (has_flag(argv, 'l'))
        flags->flag_l = true;
    //flags = disable_flags(flags);
    return flags;
}

t_algorithm *mx_parse_arguments(int argc, char *argv[]) {
    t_algorithm *algorithm = mx_algorithm_new();
    t_flags *uls_flags = mx_flags_new();
    int path_idx = 1;
    algorithm->fetcher.comparator.reverse = false;

    if (argc == 1) {
        algorithm->fetcher.fetch = mx_fetch_one_dir;
        algorithm->printer = mx_print_multicolumn;
    }
    else {
        if (argv[1][0] == '-') {
            char *flags = argv[1];

            if (!check_valid_flags(flags))
                exit(1);
            uls_flags = set_flags(uls_flags, flags);

            if (uls_flags->flag_a)
                algorithm->fetcher.filter = mx_select_all;
            if (uls_flags->flag_A)
                algorithm->fetcher.filter = mx_select_exclude_dot_dirs;

            if (uls_flags->flag_R) {
                algorithm->fetcher.fetch = mx_fetch_recursive;
                algorithm->printer = mx_print_dirs_recursive;                
            }

            if (uls_flags->flag_1) {
                if (uls_flags->flag_a || uls_flags->flag_A) {
                    algorithm->printer = mx_print_single_column_all; 
                } 
                else {
                    algorithm->printer = mx_print_single_column;
                }
            }

            if (uls_flags->flag_m) {
                algorithm->fetcher.fetch = mx_fetch_one_dir;
                    algorithm->printer = mx_print_dirs_m;
            }
            if (uls_flags->flag_a && algorithm->printer == 0) {
                algorithm->printer = mx_print_multicolumn_all;
            }
            if (uls_flags->flag_A && algorithm->printer == 0) {
                algorithm->printer = mx_print_multicolumn_all;
            }
            if (uls_flags->flag_l) {
                algorithm->fetcher.fetch = mx_fetch_one_dir;
                algorithm->printer = mx_print_long;
            }
            if (uls_flags->flag_o) {
                algorithm->fetcher.fetch = mx_fetch_one_dir;
                algorithm->printer = mx_print_long_o;
            }
            if (uls_flags->flag_F) {
                algorithm->fetcher.fetch = mx_fetch_one_dir;
                algorithm->printer = mx_print_multicolumn_F;
            }
            if (uls_flags->flag_G) {
                algorithm->fetcher.fetch = mx_fetch_one_dir;
                algorithm->printer = mx_print_multicolumn_color;
            }

                // Sorters
            if (uls_flags->flag_r)
                algorithm->fetcher.comparator.reverse = true;

            path_idx++;
            
        }
    }

    algorithm->delim = delim(uls_flags);
    mx_flags_delete(&uls_flags);

    for (int i = path_idx; i < argc; i++)
        mx_push_back(&(algorithm->paths), mx_strdup(argv[i]));

    set_defaults(algorithm);

    return algorithm;
}
