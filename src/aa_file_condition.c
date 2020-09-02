#include <uls.h>

bool mx_A_file_condition(char *name) {
    if (mx_strcmp(".\0", name) != 0
        && mx_strcmp("..\0", name) != 0) {
        return true;
    }
    return false;
}
