//
// Created by Rostyslav Druzhchenko on 29.07.2020.
//

#pragma once

#include <stdbool.h>
#include <libmx.h>

#include "graphmx.h"

// README.md
//
// `_e' suffix in functions name means that function may exit in a case
// of error.
//
// `_w' suffix in structs' *fields* mean that the field is "weak", so
// the struct does not own data obtained in this field. In all other
// cases means that the struct owns a field and *MUST* call free()
// function for this field in an appropriate place (mx_delete_xxx).
//

// Errors

enum e_error {
    ERROR_WRONG_PARAM_NUMBER,
    ERROR_FILE_NOT_FOUND,
    ERROR_FILE_IS_EMPTY,
    ERROR_LINE_NOT_VALID,
    ERROR_INVALID_NUMBER_OF_ISLANDS,
    ERROR_DUPLICATE_BRIDGES,
    ERROR_SUM_OF_BRIDGES_TOO_BIG,
    ERROR_NOT_ENOUGH_MEMORY
};

void mx_printerr(const char *s);
void mx_print_error_exit(enum e_error error, char *message);

// Helpers

int mx_atoi_positive_only(const char *str);
bool mx_is_line_a_valid_edge(char *line);
t_graph *mx_read_graph_e(char *file_name);
bool mx_validate_bridges_sum(t_graph *graph);
void mx_validate_parsed_graph_e(t_graph *graph);

void mx_print_paths(t_list *paths, t_list *edges);
void mx_delete_paths_list(t_list **paths);

// Algorithm

t_list *mx_find_all_shortest_paths(t_graph *graph);
void mx_all_paths_from_to(
    t_vertex *src, t_vertex *dst, t_graph *graph, t_list **all_paths);
t_path *mx_compose_path(t_vertex *last_vertex);
int mx_distance_between(t_vertex *vertex_0, t_vertex *vertex_1, t_list *edges);
