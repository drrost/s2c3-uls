//
// Created by Rostyslav Druzhchenko on 02.08.2020.
//

#pragma once

// ====================================================================
// Vertex
//
// Vertex owns its data
//
typedef struct s_vertex {
    char *name;
    bool is_visited;
    struct s_vertex *parent;
}              t_vertex;

t_vertex *mx_create_vertex(char *name);
void mx_delete_vertex(t_vertex **vertex);

void mx_delete_vertices(t_list *vertices);

// ====================================================================
// Edge
//
// Edge doesn't own vertices
//
typedef struct s_edge {
    t_vertex *vertex_0_w;
    t_vertex *vertex_1_w;
    int weight;
}              t_edge;

t_edge *mx_create_edge(t_vertex *vertex_0, t_vertex *vertex_1, int weight);
void mx_delete_edge(t_edge **edge);
void mx_delete_edges(t_list *edges);

// ====================================================================
// Path
//
// Path owns its data
//
typedef struct s_path {
    t_list *path; // vertices, doesn't own vertices
    int length;
    char *str_route;
}              t_path;

t_path *mx_create_path();
void mx_delete_path(t_path **path);
void mx_calculate_path_length(t_path *path, t_list *edges);

// ====================================================================
// Graph
//
// Graph owns its data
typedef struct s_graph {
    t_list *vertices;
    t_list *edges;
    int n;
}              t_graph;

t_graph *mx_create_graph(void);
void mx_delete_graph(t_graph **graph);
t_edge *mx_parse_to_edge(t_graph *graph, char *data);
t_graph *mx_graphdup(t_graph *graph);
void mx_print_graph(t_graph *graph);
