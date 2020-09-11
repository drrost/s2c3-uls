#include <uls.h>

void mx_print_dir_content_single_column(t_list *entities, const char *delim, bool print_hidden) {
	while (entities) {
		t_dirent *entity = (t_dirent *)entities->data;
		if (!print_hidden) {
			if (entity->name[0] != '.') {
				mx_printstr(entity->name);
				mx_printstr(delim);
			}
		}
		else {
			mx_printstr(entity->name);
			mx_printstr(delim);
		}
		entities = entities->next;
	}
}

void mx_print_single_column(t_list *dirs, const char *delim) {
	//hidden files and dirs are not printed

    t_dir *dir = (t_dir *)dirs->data;
    mx_print_dir_content_single_column(dir->entities, delim, false);
}

void mx_print_single_column_all(t_list *dirs, const char *delim) {
	t_dir *dir = (t_dir *)dirs->data;
    mx_print_dir_content_single_column(dir->entities, delim, true);
}

