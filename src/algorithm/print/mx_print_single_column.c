#include <uls.h>

void mx_print_single_column(t_list *entities, const char *delim) {
    while (entities) {
        t_dirent *entity = (t_dirent *)entities->data;
        mx_printstr(entity->name);
        mx_printstr(delim);
        entities = entities->next;
    }
}
