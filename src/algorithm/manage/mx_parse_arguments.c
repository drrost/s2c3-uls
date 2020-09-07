//
// Created by Rostyslav Druzhchenko on 07.09.2020.
//

#include <uls.h>
#include <stdlib.h>
#include <unistd.h>

t_algorithm *mx_algorithm_new() {
    t_algorithm *algorithm = (t_algorithm *)malloc(sizeof(t_algorithm));
    mx_memset(algorithm, 0, sizeof(t_algorithm));
    return algorithm;
}

void mx_algorithm_del(t_algorithm **algorithm) {
    mx_strdel(&((*algorithm)->delim));
    t_list *work = (*algorithm)->paths;
    while (work) {
        char *s = (char *)work->data;
        mx_strdel(&s);
        mx_pop_front(&work);
    }
}

static int mx_arr_size(char **arr) {
    int size = 0;
    while (*arr) {
        arr++;
        size++;
    }
    return size;
}

t_algorithm *mx_parse_arguments(const char *line) {
    char **arr = mx_strsplit(line, ' ');
    int size = mx_arr_size(arr);

    t_algorithm *algorithm = mx_algorithm_new();
    if (size == 0) {
        char *path = mx_strdup(".");
        mx_push_back(&(algorithm->paths), path);
        algorithm->fetcher = mx_fetch_one_dir;
        algorithm->printer = mx_print_dir_content;
    }

    char *delim = isatty(STDOUT_FILENO) ? "\t\t" : "\n";
    algorithm->delim = mx_strdup(delim);

    mx_del_strarr(&arr);
    return algorithm;
}
