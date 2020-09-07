//
// Created by Rostyslav Druzhchenko on 27.08.2020.
//

#include <uls.h>

static void do_scan(const char *dir_name, t_list **dirs) {
    mx_scandir(dir_name, dirs, mx_select_exclude_dot_dirs, mx_alphasort);

    t_list *last_dir_node = mx_list_get_last(*dirs);
    t_dir *dir = (t_dir *)last_dir_node->data;
    t_list *entities = dir->entities;

    while (entities) {
        t_dirent *dir_ent = (t_dirent *)entities->data;

        if (dir_ent->type == DT_DIR) {
            char *subdir_name = mx_strformat("%s/%s", dir_name, dir_ent->name);
            do_scan(subdir_name, dirs);
//            mx_strdel(&subdir_name);
        }
        entities = entities->next;
    }
}

t_list *mx_fetch_recursive(const char *dir_name) {
    t_list *dirs = 0;
    do_scan(dir_name, &dirs);
    return dirs;
}
