//
// Created by Rostyslav Druzhchenko on 07.09.2020.
//

#include <uls.h>
#include <unistd.h>

static char *delim() {
    char *delim = isatty(STDOUT_FILENO) ? "\t\t" : "\n";
    return mx_strdup(delim);
}

t_algorithm *mx_parse_arguments(int argc, char *argv[]) {
    t_algorithm *algorithm = mx_algorithm_new();
    int path_idx = 1;

    if (argc == 1) {
        algorithm->fetcher = mx_fetch_one_dir;
        algorithm->printer = mx_print_single_dir;
    }
    else {
        if (argv[1][0] == '-') {
            char *flags = argv[1];

            if (mx_get_char_index(flags, 'R') != -1) {
                algorithm->fetcher = mx_fetch_recursive;
                algorithm->printer = mx_print_dirs_recursive;
            }
            path_idx++;
        }
    }

    for (int i = path_idx; i < argc; i++)
        mx_push_back(&(algorithm->paths), mx_strdup(argv[i]));

    if (algorithm->paths == 0)
        mx_push_back(&(algorithm->paths), mx_strdup("."));

    algorithm->delim = delim();

    return algorithm;
}
