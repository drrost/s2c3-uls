//
// Created by Rostyslav Druzhchenko on 29.08.2020.
//

#include <uls.h>

void mx_print_dirent_simple(t_list *dirs, char *delim) {
    while (dirs) {
        t_list *entities = ((t_dir *)dirs->data)->entities;
        while (entities) {
            struct dirent *entity = (struct dirent *)entities->data;
            mx_printstr(entity->d_name);
            if (entities->next != 0)
                mx_printstr(delim);
            entities = entities->next;
        }
        dirs = dirs->next;
    }
    mx_printstr("\n");
}
