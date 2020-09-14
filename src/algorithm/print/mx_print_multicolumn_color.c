//
// Created by Karina Barinova on 09.09.2020.
//

#include <uls.h>
#include <sys/ioctl.h>
#include <unistd.h>

static int get_files_line(int max) {
    struct winsize w;
    int size_terminal = 80;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    if (!w.ws_col)
        return  size_terminal / max;
    return w.ws_col / max;
}

static int get_rows(int size, int files_line) {
    int rows = size / files_line;

    if (size % files_line)
        rows++;
    return rows;
}

void mx_print_multicolumn_color(t_list *entities, const char *delim) {
    int longest = mx_get_maxlen(entities);
    int size = mx_list_size(entities);
    int files_line = get_files_line(longest + 1);
    int rows = get_rows(size, files_line);
    struct stat buf;
    int len_str = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j + i < size; j+= rows) {
            lstat(mx_find_index(entities, (j + i)), &buf);
            mx_color_set(mx_acl_strcol(mx_get_permissions(buf.st_mode)),
            mx_acl_bkcol(mx_get_permissions(buf.st_mode)));
            mx_printstr(mx_find_index(entities, (j + i)));
            mx_color_reset();
            len_str = mx_strlen(mx_find_index(entities, (j + i)));
            if (j + rows + i < size)
                mx_print_space((longest + 1) - len_str);
        }
        mx_printstr(delim);
    }
}
