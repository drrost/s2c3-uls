//
// Created by Karina Barinova on 10.09.2020.
//

#include <uls.h>

int mx_find_blocks(t_list *entities, int files_count) {
    int blocks = 0;
    for (int i = 0; i < files_count; i++) {
        t_dirent *custom_dirent = (t_dirent *)entities->data;
        struct stat i_stat = custom_dirent->file_stat;
        blocks += i_stat.st_blocks;
        entities = entities->next;
    }
    return blocks;
}
