#include <sys/stat.h>
#include <sys/types.h>
#include <uls.h>

static void print_size(struct stat buf) {
    mx_printstr(mx_itoa(buf.st_size));//print size
    mx_printstr("\t");
}

static void print_last_modified_time(struct stat buf) {
    mx_printstr(ctime(&buf.st_ctime));//last modified time
}

void print_permissions(struct dirent *dir) {
    struct stat buf;
    stat(dir->d_name, &buf);
        if (buf.st_size == 0) //check for empty file
            mx_printstr("-");
        mx_printstr((buf.st_mode & S_IRUSR) ? "r" : "-");
        mx_printstr((buf.st_mode & S_IWUSR) ? "w" : "-");
        mx_printstr((buf.st_mode & S_IXUSR) ? "x" : "-");
        mx_printstr((buf.st_mode & S_IRGRP) ? "r" : "-");
        mx_printstr((buf.st_mode & S_IWGRP) ? "w" : "-");
        mx_printstr((buf.st_mode & S_IXGRP) ? "x" : "-");
        mx_printstr((buf.st_mode & S_IROTH) ? "r" : "-");
        mx_printstr((buf.st_mode & S_IWOTH) ? "w" : "-");
        mx_printstr((buf.st_mode & S_IXOTH) ? "x" : "-");
        mx_printstr("\t");
        print_size(buf);
        print_last_modified_time(buf);
        
}
