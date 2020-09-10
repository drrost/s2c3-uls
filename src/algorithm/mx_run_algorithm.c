//
// Created by Rostyslav Druzhchenko on 07.09.2020.
//

#include <uls.h>

static t_list *run_fetcher(const char *path, t_fetcher fetcher) {
    return fetcher.fetch(path, fetcher.filter, fetcher.comparator);
}

void mx_run_algorithm(t_algorithm *algorithm) {
    char *path = (char *)algorithm->paths->data;
    t_list *dirs = run_fetcher(path, algorithm->fetcher);

    algorithm->printer(dirs, algorithm->delim);

    // TODO: Move to a separate method
    while (dirs) {
        t_dir *dir = (t_dir *)dirs->data;
        mx_dirdelete(&dir);
        dirs = dirs->next;
    }
}
