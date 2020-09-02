#include <uls.h>
#include <stdlib.h>

t_d_lst *mx_create_data_node(t_file *file, t_dir *dir) {
    t_d_lst *node = (t_d_lst *)malloc(sizeof(t_d_lst));

    node->file = file;
    node->dir = dir;
    node->next = NULL;
    return node;
}
