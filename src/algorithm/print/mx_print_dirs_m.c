#include <uls.h>

static int mx_count_files(t_list *entities, bool print_hidden) {
	int sum = 0;                                                                                   

    while (entities) {                                                                  
     t_dirent *entity = (t_dirent *)entities->data;  

     if (!print_hidden) {
	     if (entity->name[0] != '.') {                                                                 
	             sum++;                                                                                
	     }   
	 }
	 else 
	 	sum++;                                                                                         
     entities = entities->next;                                                                    
    }                                                                                                                                                                                 
    return sum;   
}

void mx_print_dir_content_m(t_list *entities, const char *delim, bool print_hidden) {
	int counter = mx_count_files(entities, print_hidden);
	int i = 0;

	while (entities) {
		t_dirent *entity = (t_dirent *)entities->data;
		if (!print_hidden) {
			if (entity->name[0] != '.') {
				mx_printstr(entity->name);
				if (i != counter - 1)
					mx_printstr(delim);
				i++;
			}
		}
		else {
			mx_printstr(entity->name);
			if (i != counter - 1)
				mx_printstr(delim);
			i++;
		}
		entities = entities->next;
	}
}

void mx_print_dirs_m(t_list *dirs, const char *delim) {
	//hidden files and dirs are not printed

    t_dir *dir = (t_dir *)dirs->data;

    mx_print_dir_content_m(dir->entities, delim, false);
    mx_printstr("\n");
}

void mx_print_dirs_m_all(t_list *dirs, const char *delim) {

    t_dir *dir = (t_dir *)dirs->data;

    mx_print_dir_content_m(dir->entities, delim, true);
    mx_printstr("\n");
}
