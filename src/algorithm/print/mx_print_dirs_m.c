#include <uls.h>

int mx_count_files(t_list *entities) {
	int sum = 0;                                                                                   

    while (entities) {                                                                  
     t_dirent *entity = (t_dirent *)entities->data;  

     if (entity->name[0] != '.') {                                                                 
             sum++;                                                                                
     }                                                                                             
     entities = entities->next;                                                                    
    }                                                                                                                                                                                 
    return sum;   
}

void mx_print_dir_content_m(t_list *entities, const char *delim) {
	int counter = mx_count_files(entities);
	int i = 0;

	while (entities) {
		t_dirent *entity = (t_dirent *)entities->data;

		if (entity->name[0] != '.') {
			mx_printstr(entity->name);
			if (i != counter - 1)
				mx_printstr(", ");
			mx_printstr(delim); //MUST be removed
			i++;
		}
		entities = entities->next;
	}
}

void mx_print_dirs_m(t_list *dirs, const char *delim) {
	//hidden files and dirs are not printed

    t_dir *dir = (t_dir *)dirs->data;
    
    mx_print_dir_content_m(dir->entities, delim);
}
