//
// Created by Karina Barinova on 10.09.2020.
//

#include <uls.h>

int mx_get_maxsize(t_list *entities) {
    int max = 0;
    int i = 0;
    struct stat buf;

    for (; entities != NULL; entities = entities->next) {
        lstat(mx_find_index(entities, i), &buf);
        i++;
        if (max < mx_strlen(mx_get_size(buf))) {
            if (mx_get_char_index(mx_get_size(buf), ',') > 0) {
                if (max <= 8)
                    max = 8;
            }
            else {
                max = mx_strlen(mx_get_size(buf));
            }
        }
    }
    return max;
}

void mx_print_space(int n) {
    for (int i = 0; i < n; i++)
        mx_printstr(" ");
}
