//
// Created by Karina Barinova on 09.09.2020.
//

#include <uls.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void mx_print_permissions(mode_t mode) {
	char perms[11];
	if (MX_ISREG(mode))
		perms[0] = '-';
	else if (MX_ISDIR(mode))
		perms[0] = 'd';
	else if (MX_ISFIFO(mode))
		perms[0] = '|';
	else if (MX_ISSOCK(mode))
		perms[0] = 's';
	else if (MX_ISCHR(mode))
		perms[0] = 'c';
	else if (MX_ISBLK(mode))
		perms[0] = 'b';
	else if (MX_ISLNK(mode))
		perms[0] = 'l';
	//user
	perms[1] = (mode & MX_IRUSR) ? 'r' : '-';
	perms[2] = (mode & MX_IWUSR) ? 'w' : '-';
	perms[3] = (mode & MX_IXUSR) ? 'x' : '-';
	perms[3] = (mode & MX_ISUID) ? 's' : perms[3];
	//group
	perms[4] = (mode & MX_IRGRP) ? 'r' : '-';
	perms[5] = (mode & MX_IWGRP) ? 'w' : '-';
	perms[6] = (mode & MX_IXGRP) ? 'x' : '-';
	perms[6] = (mode & MX_ISGID) ? 's' : perms[6];
	//other
	perms[7] = (mode & MX_IROTH) ? 'r' : '-';
	perms[8] = (mode & MX_IWOTH) ? 'w' : '-';
	perms[9] = (mode & MX_IXOTH) ? 'x' : '-';
	perms[9] = (mode & MX_ISVTX) ? 't' : perms[9];
	perms[10] = '\0';
	mx_printstr(perms);

}

void mx_print_dir_long_format(t_list *entities, const char *delim) {
	struct stat buf;
	int files_count = mx_get_num_files(entities);
	mx_printstr("total: ");
	mx_printstr("\n");
	for (int i = 0; i < files_count; i++) {
		lstat(mx_find_index(entities, i), &buf);
		mx_print_permissions(buf.st_mode);
		mx_printstr(delim);
		mx_printstr("\n");
	}
}

void mx_print_long(t_list *dirs, const char *delim) {
	//hidden files and dirs are not printed

    t_dir *dir = (t_dir *)dirs->data;
    mx_print_dir_long_format(dir->entities, delim);
}
