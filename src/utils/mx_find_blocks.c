//
// Created by Karina Barinova on 10.09.2020.
//

#include <uls.h>

int mx_find_blocks(t_list *entities, int files_count) {
	struct stat buf;
	int blocks = 0;
	for (int i = 0; i < files_count; i++) {
		lstat(mx_find_index(entities, i), &buf);
		blocks += buf.st_blocks;
	}
	return blocks;
}
