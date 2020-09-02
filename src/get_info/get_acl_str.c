#include <uls.h>

#include "uls.h"

static void set_file_type(t_file *file, char *acl) {
    acl[0] = MX_ISDIR(file->stat.st_mode) ? 'd' : '-';
    acl[0] = MX_ISCHR(file->stat.st_mode) ? 'c' : acl[0];
    acl[0] = MX_ISBLK(file->stat.st_mode) ? 'b' : acl[0];
    acl[0] = MX_ISFIFO(file->stat.st_mode) ? 'p' : acl[0];
    acl[0] = MX_ISLNK(file->stat.st_mode) ? 'l' : acl[0];
    acl[0] = MX_ISSOCK(file->stat.st_mode) ? 's' : acl[0];
}

static void set_user_acl(t_file *file, char *acl) {
    acl[1] = (file->stat.st_mode & MX_IRUSR) ? 'r' : '-';
    acl[2] = (file->stat.st_mode & MX_IWUSR) ? 'w' : '-';
    acl[3] = (file->stat.st_mode & MX_IXUSR) ? 'x' : '-';
    acl[3] = (file->stat.st_mode & MX_ISUID) ? 's' : acl[3];
}

static void set_group_acl(t_file *file, char *acl) {
    acl[4] = (file->stat.st_mode & MX_IRGRP) ? 'r' : '-';
    acl[5] = (file->stat.st_mode & MX_IWGRP) ? 'w' : '-';
    acl[6] = (file->stat.st_mode & MX_IXGRP) ? 'x' : '-';
    acl[6] = (file->stat.st_mode & MX_ISGID) ? 's' : acl[6];
}

static void set_other_acl(t_file *file, char *acl) {
    acl[7] = (file->stat.st_mode & MX_IROTH) ? 'r' : '-';
    acl[8] = (file->stat.st_mode & MX_IWOTH) ? 'w' : '-';
    acl[9] = (file->stat.st_mode & MX_IXOTH) ? 'x' : '-';
    acl[9] = (file->stat.st_mode & MX_ISVTX) ? 't' : acl[9];
}

char *mx_gen_acl_str(t_file *file, char *path) {
    char *acl = mx_strnew(11);

    set_file_type(file, acl);
    set_user_acl(file, acl);
    set_group_acl(file, acl);
    set_other_acl(file, acl);
    mx_set_acl_ads(path, acl);
    return acl;
}
