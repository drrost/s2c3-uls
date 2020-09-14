//
// Created by Karina Barinova on 10.09.2020.
//

#include <uls.h>

static int get_size(struct stat *buf) {
    char *size_str = mx_get_size(*buf);
    int len = mx_strlen(size_str);
    mx_strdel(&size_str);
    return len;
}

int mx_get_maxsize(t_list *entities) {
    int max = 0;
    int i = 0;
    struct stat buf;

    for (; entities != NULL; entities = entities->next) {
        lstat(mx_find_index(entities, i), &buf);
        i++;
        int len = get_size(&buf);
        if (max < len) {
            if (mx_get_char_index(mx_get_size(buf), ',') > 0) {
                if (max <= 8)
                    max = 8;
            }
            else {
                max = len;
            }
        }
    }
    return max;
}

void mx_print_space(int n) {
    for (int i = 0; i < n; i++)
        mx_printstr(" ");
}
