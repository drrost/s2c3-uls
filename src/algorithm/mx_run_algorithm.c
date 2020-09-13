//
// Created by Rostyslav Druzhchenko on 07.09.2020.
//

#include <uls.h>

static t_list *run_fetcher(const char *path, t_fetcher fetcher) {
    return fetcher.fetch(path, fetcher.filter, fetcher.comparator);
}

static void run_printer(t_printer printer, t_list *dirs) {
    if (printer.is_recursive == false) {
        t_dir *dir = (t_dir *)dirs->data;
        printer.printer(dir->entities, printer.delim);
    }
    else
        mx_print_dirs_recursive(dirs, printer.delim, printer.printer);
}

void mx_run_algorithm(t_algorithm *algorithm) {
    char *path = (char *)algorithm->paths->data;
    t_list *dirs = run_fetcher(path, algorithm->fetcher);

    run_printer(algorithm->printer, dirs);

    // TODO: Move to a separate method
    while (dirs) {
        t_dir *dir = (t_dir *)dirs->data;
        mx_dirdelete(&dir);
        mx_pop_front(&dirs);
    }
}
