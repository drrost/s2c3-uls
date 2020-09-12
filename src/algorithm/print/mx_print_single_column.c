#include <uls.h>

static void do_print(t_list *entities, const char *delim) {
    while (entities) {
        t_dirent *entity = (t_dirent *)entities->data;
        mx_printstr(entity->name);
        mx_printstr(delim);
        entities = entities->next;
    }
}

void mx_print_single_column(t_list *dirs, const char *delim) {
    mx_print_dirs(dirs, delim, do_print);
}
