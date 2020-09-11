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
}

static void assign_fetchers(t_algorithm *algorithm, t_flags *flags) {
    if (flags->R)
        algorithm->fetcher.fetch = mx_fetch_recursive;
    else
        algorithm->fetcher.fetch = mx_fetch_one_dir;
}

static void assign_sorters(t_algorithm *algorithm, t_flags *flags) {
    algorithm->fetcher.comparator.cmp = mx_alphasort;

    if (flags->r)
        algorithm->fetcher.comparator.reverse = true;
    if (flags->t)
        algorithm->fetcher.comparator.cmp = mx_timesort;
}

static void assign_filters(t_algorithm *algorithm, t_flags *flags) {
    algorithm->fetcher.filter = mx_select_exclude_dot_dirs;

    if (flags->A)
        algorithm->fetcher.filter = mx_select_exclude_dot_dirs;
    if (flags->a)
        algorithm->fetcher.filter = mx_select_all;
}

static void assign_printers(t_algorithm *algorithm, t_flags *flags) {
    algorithm->printer = mx_print_single_column;

    if (flags->R)
        algorithm->printer = mx_print_dirs_recursive;

    if (flags->_1) {
        if (flags->a || flags->A) {
            algorithm->printer = mx_print_single_column_all;
        }
        else {
            algorithm->printer = mx_print_single_column;
        }
    }

    if (flags->m) {
        if (flags->a || flags->A) {
            algorithm->printer = mx_print_dirs_m_all;
        }
        else {
            algorithm->printer = mx_print_dirs_m;
        }
    }
    if (flags->a && algorithm->printer == 0) {
        algorithm->printer = mx_print_multicolumn_all;
    }
    if (flags->A && algorithm->printer == 0) {
        algorithm->printer = mx_print_multicolumn_all;
    }
    if (flags->l) {
        algorithm->printer = mx_print_long;
    }
    if (flags->o) {
        algorithm->printer = mx_print_long_o;
    }
    if (flags->F) {
        algorithm->printer = mx_print_multicolumn_F;
    }
    if (flags->G) {
        algorithm->printer = mx_print_multicolumn_color;
    }
}

t_algorithm *mx_parse_arguments(int argc, char *argv[]) {
    t_algorithm *algorithm = mx_algorithm_new();
    int path_idx = argc > 1 && argv[1][0] == '-' ? 2 : 1;
    const char *line = argc > 1 && argv[1][0] == '-' ? line = argv[1] : "";
    t_flags flags = mx_parse_flags(line);

    assign_fetchers(algorithm, &flags);
    assign_sorters(algorithm, &flags);
    assign_filters(algorithm, &flags);
    assign_printers(algorithm, &flags);

//    if (argc == 1) {
//        if (!isatty(STDOUT_FILENO)) {
//            algorithm->printer = mx_print_single_column;
//        }
//        else {
//            algorithm->printer = mx_print_multicolumn;
//        }
//    }

    algorithm->delim = delim(flags);

    for (int i = path_idx; i < argc; i++)
        mx_push_back(&(algorithm->paths), mx_strdup(argv[i]));

    set_defaults(algorithm);

    return algorithm;
}
