//
// Created by Rostyslav Druzhchenko on 07.09.2020.
//

#include <uls.h>
#include <unistd.h>

static char *delim(t_flags flags) {
    char *delim;
    if (flags.m)
        delim = ", ";
    else if (flags._1)
        delim = "\n";
    else if (flags.l)
        delim = "  ";
    else if (flags.o || flags.G)
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

t_algorithm *mx_parse_arguments(int argc, char *argv[]) {
    t_algorithm *algorithm = mx_algorithm_new();
    int path_idx = 1;

    const char *line = argc > 1 && argv[1][0] == '-' ? line = argv[1] : "";
    t_flags uls_flags = mx_parse_flags(line);

    if (argc == 1) {
        if (!isatty(STDOUT_FILENO)) {
            algorithm->printer = mx_print_single_column;
        }
        else {
            algorithm->printer = mx_print_multicolumn;
        }
    }
    else {
        if (argv[1][0] == '-') {

            // Fetchers - R

            if (uls_flags.R) {
                algorithm->fetcher.fetch = mx_fetch_recursive;
                algorithm->printer = mx_print_dirs_recursive;
            }

            // Sorters - r, t, f

            if (uls_flags.r)
                algorithm->fetcher.comparator.reverse = true;
            if (uls_flags.t)
                algorithm->fetcher.comparator.cmp = mx_timesort;

            // Filters - a, A

            if (uls_flags.A)
                algorithm->fetcher.filter = mx_select_exclude_dot_dirs;
            if (uls_flags.a)
                algorithm->fetcher.filter = mx_select_all;

            // Printers - 1, G, l, m, o

            if (uls_flags._1) {
                if (uls_flags.a || uls_flags.A) {
                    algorithm->printer = mx_print_single_column_all; 
                } 
                else {
                    algorithm->printer = mx_print_single_column;
                }
            }

            if (uls_flags.m) {
                if (uls_flags.a || uls_flags.A) {
                    algorithm->printer = mx_print_dirs_m_all; 
                }
                else {
                    algorithm->printer = mx_print_dirs_m;
                }
            }
            if (uls_flags.a && algorithm->printer == 0) {
                algorithm->printer = mx_print_multicolumn_all;
            }
            if (uls_flags.A && algorithm->printer == 0) {
                algorithm->printer = mx_print_multicolumn_all;
            }
            if (uls_flags.l) {
                algorithm->printer = mx_print_long;
            }
            if (uls_flags.o) {
                algorithm->printer = mx_print_long_o;
            }
            if (uls_flags.F) {
                algorithm->printer = mx_print_multicolumn_F;
            }
            if (uls_flags.G) {
                algorithm->printer = mx_print_multicolumn_color;
            }

            path_idx++;
        }
    }

    algorithm->delim = delim(uls_flags);

    for (int i = path_idx; i < argc; i++)
        mx_push_back(&(algorithm->paths), mx_strdup(argv[i]));

    set_defaults(algorithm);

    return algorithm;
}
