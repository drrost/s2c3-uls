//
// Created by Karina Barinova on 10.09.2020.
//

#include <uls.h>

void mx_print_dirs_long(t_list *dirs, const char *delim, PRINTER(printer)) {
    while (dirs) {
        t_dir *dir = (t_dir *)dirs->data;
        if (!MX_ISREG(dir->i_stat.st_mode) && mx_strlen(dir->name) > 0) {
            mx_printstr(dir->name);
            mx_printstr(":\n");
        }

        if (dir->error_code != ERROR_PERMISSION_DENIED) {
            t_list *entities = (t_list *)dir->entities;
            if (entities)
                printer(entities, delim);
            if (dirs->next)
                mx_printstr("\n");
        }
        else {
            mx_print_error_permission_denied(dir->name);
            if (dirs->next) {
                mx_printstr("\n");
            }
        }

        dirs = dirs->next;
    }
}

void mx_print_long(t_list *entities, const char *delim) {
    int files_count = mx_list_size(entities);
    int max_size = mx_get_maxsize(entities);
    int max_links = mx_get_maxlinks(entities);
    int max_owner = mx_get_maxowner(entities);
    int max_group = mx_get_maxgroup(entities);
    char *s = 0;

    t_dirent *custom_dirent = (t_dirent *)entities->data;
    if (!MX_ISCHR(custom_dirent->file_stat.st_mode) && !MX_ISREG(custom_dirent->file_stat.st_mode)) {
        mx_print_total(entities, files_count);
    }

    while (entities) {
        t_dirent *custom_dirent = (t_dirent *)entities->data;

        s = mx_get_permissions(custom_dirent->file_stat.st_mode,
                               custom_dirent->path,
                               custom_dirent->name);
        mx_printstr(s);
        mx_strdel(&s);

        char *s = mx_itoa(custom_dirent->file_stat.st_nlink);
        mx_print_space((max_links - mx_strlen(s)) + 1);
        mx_strdel(&s);

        mx_printint(custom_dirent->file_stat.st_nlink);
        mx_printstr(" ");

        s = mx_get_owner(custom_dirent->file_stat.st_uid);
        mx_printstr(s);
        mx_print_space_owner(max_owner, s);
        mx_strdel(&s);

        s = mx_get_group(custom_dirent->file_stat.st_gid);
        mx_printstr(s);
        mx_print_space(max_group - mx_strlen(s));
        mx_printstr("  ");
        mx_strdel(&s);

        char *size_str = mx_get_size(custom_dirent->file_stat);
        mx_print_space_size(max_size, size_str);
        mx_printstr(size_str);
        mx_printstr(" ");
        mx_strdel(&size_str);

        s = mx_get_time(custom_dirent->file_stat);
        mx_printstr(s);
        mx_strdel(&s);

        mx_printstr(delim);
        mx_printstr(custom_dirent->name);
        mx_print_link(entities);
        mx_printstr("\n");
        entities = entities->next;
    }
}
