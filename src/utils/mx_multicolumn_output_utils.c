//
// Created by Karina Barinova on 09.09.2020.
//

#include <uls.h>

char *mx_find_index(t_list *entities, int index) {
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

void mx_count_spaces(t_list *entities, int max, int j, const char *delim) {
    int cur_len = mx_strlen(mx_find_index(entities, j));
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

int mx_get_maxlen(t_list *entities) {
    int max_len = 0;

    while (entities) {
        t_dirent *entity = (t_dirent *)entities->data;
        if (mx_strlen(entity->name) > max_len)
            max_len = mx_strlen(entity->name);
        entities = entities->next;
    }
    return max_len;
}

int mx_get_max_spaces(int longest) {
    int tmp;
    int spaces;

    tmp = longest - 8;
    if (tmp < 0) {
        spaces = 8 - longest;
        return spaces;
    }
    while (tmp >= 8)
        tmp -= 8;
    spaces = 8 - tmp;
    return spaces;
}

int mx_lines_count(int files_count, int longest) {
    int win_col = get_window_size();
    int count = 1;
    int space = mx_get_max_spaces(longest);
    int c_words;
    int add;

    if (files_count * (longest + space) >= win_col) {
        c_words = win_col / (longest + space);
        if (c_words == 0)
            c_words++;
        add = 0;
        if ((files_count % c_words) != 0)
            add++;
        count = (files_count / c_words) + add;
    }
    if (!files_count)
        count = 0;
    return count;
}
