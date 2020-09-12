#include <uls.h>

static void do_print(t_list *entities, const char *delim) {
    int counter = mx_list_size(entities);
    int i = 0;

    while (entities) {
        t_dirent *entity = (t_dirent *)entities->data;
        mx_printstr(entity->name);
        if (i != counter - 1)
            mx_printstr(delim);
        i++;
        entities = entities->next;
    }
}

void mx_print_dirs_m(t_list *dirs, const char *delim) {
    mx_print_dirs(dirs, delim, do_print);
}
