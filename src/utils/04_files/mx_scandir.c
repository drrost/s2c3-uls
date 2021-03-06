//
// Created by Rostyslav Druzhchenko on 29.08.2020.
//

#include <uls.h>

static int run_filters(t_filter filter, struct dirent *dir_ent) {
    for (int i = 0; filter.filters[i]; i++) {
        int (*a_filter)(const struct dirent *) = filter.filters[i];
        if (a_filter(dir_ent) == 0)
            return 0;
    }
    return 1;
}

static void fill_stat(const char *dir_name, t_dirent *dir_ent) {
    struct stat i_stat;
    char *full_path = mx_add_path(dir_name, dir_ent->name);
    lstat(full_path, &i_stat);
    mx_strdel(&full_path);
    mx_statcpy(&(dir_ent->file_stat), &i_stat);
}

static int read_dir(const char *dirname, t_filter filter, t_list **result) {
    struct stat stat;
    int error_code = 0;
    lstat(dirname, &stat);

    // Handle as a file
    if (MX_ISDIR(stat.st_mode) == 0 && MX_ISLNK(stat.st_mode) == 0) {
        t_dirent *custom_dirent = mx_dirent_new(dirname, stat.st_mode);
        mx_statcpy(&(custom_dirent->file_stat), &stat);
        custom_dirent->path = mx_strdup(".");
        custom_dirent->file_lonely = true;
        mx_push_back(result, custom_dirent);
        return error_code;
    }

    // Handle as a directory
    DIR *dir = opendir(dirname);
    if (dir == 0)
        error_code = ERROR_PERMISSION_DENIED;
    else {
        struct dirent *dir_ent = 0;
        while ((dir_ent = readdir(dir)))
            if (run_filters(filter, dir_ent)) {
                t_dirent *custom_dirent = mx_dirent_new(
                    dir_ent->d_name, dir_ent->d_type);
                fill_stat(dirname, custom_dirent);
                custom_dirent->path = mx_strdup(dirname);
                mx_push_back(result, custom_dirent);
            }
        closedir(dir);
    }

    return error_code;
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

static void mark_skipped(t_list *dir_content) {
    while (dir_content) {
        t_dirent *dirent = (t_dirent *)dir_content->data;
        if (mx_strcmp(dirent->name, ".") == 0 ||
            mx_strcmp(dirent->name, "..") == 0) {
            dirent->skip_on_recurse = true;
        }
        dir_content = dir_content->next;
    }
}

int mx_scandir(const char *dirname, t_list **dirs,
               t_filter filter, t_comparator comparator) {
    t_list *dir_content = 0;
    int code = read_dir(dirname, filter, &dir_content);
    sort_dirents(dir_content, comparator);
    mark_skipped(dir_content);

    t_dir *result = mx_dirnew();
    result->error_code = code;
    lstat(dirname, &(result->i_stat));
    result->entities = dir_content;
    result->name = mx_strdup(dirname);
    mx_push_back(dirs, result);

    return 0;
}
