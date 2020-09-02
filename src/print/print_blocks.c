#include <uls.h>

void mx_print_blocks(unsigned long long blocks) {
    mx_printstr("total ");
    mx_printint(blocks);
    mx_printstr("\n");
}
