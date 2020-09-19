#include <unistd.h>
#include <stdlib.h>

#include <uls.h>

void mx_printerr(const char *s) {
    write(STDERR_FILENO, s, mx_strlen(s));
}

void mx_print_error_exit(enum e_error error, char *message) {
    switch (error) {
        case ERROR_ILLEGAL_OPTION:
            mx_printerr("uls: illegal option -- ");
            mx_printerr(message);
            mx_printerr("\n");
            mx_printerr("usage: uls [-");
            mx_printerr(FLAGS);
            mx_printerr("] [file ...]\n");
            break;
        default:
            mx_printerr("ERROR\n");
            break;
    }
    exit(1);
}
