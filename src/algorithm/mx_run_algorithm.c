//
// Created by Rostyslav Druzhchenko on 07.09.2020.
//

#include <uls.h>

static t_list *run_fetcher(const char *path, t_fetcher fetcher) {
    return fetcher.fetch(path, fetcher.filter, fetcher.comparator);
}

void (*select_printer(t_printer printer, t_dir *dir))(PRINTER_PARAMS) {
    if (S_ISLNK(dir->i_stat.st_mode))
        return printer.printer_link;
    return printer.printer;
}

static void run_printer(t_printer printer, t_list *dirs) {
    int len = mx_list_size(dirs);
    if (len <= 1) {
        t_dir *dir = (t_dir *)dirs->data;
        PRINTER(printer_f) = select_printer(printer, dir);
        printer_f(dir->entities, printer.delim);
    }
    else if (printer.is_recursive == true)
        mx_print_dirs_recursive(dirs, printer.delim, printer.printer);
    else {
        mx_print_dirs_long(dirs, printer.delim, printer.printer);
    }
}

static void delete_dirs_list(t_list **dirs) {
    while (*dirs) {
        t_dir *dir = (t_dir *)((*dirs)->data);
        mx_dirdelete(&dir);
        mx_pop_front(dirs);
    }
}

static t_list *fetch_all(t_list *paths, t_fetcher fetcher) {
    t_list *result = 0;
    while (paths) {
        char *path = (char *)paths->data;
        t_list *one_dir = run_fetcher(path, fetcher);
        mx_list_attach_back(&result, one_dir);
        paths = paths->next;
    }
    return result;
}

void mx_run_algorithm(t_algorithm *algorithm) {
    if (algorithm->paths == 0)
        return;
    t_list *dirs = fetch_all(algorithm->paths, algorithm->fetcher);
    run_printer(algorithm->printer, dirs);
    delete_dirs_list(&dirs);
}
