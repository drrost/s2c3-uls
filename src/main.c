#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <sys/ioctl.h>
#include <unistd.h>
#include <uls.h>

int find_longest_name(DIR *directory) {
    int longest = 0;
    struct dirent *dir;

    while((dir = readdir(directory)) != 0) {
        if (mx_strlen(dir->d_name) > longest)
            longest = mx_strlen(dir->d_name);
    }
    //closedir()
    return longest;
}

void uls(const char *path, t_flags flags) {
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

    // //TEST: check length of directory entries
    // int tab_size = 8;
    // //int longest_name = (find_longest_name(directory)) + tab_size;

    // struct winsize ws; //check terminal width;
    // size_t line_length= 80;
    // if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != -1 
    // && 0 < ws.ws_col && ws.ws_col == (size_t)ws.ws_col)
    //     line_length = ws.ws_col;
    // //printf("Screen width: %zu\n", line_length);


    //readdir returns next directory entry in the stream
    while ((dir = readdir(directory)) != 0) {
        if (!flags.flag_a && dir->d_name[0] == '.')// to skip "." and ".." directories
            continue;
        

        if (flags.flag_l) {
            print_permissions(dir);
        }
        mx_printstr(dir->d_name);
        if (flags.flag_l)
            mx_printstr("\n");
        if (!flags.flag_l)
            // TODO: fix the last element alignment issue
            mx_printstr("\t\t");
    }
}

int main(int argc, char *argv[]) {

    const char *current_path = ".";
    t_flags flags;

    if (argc == 1) {
        mx_basic(current_path);
    }
    else if (argc == 2) {
        if (argv[1][0] == '-') {
            flags.flag_l = false;
            flags.flag_a = false;
            char *p = (char *)(argv[1] + 1);

            while (*p) {
                if (*p == 'a')
                    flags.flag_a = true;
                else if (*p == 'l')
                    flags.flag_l = true;
                else {
                    mx_printerr(ILLEGAL_OPTION);
                    mx_printerr(p);
                    mx_printerr("\n");
                    mx_printerr(USAGE);
                    exit(EXIT_FAILURE);
                }
                p++;
            }
            uls(current_path, flags);
        }
        else {
            //uls(argv[1], 0, 0);
            //uls(argv[1], flags); //decide on steps if file/directory is passed
        }
    }
    else if (argc == 3) {
        if (argv[1][0] != '-') {
            mx_printerr(USAGE);
            exit(EXIT_FAILURE);
        }
        flags.flag_a = false;
        flags.flag_l = false;
        char *p = (char *)(argv[1] + 1);

        while (*p) {
            if (*p == 'a')
                flags.flag_a = true;
            else if (*p == 'l')
                flags.flag_l = true;
            else {
                mx_printerr(ILLEGAL_OPTION);
                mx_printerr(p);
                mx_printerr("\n");
                mx_printerr(USAGE);
                exit(EXIT_FAILURE);
            }
            p++;
        }
        uls(argv[2], flags);
    }
    return 0;
}
