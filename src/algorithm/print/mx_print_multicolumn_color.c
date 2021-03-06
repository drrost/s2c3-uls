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
        return size_terminal / max;
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
    t_dirent *custom_dirent = (t_dirent *)entities->data;
    struct stat buf;
    int len_str = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < size; j++) {
            if (j == i || (j - i) % rows == 0) {
                char *my_path = get_path(custom_dirent->path,
                                         mx_find_index(entities, j));
                lstat(my_path, &buf);
                char *perms = mx_get_permissions(buf.st_mode,
                                                 custom_dirent->path,
                                                 mx_find_index(entities, j));
                mx_color_set(mx_acl_strcol(perms),
                             mx_acl_bkcol(perms));
                mx_printstr(mx_find_index(entities, j));
                mx_color_reset();
                len_str = mx_strlen(mx_find_index(entities, j));
                if (j + rows < size)
                    mx_print_space((longest + 1) - len_str);
                mx_strdel(&perms);
                mx_strdel(&my_path);
            }
        }
        mx_printstr(delim);
    }
}
