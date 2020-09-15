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
    char *s = mx_itoa(mx_find_blocks(entities, files_count));
    mx_printstr(s);
    mx_strdel(&s);
    mx_printstr("\n");
}


// void mx_print_spaceown(int max, const char *owner) {
//     int sum = max - mx_strlen(owner);

//     if (sum == mx_strlen(owner))
//         mx_printstr("  ");
//     else
//         mx_print_space(sum);
//     mx_printstr("  ");
// }

// int mx_get_maxowner(t_list *entities) {
//     int max = 0;
//     struct stat buf;
//     int i = 0;

//     for (; entities != 0; entities = entities->next) {
//         lstat(mx_find_index(entities, i), &buf);
//         i++;
//         if (max < mx_strlen(mx_get_owner(buf.st_uid)))
//             max = mx_strlen(mx_get_owner(buf.st_uid));
//     }
//     return max;
// }

void mx_print_long(t_list *entities, const char *delim) {
    int files_count = mx_list_size(entities);
    int max_size = mx_get_maxsize(entities);
    int max_links = mx_get_maxlinks(entities);
    char *s = 0;
    //int max_owner = mx_get_maxowner(entities);
    //int max_group = mx_get_maxgroup(entities);

    mx_print_total(entities, files_count);
    while (entities) {
        t_dirent *custom_dirent = (t_dirent *)entities->data;
        struct stat i_stat = custom_dirent->file_stat;

        s = mx_get_permissions(i_stat.st_mode, custom_dirent->path, custom_dirent->name);
        mx_printstr(s);
        mx_strdel(&s);

        char *s = mx_itoa(i_stat.st_nlink);
        if (mx_strcmp(custom_dirent->path, "."))
            mx_print_space((max_links - mx_strlen(s)) + 2);
        else
            mx_print_space((max_links - mx_strlen(s)) + 1);
        mx_strdel(&s);

        mx_printint(i_stat.st_nlink);
        mx_printstr(" ");
        //mx_print_spaceown(max_owner, mx_get_owner(buf.st_uid));

        s = mx_get_owner(i_stat.st_uid);
        mx_printstr(s);
        mx_strdel(&s);

        mx_printstr(delim);

        s = mx_get_group(i_stat.st_gid);
        mx_printstr(s);
        mx_strdel(&s);

        char *size_str = mx_get_size(i_stat);
        mx_print_space_size(max_size, size_str);
        mx_printstr(size_str);
        mx_strdel(&size_str);

        mx_printstr(" ");

        s = mx_get_time(i_stat);
        mx_printstr(s);
        mx_strdel(&s);

        mx_printstr(" ");
        mx_printstr(custom_dirent->name);
        mx_printstr("\n");
        entities = entities->next;
    }
}
