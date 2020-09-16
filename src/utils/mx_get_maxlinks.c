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
        struct stat i_stat = custom_dirent->file_stat;
        l = mx_itoa(i_stat.st_nlink);
        if (max < mx_strlen(l))
            max = mx_strlen(l);
        free(l);
    }
    return max;
}
