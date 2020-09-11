//
// Created by Karina Barinova on 09.09.2020.
//

#include <uls.h>


int mx_get_num_files(t_list *entities, bool print_hidden) {
    int sum = 0;

    while (entities != 0) {
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
