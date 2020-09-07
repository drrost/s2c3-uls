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
        char *path = mx_strdup(".");
        mx_push_back(&(algorithm->paths), path);
        algorithm->fetcher = mx_fetch_one_dir;
        algorithm->printer = mx_print_dir_content;
    }
    else {
        if (argv[1][0] == '-') {
            // handle flags
            path_idx++;
        }
    }

    for (int i = path_idx; i < argc; i++) {
        mx_push_back(&(algorithm->paths), argv[i]);
    }

    algorithm->delim = delim();

    return algorithm;
}
