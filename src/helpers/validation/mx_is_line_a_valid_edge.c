//
// Created by Rostyslav Druzhchenko on 01.08.2020.
//

#include <stdbool.h>
#include <libmx.h>

static bool is_line_valid(
    int dash_count, int comma_count, int comma_first_idx,
    int dash_first_idx, char *line) {
    int len = mx_strlen(line);
    if (dash_count != 1)
        return false;
    if (comma_count != 1)
        return false;
    if (comma_first_idx - dash_first_idx <= 1)
        return false;
    if (dash_first_idx <= 0 || dash_first_idx > len - 3)
        return false;
    if (comma_first_idx > len - 2)
        return false;
    if (mx_strncmp(line, line + dash_first_idx + 1, dash_first_idx) == 0)
        return false;
    return true;
}

bool mx_is_line_a_valid_edge(char *line) {
    int dash_count = 0;
    int comma_count = 0;
    int dash_first_idx = -1;
    int comma_first_idx = -1;
    int len = mx_strlen(line);
    for (int i = 0; i < len; i++) {
        char ch = line[i];
        if (!(mx_isalpha(ch) || mx_isdigit(ch) || ch == '-' || ch == ','))
            return false;
        if (ch == '-') {
            dash_count++;
            if (dash_first_idx == -1)
                dash_first_idx = i;
        }
        else if (ch == ',') {
            comma_count++;
            if (comma_first_idx == -1)
                comma_first_idx = i;
        }
    }
    return is_line_valid(dash_count, comma_count, comma_first_idx,
                         dash_first_idx, line);
}
