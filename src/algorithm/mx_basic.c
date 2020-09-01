//
// Created by Rostyslav Druzhchenko on 25.08.2020.
//

#include <uls.h>
#include <unistd.h>

// TODO: delete commented code
//
//void print_dirent_arr(struct dirent **arr, char *delim) {
//    //works as ls -1 for now
//    for (int i = 0; arr[i]; i++) {
//        if (arr[i]->d_name[0] == '.')
//            continue;
//        else {
//            mx_printstr(arr[i]->d_name);
//        }
//        if (arr[i + 1] != 0)
//            mx_printstr(delim);
//    }
//    mx_printstr("\n");
//}

static void print_dir_content(t_list *entities, const char *delim) {
    while (entities) {
        t_dirent *entity = (t_dirent *)entities->data;
        mx_printstr(entity->name);
        if (entities->next != 0)
            mx_printstr(delim);
        entities = entities->next;
    }
}


void mx_basic(const char *dir_name) {
    t_list *dirs = 0;

    mx_scandir(dir_name, &dirs, mx_select_exclude_dot_dirs, mx_alphasort);
    char *delim = isatty(STDOUT_FILENO) ? "\t\t" : "\n";
    t_dir *dir = (t_dir *)dirs->data;
    print_dir_content(dir->entities, delim);
    mx_printline("");

//    mx_delete_dirent_arr(&arr);
}
