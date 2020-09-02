#include <uls.h>

unsigned char mx_acl_strcol(char *acl) {
    if (acl[0] == 'd' && acl[8] == 'w' && acl[9] == 't')
        return MX_BLACK;
    else if (acl[0] == '-' && acl[9] == 'x')
        return MX_RED;
    else if (acl[0] == 'c' || acl[0] == 'b')
        return MX_BLUE;
    else if (acl[0] == 'd')
        return MX_BLUE;
    else if (acl[0] == 'l')
        return MX_MAGENTA;
    else if (acl[0] == 's')
        return MX_GREEN;
    else if (acl[0] == 'p')
        return MX_RED;
    return MX_DEF;
}
