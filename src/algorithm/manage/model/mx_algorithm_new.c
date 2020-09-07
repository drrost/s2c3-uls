//
// Created by Rostyslav Druzhchenko on 07.09.2020.
//

#include <uls.h>
#include <stdlib.h>

t_algorithm *mx_algorithm_new() {
    t_algorithm *algorithm = (t_algorithm *)malloc(sizeof(t_algorithm));
    mx_memset(algorithm, 0, sizeof(t_algorithm));
    return algorithm;
}
