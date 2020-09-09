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
    else
        delim = isatty(STDOUT_FILENO) ? "\t" : "\n";
    return mx_strdup(delim);
}

t_algorithm *mx_parse_arguments(int argc, char *argv[]) {
    t_algorithm *algorithm = mx_algorithm_new();
    t_flags *uls_flags = mx_flags_new();
    int path_idx = 1;

    if (argc == 1) {
        algorithm->fetcher = mx_fetch_one_dir;
        algorithm->printer = mx_print_multicolumn;
    }
    else {
        if (argv[1][0] == '-') {
            char *flags = argv[1];

            if (mx_get_char_index(flags, 'R') != -1) {
                uls_flags->flag_R = true;
                algorithm->fetcher = mx_fetch_recursive;
                algorithm->printer = mx_print_dirs_recursive;
            }

            if (mx_get_char_index(flags, '1') != -1) {
                uls_flags->flag_1 = true;
                algorithm->fetcher = mx_fetch_one_dir;
                algorithm->printer = mx_print_single_column;
            }

            if (mx_get_char_index(flags, 'm') != -1) {
                uls_flags->flag_m = true;
                algorithm->fetcher = mx_fetch_one_dir;
                algorithm->printer = mx_print_dirs_m;
            }
            path_idx++;
        }
    }

    for (int i = path_idx; i < argc; i++)
        mx_push_back(&(algorithm->paths), mx_strdup(argv[i]));

    if (algorithm->paths == 0)
        mx_push_back(&(algorithm->paths), mx_strdup("."));

    algorithm->delim = delim(uls_flags);
    mx_flags_delete(&uls_flags);

    return algorithm;
}
