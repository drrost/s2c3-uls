//
// Created by Rostyslav Druzhchenko on 07.09.2020.
//

#include <uls.h>

void mx_print_dir_content(t_list *entities, const char *delim) {
    while (entities) {
        t_dirent *entity = (t_dirent *)entities->data;
        if (entity->name[0] != '.') {
        	mx_printstr(entity->name);
        }
        else {
        	entities = entities->next;
        	continue;
        }
        if (entities->next != 0)
            mx_printstr(delim);
        entities = entities->next;
    }
}
