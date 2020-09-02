#include <uls.h>
#include <sys/acl.h>
#include <sys/xattr.h>
#include <sys/types.h>

void mx_set_acl_ads(char *path, char *acl) {
    acl_t my_acl = acl_get_file(path, ACL_TYPE_EXTENDED);
    ssize_t len = 0;
    char *text_acl = acl_to_text(my_acl, &len);
    ssize_t buflen = listxattr(path, NULL, 0, XATTR_NOFOLLOW);

    acl[10] = ' ';
    if (text_acl && acl[0] != 'l')
        acl[10] = '+';
    if (buflen > 0)
        acl[10] = '@';
    acl_free(my_acl);
    if (text_acl)
        mx_strdel(&text_acl);
}
