//
// Created by Rostyslav Druzhchenko on 27.08.2020.
//

#include <uls.h>

static void do_scan(t_list **dirs, FETCH_PARAMS) {
    mx_scandir(dir_name, dirs, filter, cmp);

    t_list *last_dir_node = mx_list_get_last(*dirs);
    t_dir *dir = (t_dir *)last_dir_node->data;
    t_list *entities = dir->entities;

    while (entities) {
        t_dirent *dir_ent = (t_dirent *)entities->data;

        if (dir_ent->type == DT_DIR) {
            char *subdir_name = mx_add_path(dir_name, dir_ent->name);
            do_scan(dirs, subdir_name, filter, cmp);
            mx_strdel(&subdir_name);
        }
        entities = entities->next;
    }
}

t_list *mx_fetch_recursive(FETCH_PARAMS) {
    t_list *dirs = 0;
    do_scan(&dirs, dir_name, filter, cmp);
    return dirs;
}
