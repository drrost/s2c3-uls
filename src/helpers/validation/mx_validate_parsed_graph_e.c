//
// Created by Rostyslav Druzhchenko on 02.08.2020.
//

#include "pathfinder.h"

void mx_validate_parsed_graph_e(t_graph *graph) {
    int list_size = mx_list_size(graph->vertices);
    if (list_size != graph->n) {
        mx_delete_graph(&graph);
        mx_print_error_exit(ERROR_INVALID_NUMBER_OF_ISLANDS, "");
    }

    if (!mx_validate_bridges_sum(graph)) {
        mx_delete_graph(&graph);
        mx_print_error_exit(ERROR_SUM_OF_BRIDGES_TOO_BIG, "");
    }
}
