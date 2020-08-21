#include <unistd.h>
#include <string.h>

void mx_printstr(const char *s) {
    write(1, s, strlen(s));
}
