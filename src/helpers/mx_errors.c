#include <unistd.h>
#include <stdlib.h>

#include <uls.h>

void mx_printerr(const char *s) {
    write(STDERR_FILENO, s, mx_strlen(s));
}

void mx_print_error_exit(enum e_error error, char *message) {
    switch (error) {
        case ERROR_WRONG_PARAM_NUMBER:
            mx_printerr("usage: ./pathfinder [filename]\n");
            break;
        case ERROR_FILE_NOT_FOUND:
            mx_printerr("error: file ");
            mx_printerr(message);
            mx_printerr(" does not exist\n");
            break;
        case ERROR_FILE_IS_EMPTY:
            mx_printerr("error: file ");
            mx_printerr(message);
            mx_printerr(" is empty\n");
            break;
        case ERROR_LINE_NOT_VALID:
            mx_printerr("error: line ");
            mx_printerr(message);
            mx_printerr(" is not valid\n");
            break;
        case ERROR_INVALID_NUMBER_OF_ISLANDS:
            mx_printerr("error: invalid number of islands\n");
            break;
        case ERROR_DUPLICATE_BRIDGES:
            mx_printerr("error: duplicate bridges\n");
            break;
        case ERROR_SUM_OF_BRIDGES_TOO_BIG:
            mx_printerr("error: sum of bridges lengths is too big\n");
            break;
        default:
            mx_printerr("ERROR\n");
            break;
    }
    exit(0);
}
