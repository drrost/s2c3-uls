//
// Created by Rostyslav Druzhchenko on 11.09.2020.
//

#include <libmx.h>

int mx_timesort(t_dirent *d1, t_dirent *d2) {
    return d1->m_time < d2->m_time;
}
