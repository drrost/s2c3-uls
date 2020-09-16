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

static void fill_stat(const char *dirname, t_dirent *dirent) {
    struct stat i_stat;
    char *full_path = mx_add_path(dirname, dirent->name);
    lstat(full_path, &i_stat);
    mx_strdel(&full_path);
    dirent->file_stat = i_stat;
}

static t_list *read_dir(const char *dirname, t_filter filter) {
    t_list *work = 0;

    struct stat stat;
    lstat(dirname, &stat);
    if (S_ISDIR(stat.st_mode) == 0) {
        t_dirent *custom_dirent = mx_dirent_new(
            dirname, stat.st_mode);
        fill_stat("", custom_dirent);
        custom_dirent->path = mx_strdup(dirname);
        mx_push_back(&work, custom_dirent);
        return work;
    }

    DIR *dir = opendir(dirname);
    struct dirent *dir_ent = 0;
    while ((dir_ent = readdir(dir)))
        if (run_filters(filter, dir_ent)) {
            t_dirent *custom_dirent = mx_dirent_new(
                dir_ent->d_name, dir_ent->d_type);
            fill_stat(dirname, custom_dirent);
            custom_dirent->path = mx_strdup(dirname);
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
    if (comparator.reverse == false)
        return comparator.cmp(d1, d2);
    else
        return comparator.cmp(d2, d1);
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
