#include <uls.h>

void mx_pop_data_front(t_d_lst **head) {
    t_d_lst *p = NULL;

    if ((*head != NULL) && (head != NULL)) {
        p = (*head)->next;
        free(*head);
        (*head) = p;
    }
}
