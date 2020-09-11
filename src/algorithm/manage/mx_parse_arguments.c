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

t_algorithm *mx_parse_arguments(int argc, char *argv[]) {
    t_algorithm *algorithm = mx_algorithm_new();
    int path_idx = argc > 1 && argv[1][0] == '-' ? 2 : 1;
    const char *line = argc > 1 && argv[1][0] == '-' ? argv[1] : "";

    t_flags flags = mx_parse_flags(line);

    mx_assign_fetchers(algorithm, &flags);
    mx_assign_sorters(algorithm, &flags);
    mx_assign_filters(algorithm, &flags);
    mx_assign_printers(algorithm, &flags);

    algorithm->delim = delim(flags);

    for (int i = path_idx; i < argc; i++)
        mx_push_back(&(algorithm->paths), mx_strdup(argv[i]));

    set_defaults(algorithm);

    return algorithm;
}
