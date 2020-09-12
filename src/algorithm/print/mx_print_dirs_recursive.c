//
// Created by Rostyslav Druzhchenko on 07.09.2020.
//

#include <uls.h>

void mx_print_dirs_recursive(t_list *dirs, const char *delim,
                             PRINTER(printer)) {
    int count = 0;

    while (dirs) {
        t_dir *dir = (t_dir*)dirs->data;
        if (count != 0) {
            mx_printstr(dir->name);
            mx_printstr(":\n");
        }

        t_list *entities = (t_list *)dir->entities;
        printer(entities, delim);
        if (entities && dirs->next) {
            mx_printstr("\n\n");
        } else {
            mx_printstr("\n");
        }

        dirs = dirs->next;
        count++;
    }
}
