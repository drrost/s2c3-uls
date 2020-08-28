#include "uls.h"

// char *flag_F(char *file) {
// 	struct stat buf;

//  stat(file, &buf);
// 	switch(buf.st_mode & S_IFMT) {
//         case S_IFDIR: file = mx_strjoin(file, "/"); //directory
//         break;
//         case S_IFLNK: mx_strjoin(file, "@"); //link
//         break;
//         case S_IFSOCK: mx_strjoin(file, "="); 
//         break;
//         case S_IFIFO: mx_strjoin(file, "|"); 
//         break;
//         case S_IFEXEC: mx_strjoin(file, "*");//executable 
//     }
//     return file;
// } 
