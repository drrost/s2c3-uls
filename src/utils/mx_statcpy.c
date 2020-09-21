//
// Created by Rostyslav Druzhchenko on 21.09.2020.
//

#include <uls.h>

void mx_statcpy(struct stat *dst, struct stat *src) {
    mx_memcpy(dst, src, sizeof(struct stat));
}
