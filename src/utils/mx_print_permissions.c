//
// Created by Karina Barinova on 09.09.2020.
//

#include <uls.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <stdlib.h>

char *get_path(const char *dir, char *file) {
	const char *path = NULL;
	char *tmp = NULL;

	if (mx_strcmp(dir, "/") == 0)
		tmp = mx_strdup(dir);
	else
		tmp = mx_strjoin(dir, "/");
	path = mx_strjoin(tmp, file);
	if (tmp != NULL)
		free(tmp);
	return (char *)path;
}

char mx_get_attr(const char *path, char *name) {
		const char *my_path = get_path(path, name);
        ssize_t xattr;
        acl_t acl;

        if ((xattr = listxattr(my_path, NULL, 0, XATTR_NOFOLLOW)) > 0) {
        	return '@';
        }
        if ((acl = acl_get_file(my_path, ACL_TYPE_EXTENDED)) != (acl_t)NULL) {
        	acl_free(acl);
        	return '+';
        }
        return ' ';
}


char *mx_get_permissions(mode_t mode, const char *path, char *name) {
	//char perms[12];
	char *perms = mx_strnew(11);
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
	perms[10] = mx_get_attr(path, name);
	//perms[11] = '\0';
	return mx_strdup(perms);
}
