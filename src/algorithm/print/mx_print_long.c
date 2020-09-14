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
    //int max_owner = mx_get_maxowner(entities);
    //int max_group = mx_get_maxgroup(entities);

    mx_print_total(entities, files_count);
    int i = 0;
    while (entities) {
        t_dirent *custom_dirent = (t_dirent *)entities->data;
        struct stat buf = custom_dirent->file_stat;

        mx_printstr(mx_get_permissions(buf.st_mode));
        mx_print_space((max_links - mx_strlen(mx_itoa(buf.st_nlink))) + 2);
        mx_printint(buf.st_nlink);
        mx_printstr(" ");
        //mx_print_spaceown(max_owner, mx_get_owner(buf.st_uid));
        mx_printstr(mx_get_owner(buf.st_uid));
        mx_printstr(delim);
        mx_printstr(mx_get_group(buf.st_gid));

        char *size_str = mx_get_size(buf);
        mx_print_space_size(max_size, size_str);
        mx_printstr(size_str);
        mx_strdel(&size_str);

        mx_printstr(" ");
        mx_printstr(mx_get_time(buf));
        mx_printstr(" ");
        mx_printstr(custom_dirent->name);
        mx_printstr("\n");
        i++;
        entities = entities->next;
    }
}
