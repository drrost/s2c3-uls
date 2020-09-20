//
// Created by Rostyslav Druzhchenko on 07.09.2020.
//

#include <uls.h>

static t_list *run_fetcher(const char *path, t_fetcher fetcher) {
    return fetcher.fetch(path, fetcher.filter, fetcher.comparator);
}

static void print_dir_as_link(t_dir *dir, t_printer printer) {
    t_list *list = 0;
    t_dirent *dir_ent = mx_dirent_new(dir->name, dir->i_stat.st_mode);
    dir_ent->file_stat = dir->i_stat;
    dir_ent->path = mx_strdup(".");

    mx_push_back(&list, dir_ent);
    printer.printer_link(list, printer.delim);
    mx_dirent_del(&dir_ent);
    mx_list_delete(list);
}

static void run_printer(t_printer printer, t_list *dirs) {
    int len = mx_list_size(dirs);
    if (len <= 1) {
        t_dir *dir = (t_dir *)dirs->data;
        if (MX_ISLNK(dir->i_stat.st_mode) && printer.printer_link != 0)
            print_dir_as_link(dir, printer);
        else
            printer.printer(dir->entities, printer.delim);
    }
    else if (printer.is_recursive == true)
        mx_print_dirs_recursive(dirs, printer.delim, printer.printer);
    else
        mx_print_dirs_long(dirs, printer.delim, printer.printer);
}

static void delete_dirs_list(t_list **dirs) {
    while (*dirs) {
        t_dir *dir = (t_dir *)((*dirs)->data);
        mx_dirdelete(&dir);
        mx_pop_front(dirs);
    }
}

static void reorganize_list(t_list **dirs) {
    t_dir *dir = mx_dirnew();
    t_list *entities = 0;

    t_list *work = *dirs;
    while (work) {
        t_dir *current_dir = (t_dir *)work->data;
        if (current_dir->entities) {
            t_dirent *first_ent = (t_dirent *)current_dir->entities->data;
            if (first_ent->file_lonely) {
                mx_push_back(&entities, first_ent);
                mx_pop_front(dirs);
            }
        }

        work = work->next;
    }

    dir->entities = entities;
    if (entities) {
        mx_push_front(dirs, dir);
        dir->name = mx_strdup("");
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

    reorganize_list(&result);

    return result;
}

void mx_run_algorithm(t_algorithm *algorithm) {
    if (algorithm->paths == 0)
        return;
    t_list *dirs = fetch_all(algorithm->paths, algorithm->fetcher);
    run_printer(algorithm->printer, dirs);
    delete_dirs_list(&dirs);
}
