//
// Created by Karina Barinova on 09.09.2020.
//

#include <uls.h>


#include <sys/ioctl.h>
#include <unistd.h>

char *mx_find_index_all(t_list *entities, int index) {
    t_dirent *entity = NULL;
    int i = 0;

    while (entities != 0) {
        entity = (t_dirent *)entities->data;
        if (i == index) {
            return entity->name;
        }
        i++;
        entities = entities->next;
    }

    return entity->name;
} 

void mx_count_spaces_all(t_list *entities, int max, int j, const char *delim) {
    int cur_len = mx_strlen(mx_find_index_all(entities, j));
    int add = 8;

    if (cur_len < 8) {
        mx_printstr(delim);
        cur_len = 8;
    }
    while (cur_len <= max) {
        mx_printstr(delim);
        while (add <= cur_len)
            add += 8;
        cur_len = add;
    }
}

int mx_get_maxlen_all(t_list *entities) {
    int max_len = 0;

    while (entities->next != 0) {
        t_dirent *entity = (t_dirent *)entities->data;

        if (mx_strlen(entity->name) > max_len)
            max_len = mx_strlen(entity->name);
        entities = entities->next;
    }
    return max_len;
}
