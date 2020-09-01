//
// Created by Rostyslav Druzhchenko on 27.08.2020.
//

#include <uls.h>
#include <unistd.h>

static void print_dir_content(t_list *entities, const char *delim) {
    while (entities) {
        t_dirent *entity = (t_dirent *)entities->data;
        mx_printstr(entity->name);
        if (entities->next != 0)
            mx_printstr(delim);
        entities = entities->next;
    }
}

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

static void print_dirs_recursive(t_list *dirs, char *delim) {
    int count = 0;

    while (dirs) {
        t_dir *dir = (t_dir*)dirs->data;
        if (count != 0) {
            mx_printstr(dir->name);
            mx_printstr(":\n");
        }

        t_list *entities = (t_list *)dir->entities;
        print_dir_content(entities, delim);
        if (entities && dirs->next) {
            mx_printstr("\n\n");
        } else {
            mx_printstr("\n");
        }

        dirs = dirs->next;
        count++;
    }
}

void mx_recursive(const char *dir_name) {
    t_list *dirs = 0;

    do_scan(dir_name, &dirs);

    char *delim = isatty(STDOUT_FILENO) ? "\t\t" : "\n";
    print_dirs_recursive(dirs, delim);
}
