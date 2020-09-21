//
// Created by Karina Barinova on 16.09.2020.
//

#include <uls.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/acl.h>

int mx_int_length(long long n) {
    int i = 1;

    for (; n > 9; i++)
        n /= 10;
    return i;
}

void mx_print_at(char *str, char *fname, const char *path) {
    char *my_path = get_path(path, fname);
    char value[1024];
    size_t size_attr = 0;
    int len = 24;
    int diff1 = 0;
    int diff2 = 0;

    if (str[10] == '@') {
        if (listxattr(my_path, value, 1024, 1) >= 0)
            size_attr = getxattr(my_path, value, 0, 1024, 0, 1);
        mx_printstr("\n");
        mx_print_space(8);
        diff1 = len - mx_strlen(value);
        mx_printstr(value);
        len = 3;
        diff2 = len - mx_int_length(size_attr);
        mx_print_space(diff1 + 1);
        mx_print_space(diff2);
        mx_printint(size_attr);
    }
    mx_strdel(&my_path);
}

void mx_print_long_at(t_list *entities, const char *delim) {
    int files_count = mx_list_size(entities);
    int max_size = mx_get_maxsize(entities);
    int max_links = mx_get_maxlinks(entities);
    int max_owner = mx_get_maxowner(entities);
    int max_group = mx_get_maxgroup(entities);

    mx_print_total(entities, files_count);
    while (entities) {
        t_dirent *custom_dirent = (t_dirent *)entities->data;

        char *perms = mx_get_permissions(custom_dirent->file_stat.st_mode,
                                         custom_dirent->path,
                                         custom_dirent->name);
        mx_printstr(perms);

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
        //mx_printstr("\n");
        mx_print_at(perms, custom_dirent->name, custom_dirent->path);
        mx_printstr("\n");
        mx_strdel(&perms);
        entities = entities->next;
    }
}
