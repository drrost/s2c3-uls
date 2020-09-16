//
// Created by Karina Barinova on 10.09.2020.
//

#include <uls.h>

void mx_print_space_size(int max, const char *size) {
    if ((max - mx_strlen(size)) < 0)
        mx_printstr(" ");
    mx_print_space(max - mx_strlen(size));
}

void mx_print_total(t_list *entities, int files_count) {
    mx_printstr("total ");
    char *s = mx_itoa(mx_find_blocks(entities, files_count));
    mx_printstr(s);
    mx_strdel(&s);
    mx_printstr("\n");
}


void mx_print_space_owner(int max, const char *owner) {
    int sum = max - mx_strlen(owner);

    if (sum == mx_strlen(owner))
        mx_printstr("  ");
    else
        mx_print_space(sum);
    mx_printstr("  ");
}

int mx_get_maxowner(t_list *entities) {
    int max = 0;

    for (; entities != 0; entities = entities->next) {
        t_dirent *custom_dirent = (t_dirent *)entities->data;
        struct stat i_stat = custom_dirent->file_stat;
        if (max < mx_strlen(mx_get_owner(i_stat.st_uid)))
            max = mx_strlen(mx_get_owner(i_stat.st_uid));
    }
    return max;
}

int mx_get_maxgroup(t_list *entities) {
    int max = 0;

    for (; entities != 0; entities = entities->next) {
        t_dirent *custom_dirent = (t_dirent *)entities->data;
        struct stat i_stat = custom_dirent->file_stat;
        if (max < mx_strlen(mx_get_group(i_stat.st_gid)))
            max = mx_strlen(mx_get_group(i_stat.st_gid));
    }
    return max;
}
