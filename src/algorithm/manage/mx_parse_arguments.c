//
// Created by Rostyslav Druzhchenko on 07.09.2020.
//

#include <uls.h>
#include <unistd.h>

static char *delim(t_flags *flags) {
    char *delim;
    if (flags->flag_m)
        delim = ", ";
    else if (flags->flag_1)
        delim = "\n";
    else if (flags->flag_l)
        delim = "  ";
    else if (flags->flag_o)
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

    if (algorithm->fetcher.sort_cmp == 0)
        algorithm->fetcher.sort_cmp = mx_alphasort;
}

static bool has_flag(const char *flags, char ch) {
    return mx_get_char_index(flags, ch) != -1;
}

t_algorithm *mx_parse_arguments(int argc, char *argv[]) {
    t_algorithm *algorithm = mx_algorithm_new();
    t_flags *uls_flags = mx_flags_new();
    int path_idx = 1;

    if (argc == 1) {
        algorithm->fetcher.fetch = mx_fetch_one_dir;
        algorithm->printer = mx_print_multicolumn;
    }
    else {
        if (argv[1][0] == '-') {
            char *flags = argv[1];

            if (has_flag(flags, 'R')) {
                uls_flags->flag_R = true;
                algorithm->fetcher.fetch = mx_fetch_recursive;
                algorithm->printer = mx_print_dirs_recursive;
            }

            if (has_flag(flags, '1')) {
                uls_flags->flag_1 = true;
                algorithm->fetcher.fetch = mx_fetch_one_dir;
                algorithm->printer = mx_print_single_column;
            }

            if (has_flag(flags, 'm')) {
                uls_flags->flag_m = true;
                algorithm->fetcher.fetch = mx_fetch_one_dir;
                algorithm->printer = mx_print_dirs_m;
            }
            if (has_flag(flags, 'a')) {
                uls_flags->flag_a = true;
                algorithm->fetcher.fetch = mx_fetch_one_dir;
                algorithm->fetcher.filter = mx_select_all;
                algorithm->printer = mx_print_multicolumn_all;
            }
            if (has_flag(flags, 'A')) {
                uls_flags->flag_A = true;
                algorithm->fetcher.fetch = mx_fetch_one_dir;
                algorithm->printer = mx_print_multicolumn_all;
            }
            if (has_flag(flags, 'l')) {
                uls_flags->flag_l = true;
                algorithm->fetcher.fetch = mx_fetch_one_dir;
                algorithm->printer = mx_print_long;
            }
            if (has_flag(flags, 'o')) {
                uls_flags->flag_o = true;
                algorithm->fetcher.fetch = mx_fetch_one_dir;
                algorithm->printer = mx_print_long_o;
            }
            if (has_flag(flags, 'F')) {
                uls_flags->flag_F = true;
                algorithm->fetcher.fetch = mx_fetch_one_dir;
                algorithm->printer = mx_print_multicolumn_F;
            }

            // Sorters
            if (has_flag(flags, 'r'))
                algorithm->fetcher.sort_cmp = mx_alphasort;

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
