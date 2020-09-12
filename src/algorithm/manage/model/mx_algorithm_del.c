//
// Created by Rostyslav Druzhchenko on 07.09.2020.
//

#include <uls.h>

void mx_algorithm_del(t_algorithm **algorithm) {
    t_list *work = (*algorithm)->paths;
    while (work) {
        char *s = (char *)work->data;
        mx_strdel(&s);
        mx_pop_front(&work);
    }
}
