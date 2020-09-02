#include <uls.h>

void mx_get_passwd(t_file *file) {
    t_passwd *passwd = getpwuid(file->stat.st_uid);

    file->username = mx_strdup(passwd->pw_name);
    file->gid = passwd->pw_gid;
}
