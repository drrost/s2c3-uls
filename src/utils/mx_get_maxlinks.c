//
// Created by Karina Barinova on 09.09.2020.
//

#include <uls.h>
#include <stdlib.h>

int mx_get_maxlinks(t_list *entities, bool print_hidden) {
	int max = 0;
	int i = 0;
	char *l = NULL;
	struct stat buf;

	for (; entities != NULL; entities = entities->next) {
		t_dirent *entity = (t_dirent *)entities->data;
		if (!print_hidden) {
			if (entity->name[0] != '.') {
				lstat(mx_find_index(entities, i, print_hidden), &buf);
				i++;
				l = mx_itoa(buf.st_nlink);
				if (max < mx_strlen(l))
					max = mx_strlen(l);
				free(l);
			}
		}
		else {
			lstat(mx_find_index(entities, i, print_hidden), &buf);
				i++;
				l = mx_itoa(buf.st_nlink);
				if (max < mx_strlen(l))
					max = mx_strlen(l);
				free(l);
		}
	}
	return max;
}
