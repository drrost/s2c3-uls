//
// Created by Karina Barinova on 10.09.2020.
//

#include <uls.h>

void mx_print_space_size(int max, const char *size) {
    if ((max - mx_strlen(size)) <= 0)
        mx_printstr("  ");
    else
        mx_print_space(((++max) - mx_strlen(size)) + 1);
}

void mx_print_total(t_list *entities, int files_count) {
    mx_printstr("total ");
    mx_printstr(mx_itoa(mx_find_blocks(entities, files_count)));
    mx_printstr("\n");
}

static void do_print(t_list *entities, const char *delim) {
    struct stat buf;
    int files_count = mx_list_size(entities);
    int max_size = mx_get_maxsize(entities);
    int max_links = mx_get_maxlinks(entities);

    mx_print_total(entities, files_count);
    for (int i = 0; i < files_count; i++) {
        lstat(mx_find_index(entities, i), &buf);
        mx_printstr(mx_get_permissions(buf.st_mode));
        mx_print_space((max_links - mx_strlen(mx_itoa(buf.st_nlink))) + 2);
        mx_printint(buf.st_nlink);
        mx_printstr(" ");
        mx_printstr(mx_get_owner(buf.st_uid));
        mx_printstr(delim);
        mx_printstr(mx_get_group(buf.st_gid));
        mx_print_space_size(max_size, mx_get_size(buf));
        mx_printstr(mx_get_size(buf));
        mx_printstr(" ");
        mx_printstr(mx_get_time(buf));
        mx_printstr(" ");
        mx_printstr(mx_find_index(entities, i));
        mx_printstr("\n");
    }
}

void mx_print_long(t_list *dirs, const char *delim) {
    mx_print_dirs(dirs, delim, do_print);
}
