#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>

#include <uls.h>

void uls(const char *path, bool op_a, bool op_l) {
    op_l++;
    struct dirent *dir;
    //opendir returns a pointer to directory entry
    DIR *directory = opendir(path);

    if (!directory) {
        if (errno == ENOENT) {
            perror(ULS);
            perror((const char *)directory);
            perror(NO_FILE_DIR);
        }
        else {
            // here could be another error message showing opendir()
            // failed for some other reasons
            perror("Cannot open a directory");
        }
        exit(EXIT_FAILURE);
    }
    //readdir returns next directory entry in the stream
    while ((dir = readdir(directory)) != 0) {
        if (!op_a && dir->d_name[0] == '.') // to skip "." and ".." directories
            continue;
        mx_printstr(dir->d_name);
        if (op_l)
            mx_printstr("\n");
        if (!op_l)
            // TODO: fix the last element alignment issue
            mx_printstr("\t\t");
    }
}

int main(int argc, char *argv[]) {
    const char *current_path = ".";

    if (argc == 1) {
        mx_basic(current_path);
    }
    else if (argc == 2) {
        if (argv[1][0] == '-') {
            int option_a = false;
            int option_l = false;
            char *p = (char *)(argv[1] + 1);

            while (*p) {
                if (*p == 'a')
                    option_a = true;
                else if (*p == 'l')
                    option_l = true;
                else {
                    mx_printerr(ILLEGAL_OPTION);
                    mx_printerr(p);
                    mx_printerr("\n");
                    mx_printerr(USAGE);
                    exit(EXIT_FAILURE);
                }
                p++;
            }
            uls(current_path, option_a, option_l);
        }
        else {
            uls(argv[1], 0, 0);
        }
    }
    else if (argc == 3) {
        if (argv[1][0] != '-') {
            mx_printerr(USAGE);
            exit(EXIT_FAILURE);
        }
        int option_a = false;
        int option_l = false;
        char *p = (char *)(argv[1] + 1);

        while (*p) {
            if (*p == 'a')
                option_a = true;
            else if (*p == 'l')
                option_l = true;
            else {
                mx_printerr(ILLEGAL_OPTION);
                mx_printerr(p);
                mx_printerr("\n");
                mx_printerr(USAGE);
                exit(EXIT_FAILURE);
            }
            p++;
        }
        uls(argv[2], option_a, option_l);
    }
    return 0;
}
