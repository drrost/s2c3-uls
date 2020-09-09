//
// Created by Rostyslav Druzhchenko on 09.09.2020.
//

#include <uls.h>
#include <stdlib.h>

void mx_flags_delete(t_flags **flags) {
    free(*flags);
}
