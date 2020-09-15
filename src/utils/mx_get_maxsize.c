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

    for (; entities != NULL; entities = entities->next) {
        t_dirent *custom_dirent = (t_dirent *)entities->data;
        struct stat i_stat = custom_dirent->file_stat;
        int len = get_size(&i_stat);
        if (max < len) {
            char *s = mx_get_size(i_stat);
            if (mx_get_char_index(s, ',') > 0) {
                if (max <= 8)
                    max = 8;
            }
            else {
                max = len;
            }
            mx_strdel(&s);
        }
    }
    return max;
}

void mx_print_space(int n) {
    for (int i = 0; i < n; i++)
        mx_printstr(" ");
}
