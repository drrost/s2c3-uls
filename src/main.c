//
// Created by Rostyslav Druzhchenko on 29.07.2020.
//

#include "pathfinder.h"

static void validate_arguments_e(int argc) {
    if (argc != 2)
        mx_print_error_exit(ERROR_WRONG_PARAM_NUMBER, "");
}

int main(int argc, char *argv[]) {
    t_graph *graph = 0;

    validate_arguments_e(argc);
    graph = mx_read_graph_e(argv[1]);

    t_list *paths = mx_find_all_shortest_paths(graph);
    mx_print_paths(paths, graph->edges);

    mx_delete_paths_list(&paths);
    mx_delete_graph(&graph);

    return 0;
}
