//
// Created by Karina Barinova on 15.09.2020.
//

#include <uls.h>
#include <unistd.h>
#include <stdlib.h>

void mx_print_link(t_list *entities) {
	char *s = 0;
	t_dirent *custom_dirent = (t_dirent *)entities->data;
    struct stat i_stat = custom_dirent->file_stat;

    s = mx_get_permissions(i_stat.st_mode, custom_dirent->path, custom_dirent->name);
	if (s[0] == 'l') {
		size_t link;
		char *path = get_path(custom_dirent->path, custom_dirent->name);
		link = readlink(path, NULL, 20000);
		if (link != 0) {
			char *res = malloc(10000);
			link = readlink(get_path(custom_dirent->path, custom_dirent->name), res, link);
			res[link] = '\0';
			mx_printstr(" -> ");
			mx_printstr(res);
			free(res);
		}
		mx_strdel(&path);
	}
	mx_strdel(&s);
}
