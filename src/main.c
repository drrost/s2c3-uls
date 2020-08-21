#include "../inc/uls.h"
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

void mx_printstr(const char *s);

void mx_printerr(const char *s) {
    write(2, s, strlen(s));
}

void uls(const char *path, bool op_a, bool op_l) {
    struct dirent *dir;
    DIR *directory = opendir(path); //opendir returns a pointer to directory entry

    if (!directory) {
        if(errno == ENOENT) {
	    perror(ULS);
	    perror((const char *)directory);
	    perror(NO_FILE_DIR);
	}
	else {
	    perror("Cannot open a directory"); // here could be another error message showing opendir() failed for some other reasons
	}
	exit(EXIT_FAILURE);
    }
    while ((dir = readdir(directory)) != NULL) { //readdir returns next directory entry in the stream
        if (!op_a && dir->d_name[0] == '.') // to skip "." and ".." directories
	    continue;
	mx_printstr(dir->d_name);
	if (op_l)
	    mx_printstr("\n");
	if (!op_l)
	    mx_printstr("\t\t"); // TO DO: fix the last element alignment issue 
    }
}

int main(int argc, char *argv[]) {
    const char *current_path = ".";

    if (argc == 1) {
        uls(current_path, 0, 0);
    } else if (argc == 2) {
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
