#include <uls.h>

unsigned char mx_acl_bkcol(char *acl) {
    if (acl[0] == 'd' && acl[8] == 'w' && acl[9] == 't')
        return MX_GREEN;
    else if (acl[0] == '-' && acl[9] == 'x')
        return MX_DEF;
    else if (acl[0] == 'b')
        return MX_CYAN;
    else if (acl[0] == 'c')
        return MX_YELLOW;
    else if (acl[0] == 'd')
        return MX_DEF;
    else if (acl[0] == 'l')
        return MX_DEF;
    else if (acl[0] == 's')
        return MX_DEF;
    else if (acl[0] == 'p')
        return MX_DEF;
    return MX_DEF;
}
