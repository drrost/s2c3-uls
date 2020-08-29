//
// Created by Rostyslav Druzhchenko on 29.08.2020.
//

#include <libmx.h>

static void swap_dirent(t_list *d1, t_list *d2) {
    void *temp = d1->data;
    d1->data = d2->data;
    d2->data = temp;
}

static void
sort_dirs(t_list *dirs,
          int (*compar)(const struct dirent **, const struct dirent **)) {
    t_list *work_i = dirs;
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
}

static t_list *read_dir(const char *dirname,
                        int (*select)(const struct dirent *)) {
    DIR *dir = opendir(dirname);
    t_list *work = 0;
    struct dirent *dirent = 0;
    while ((dirent = readdir(dir))) {
        if (select(dirent)) {
            mx_push_back(&work, dirent);
        }
    }
    closedir(dir);
    return work;
}

int
mx_scandir(const char *dirname,
           t_list **dirs,
           int (*select)(const struct dirent *),
           int (*compar)(const struct dirent **, const struct dirent **)) {
    t_list *dir_content = read_dir(dirname, select);
    sort_dirs(dir_content, compar);

    t_dir *result = mx_dirnew();
    result->entities = dir_content;
    mx_push_back(dirs, result);

    return 0;
}
