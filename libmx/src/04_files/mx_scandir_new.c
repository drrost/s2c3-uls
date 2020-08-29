//
// Created by Rostyslav Druzhchenko on 29.08.2020.
//

#include <libmx.h>

static void swap_dirent(t_list *d1, t_list *d2) {
    void *temp = d1->data;
    d1->data = d2->data;
    d2->data = temp;
}

int
mx_scandir_new(const char *dirname, t_list **dirs,
               int (*select)(const struct dirent *),
               int (*compar)(const struct dirent **, const struct dirent **)) {
    // Open dir
    DIR *dir = opendir(dirname);

    t_list *work = 0;
    // Read dir's content
    struct dirent *dirent = 0;
    while ((dirent = readdir(dir))) {
        if (select(dirent)) {
            mx_push_back(&work, dirent);
        }
    }

    // Sort
    t_list *work_i = work;
    while (work_i) {
        t_list *work_j = work_i;
        while (work_j) {
            if (compar((const struct dirent **)&(work_i),
                       (const struct dirent **)&(work_j)) > 0) {
                swap_dirent(work_i, work_j);
            }
            work_j = work_j->next;
        }
        work_i = work_i->next;
    }

    // Close dir
    closedir(dir);

    *dirs = work;

    return 0;
}
