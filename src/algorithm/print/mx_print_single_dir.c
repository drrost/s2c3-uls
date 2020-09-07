//
// Created by Rostyslav Druzhchenko on 05.09.2020.
//

#include <uls.h>

void mx_print_single_dir(t_list *dirs, const char *delim) {
    t_dir *dir = (t_dir *)dirs->data;
    mx_print_dir_content(dir->entities, delim);
    mx_printstr("\n");
}
