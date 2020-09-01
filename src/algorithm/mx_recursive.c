//
// Created by Rostyslav Druzhchenko on 27.08.2020.
//

#include <uls.h>
#include <unistd.h>

// -R /Users/rdruzhchenko/Dropbox/SharedProjects/ucode/stage2/03_uls/test/tests/tr00_pdf/ts01_recursive/dir00

static void do_scan(const char *dir_name, t_list **dirs) {

    static int level = 0;
    level++;

    mx_printline("\ndo_scan  >>>>>");
    mx_printstr("Level: ");
    mx_printint(level);
    mx_printline("");

    mx_printstr("dir_name:    ");
    mx_printstr(dir_name);
    mx_printline("");

    mx_scandir(dir_name, dirs, mx_select_exclude_dot_dirs, mx_alphasort);
    t_list *last_dir_node = mx_list_get_last(*dirs);
    t_dir *dir = (t_dir*)last_dir_node->data;
    t_list *entities = dir->entities;

    while (entities) {
        tp_dirent dir_ent = (tp_dirent)entities->data;
        mx_printstr("dir_ent->d_name : ");
        mx_printline(dir_ent->d_name);

        if (dir_ent && dir_ent->d_type == DT_DIR) {
            int parent_len = mx_strlen(dir_name);
            int len = parent_len + 1 + mx_strlen(dir_ent->d_name);
            char *subdir_name = mx_strnew(len);
            char *old = subdir_name;
            mx_strcpy(subdir_name, dir_name);
            subdir_name += parent_len;
            subdir_name[0] = '/';
            subdir_name += 1;
            mx_strcpy(subdir_name, dir_ent->d_name);

            subdir_name = old;
            mx_printstr("subdir_name: ");
            mx_printline(subdir_name);

            do_scan(subdir_name, dirs);
            mx_strdel(&subdir_name);
        }
        entities = entities->next;
    }
    level--;
    mx_printline("do_scan  <<<<<");
    mx_printline("");
}

void mx_recursive(const char *dir_name) {
    t_list *dirs = 0;

    do_scan(dir_name, &dirs);

    char *delim = isatty(STDOUT_FILENO) ? "\t\t" : "\n";
    mx_print_dirent_simple(dirs, delim);

}
