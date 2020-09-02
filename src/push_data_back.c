#include <uls.h>

void mx_push_data_back(t_d_lst **head, t_file *file, t_dir *dir) {
    t_d_lst *new_node = mx_create_data_node(file, dir);
    t_d_lst *p = (*head);

    if (p == NULL)
        (*head) = new_node;
    else {
        while (p->next != NULL)
            p = p->next;
        p->next = new_node;
    }
}
