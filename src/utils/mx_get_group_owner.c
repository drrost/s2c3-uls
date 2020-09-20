//
// Created by Karina Barinova on 09.09.2020.
//

#include <uls.h>
#include <grp.h>
#include <pwd.h>

char *mx_get_owner(uid_t st_uid) {
    char *owner = NULL;
    struct passwd *pass;

    if ((pass = getpwuid(st_uid)) == NULL)
        owner = mx_itoa(st_uid);
    else
        owner = mx_strdup(pass->pw_name);
    return owner;
}

char *mx_get_group(gid_t st_gid) {
    char *group;
    struct group *buf;

    if ((buf = getgrgid(st_gid)) == NULL)
        group = mx_itoa(st_gid);
    else
        group = mx_strdup(buf->gr_name);
    return group;
}
