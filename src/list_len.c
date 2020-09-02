#include <uls.h>

static int dirs_only_len(t_d_lst *p, int *len) {
    while (p != NULL) {
        if (p->dir != NULL)
            *len += 1;
        p = p->next;
    }
    return *len;
}

static int files_only_len(t_d_lst *p, int *len) {
    while (p != NULL) {
        if (p->file != NULL)
            *len += 1;
        p = p->next;
    }
    return *len;
}

static int full_len(t_d_lst *p, int *len) {
    while (p != NULL) {
        *len += 1;
        p = p->next;
    }
    return *len;
}

int mx_d_lst_len(t_d_lst **head, int mode) {
    t_d_lst *p = (*head);
    int len = 0;

    if (mode == 0)
        return full_len(p, &len);
    if (mode == 1)
        return files_only_len(p, &len);
    if (mode == 2)
        return dirs_only_len(p, &len);
    return 0;
}
