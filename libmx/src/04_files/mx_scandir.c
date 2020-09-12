//
// Created by Rostyslav Druzhchenko on 29.08.2020.
//

#include <libmx.h>
#include <sys/stat.h>

static int run_filters(t_filter filter, struct dirent *dir_ent) {
    for (int i = 0; filter.filters[i]; i++) {
        int (*a_filter) (const struct dirent *) = filter.filters[i];
        if (a_filter(dir_ent) == 0)
            return 0;
    }
    return 1;
}

static t_list *read_dir(const char *dirname, t_filter filter) {
    DIR *dir = opendir(dirname);
    t_list *work = 0;
    struct dirent *dir_ent = 0;
    while ((dir_ent = readdir(dir)))
        if (run_filters(filter, dir_ent)) {
            t_dirent *custom_dirent = mx_dirent_new(
                dir_ent->d_name, dir_ent->d_type);

            struct stat i_stat;
            lstat(custom_dirent->name, &i_stat);
            custom_dirent->mod_time = i_stat.st_mtimespec.tv_nsec;
            custom_dirent->acc_time = i_stat.st_atimespec.tv_nsec;
            custom_dirent->change_time = i_stat.st_ctimespec.tv_nsec;

            mx_push_back(&work, custom_dirent);
        }
    closedir(dir);
    return work;
}

static void swap_dirent(t_list *d1, t_list *d2) {
    void *temp = d1->data;
    d1->data = d2->data;
    d2->data = temp;
}

static int run_comparator(t_comparator comparator,
                          t_dirent *d1, t_dirent *d2) {
    if (comparator.reverse == false) {
        return comparator.cmp(d1, d2);
    }
    else {
        return comparator.cmp(d2, d1);
    }
}

static void sort_dirents(t_list *dirs, t_comparator comparator) {
    t_list *work_i = dirs;
    while (work_i) {
        t_list *work_j = work_i;
        while (work_j) {
            if (run_comparator(
                comparator,
                (t_dirent *)work_i->data,
                (t_dirent *)work_j->data) > 0) {
                swap_dirent(work_i, work_j);
            }
            work_j = work_j->next;
        }
        work_i = work_i->next;
    }
}

int mx_scandir(const char *dirname, t_list **dirs,
               t_filter filter, t_comparator comparator) {
    t_list *dir_content = read_dir(dirname, filter);
    sort_dirents(dir_content, comparator);

    t_dir *result = mx_dirnew();
    result->entities = dir_content;
    result->name = mx_strdup(dirname);
    mx_push_back(dirs, result);

    return 0;
}
