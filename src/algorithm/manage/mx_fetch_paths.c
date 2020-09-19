//
// Created by Rostyslav Druzhchenko on 19.09.2020.
//

#include <uls.h>
#include <stdlib.h>

static bool alphasort_local(void *s1, void *s2) {
    return mx_strcmp(s1, s2) > 0;
}

static bool files_first(void *s1, void *s2) {
    char *s_1 = (char *)s1;
    char *s_2 = (char *)s2;

    struct stat stat_1;
    struct stat stat_2;

    lstat(s_1, &stat_1);
    lstat(s_2, &stat_2);

    if ((S_ISDIR(stat_1.st_mode) == 0 && S_ISDIR(stat_2.st_mode) == 0) ||
        (S_ISREG(stat_1.st_mode) == 0 && S_ISREG(stat_2.st_mode) == 0))
        return mx_strcmp(s1, s2) > 0;
    else
        return true;
}

static bool is_exists(char *path) {
    struct stat stat;
    int result = lstat(path, &stat);
    return result == 0;
}

static void delete_node(t_list **node) {
    char *s = (char *)(*node)->data;
    mx_strdel(&s);
    free(*node);
    *node = 0;
}

static void check_existance(t_list **list) {
    t_list *work = *list;
    while (work) {
        char *path = (char *)work->data;
        if (is_exists(path) == false) {
            mx_print_error_no_such_file((char *)work->data);
            mx_list_remove(list, work, delete_node);
        }
        work = work->next;
    }
}

t_list *mx_fetch_paths(int start_idx, int argc, char *argv[]) {
    t_list *result = 0;
    if (start_idx == argc) {
        mx_push_back(&result, mx_strdup("."));
        return result;
    }

    for (int i = start_idx; i < argc; i++)
        mx_push_back(&result, mx_strdup(argv[i]));
    mx_sort_list(result, alphasort_local);

    check_existance(&result);
    mx_sort_list(result, files_first);

    return result;
}
