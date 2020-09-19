//
// Created by Karina Barinova on 10.09.2020.
//

#include <uls.h>

void mx_print_long_u(t_list *entities, const char *delim) {
    int files_count = mx_list_size(entities);
    int max_size = mx_get_maxsize(entities);
    int max_links = mx_get_maxlinks(entities);
    int max_owner = mx_get_maxowner(entities);
    int max_group = mx_get_maxgroup(entities);
    char *s = 0;

    mx_print_total(entities, files_count);
    while (entities) {
        t_dirent *custom_dirent = (t_dirent *)entities->data;
        struct stat i_stat = custom_dirent->file_stat;

        s = mx_get_permissions(i_stat.st_mode, custom_dirent->path, custom_dirent->name);
        mx_printstr(s);
        mx_strdel(&s);

        char *s = mx_itoa(i_stat.st_nlink);
        mx_print_space((max_links - mx_strlen(s)) + 1);
        mx_strdel(&s);

        mx_printint(i_stat.st_nlink);
        mx_printstr(" ");

        s = mx_get_owner(i_stat.st_uid);
        mx_printstr(s);
        mx_print_space_owner(max_owner, s);
        mx_strdel(&s);

        s = mx_get_group(i_stat.st_gid);
        mx_printstr(s);
        mx_print_space(max_group - mx_strlen(s));
        mx_printstr("  ");
        mx_strdel(&s);

        char *size_str = mx_get_size(i_stat);
        mx_print_space_size(max_size, size_str);
        mx_printstr(size_str);
        mx_printstr(" ");
        mx_strdel(&size_str);

        s = mx_get_time(i_stat);
        mx_printstr(s);
        mx_strdel(&s);

        mx_printstr(delim);
        mx_printstr(custom_dirent->name);
        mx_print_link(entities);
        mx_printstr("\n");
        entities = entities->next;
    }
}
