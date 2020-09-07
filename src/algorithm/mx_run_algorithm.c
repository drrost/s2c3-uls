//
// Created by Rostyslav Druzhchenko on 07.09.2020.
//

#include <uls.h>

void mx_run_algorithm(t_algorithm *algorithm) {
    char *path = (char *)algorithm->paths->data;
    t_list *dirs = algorithm->fetcher(path);

    t_dir *dir = (t_dir *)dirs->data;
    algorithm->printer(dir->entities, algorithm->delim);
    mx_printline("");

    // TODO: Move to a separate method
    while (dirs) {
        t_dir *dir = (t_dir *)dirs->data;
        mx_dirdelete(&dir);
        dirs = dirs->next;
    }
}
