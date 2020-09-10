//
// Created by Karina Barinova on 09.09.2020.
//

#include <uls.h>
#include <unistd.h>

static void mx_print_space_size(int max, const char *size) {
	if ((max - mx_strlen(size)) <= 0)
		mx_printstr("  ");
	else
		mx_print_space(((++max) - mx_strlen(size)) + 1);
}

void mx_print_dir_long_format(t_list *entities, const char *delim) {
	struct stat buf;
	int files_count = mx_get_num_files(entities);
	int max_size = mx_get_maxsize(entities);

	mx_printstr("total: ");
	mx_printstr(mx_itoa(mx_find_blocks(entities, files_count)));
	mx_printstr("\n");
	for (int i = 0; i < files_count; i++) {
		lstat(mx_find_index(entities, i), &buf);
		mx_print_permissions(buf.st_mode);
		mx_printstr(delim);
		mx_printint(buf.st_nlink);
		mx_printstr(" ");
		mx_printstr(mx_get_owner(buf.st_uid));
		mx_printstr(delim);
		mx_printstr(mx_get_group(buf.st_gid));
		mx_print_space_size(max_size, mx_get_size(buf));
		mx_printstr(mx_get_size(buf));
		mx_printstr(" ");
		mx_printstr(mx_get_time(buf));
		mx_printstr(" ");
		mx_printstr(mx_find_index(entities, i));
		mx_printstr("\n");
	}
}

void mx_print_long(t_list *dirs, const char *delim) {
	//hidden files and dirs are not printed

    t_dir *dir = (t_dir *)dirs->data;
    mx_print_dir_long_format(dir->entities, delim);
}
