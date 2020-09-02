#include <uls.h>

static void dirs_read(t_uls *uls, t_d_lst **head) {
    t_d_lst *p = (*head);
    int i = 0;

    while (p != NULL) {
        if (p->dir != NULL) {
            uls->dirs[i] = p->dir;
            i++;
        }
        p = p->next;
    }
}

static void files_read(t_uls *uls, t_d_lst **head) {
    t_d_lst *p = (*head);
    int i = 0;

    while (p != NULL) {
        if (p->file != NULL) {
            uls->files[i] = p->file;
            i++;
        }
        p = p->next;
    }
}

static void delete_lst(t_d_lst **head) {
    while ((*head) != NULL)
        mx_pop_data_front(head);
    head = NULL;
}

void mx_lst_to_arr(t_uls *uls, t_d_lst **head) {
    unsigned int f_len = mx_d_lst_len(head, 1);
    unsigned int d_len = mx_d_lst_len(head, 2);

    if (f_len > 0) {
        uls->files_count = f_len;
        uls->files = mx_create_files_array(f_len);
        files_read(uls, head);
    }
    if (d_len > 0) {
        uls->dirs_count = d_len;
        uls->dirs = mx_create_dirs_array(d_len);
        dirs_read(uls, head);
    }
    delete_lst(head);
}
