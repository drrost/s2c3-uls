//
// Created by Karina Barinova on 09.09.2020.
//

#include <uls.h>
#include <stdlib.h>

int mx_get_maxlinks(t_list *entities) {
    int max = 0;
    char *l = NULL;

    for (; entities != NULL; entities = entities->next) {
        t_dirent *custom_dirent = (t_dirent *)entities->data;
        l = mx_itoa(custom_dirent->file_stat.st_nlink);
        if (max < mx_strlen(l))
            max = mx_strlen(l);
        free(l);
    }
    return max;
}

int mx_get_maxinode(t_list *entities) {
    int max = 0;
    char *l = NULL;

    for (; entities != NULL; entities = entities->next) {
        t_dirent *custom_dirent = (t_dirent *)entities->data;
        l = mx_itoa(custom_dirent->file_stat.st_ino);
        if (max < mx_strlen(l))
            max = mx_strlen(l);
        free(l);
    }
    return max;
}
