//
// Created by Rostyslav Druzhchenko on 11.09.2020.
//

#include <uls.h>

void mx_print_dirs(t_list *dirs, const char *delim, PRINTER(printer)) {
    while (dirs) {
        t_dir *dir = (t_dir *)dirs->data;
        printer(dir->entities, delim);
        dirs = dirs->next;
    }
}
