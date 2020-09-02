#include <uls.h>

void mx_print_G(char *name, char *acl) {
    mx_change_color(mx_acl_strcol(acl), mx_acl_bkcol(acl));
    mx_printstr(name);
    mx_color_reset();
}
