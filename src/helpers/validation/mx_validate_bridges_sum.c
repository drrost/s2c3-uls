//
// Created by Rostyslav Druzhchenko on 01.08.2020.
//

#include <stdbool.h>
#include "pathfinder.h"

static int add_overflow(int *result, int x, int y) {
    *result = x + y;
    if (*result > 0 && x < 0 && y < 0)
        return -1;
    if (*result < 0 && x > 0 && y > 0)
        return -1;
    return 0;
}

bool mx_validate_bridges_sum(t_graph *graph) {
    int overflowed = 0;
    t_list *work = graph->edges;
    while (work) {
        int f = add_overflow(
            &overflowed, overflowed, ((t_edge *)work->data)->weight);
        if (f == -1) {
            return false;
        }
        work = work->next;
    }
    return true;
}
