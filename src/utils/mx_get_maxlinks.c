//
// Created by Karina Barinova on 09.09.2020.
//

#include <uls.h>
#include <stdlib.h>

int mx_get_maxlinks(t_list *entities) {
    int max = 0;
    int i = 0;
    char *l = NULL;
    struct stat buf;

    for (; entities != NULL; entities = entities->next) {
        lstat(mx_find_index(entities, i), &buf);
        i++;
        l = mx_itoa(buf.st_nlink);
        if (max < mx_strlen(l))
            max = mx_strlen(l);
        free(l);
    }
    return max;
}
