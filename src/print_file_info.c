#include <sys/stat.h>
#include <sys/types.h>
#include <grp.h>
#include <pwd.h>
#include <uls.h>
#include <stdlib.h>

void print_group(struct dirent *dir) {
    struct stat buf;
    struct group *groupinfo;
    char *str = NULL;

    lstat(dir->d_name, &buf);
    groupinfo = getgrgid(buf.st_gid);
    if (groupinfo != NULL)
        printf("%s", groupinfo->gr_name);
    else {
        str = mx_itoa(buf.st_gid);
        mx_printstr(str);
        free(str);
    }
    mx_printstr("  ");
}

void print_owner(struct dirent *dir) {
    struct stat buf;

    stat(dir->d_name, &buf);
    mx_printstr(getpwuid(buf.st_uid)->pw_name);
    mx_printstr("  ");
}

static void print_size(struct stat buf) {
    mx_printstr(mx_itoa(buf.st_size));//print size
    mx_printstr("  ");
}

static void print_last_modified_time(struct stat buf) {
    mx_printstr(ctime(&buf.st_ctime));//last modified time
}

void mx_print_permissions(struct dirent *dir) {
    struct stat buf;

    stat(dir->d_name, &buf);
        mx_printstr((buf.st_mode & S_IRUSR) ? "r" : "-");
        mx_printstr((buf.st_mode & S_IWUSR) ? "w" : "-");
        mx_printstr((buf.st_mode & S_IXUSR) ? "x" : "-");
        mx_printstr((buf.st_mode & S_IRGRP) ? "r" : "-");
        mx_printstr((buf.st_mode & S_IWGRP) ? "w" : "-");
        mx_printstr((buf.st_mode & S_IXGRP) ? "x" : "-");
        mx_printstr((buf.st_mode & S_IROTH) ? "r" : "-");
        mx_printstr((buf.st_mode & S_IWOTH) ? "w" : "-");
        mx_printstr((buf.st_mode & S_IXOTH) ? "x" : "-");
        mx_printstr("  ");
        print_owner(dir);
        print_group(dir);
        print_size(buf);
        print_last_modified_time(buf);
        
}

void print_type_of_file(struct dirent *dir) {
    struct stat buf;

    stat(dir->d_name, &buf);
    switch(buf.st_mode & S_IFMT) {
        case S_IFREG: mx_printstr("-");
        break;
        case S_IFDIR: mx_printstr("d");
        break;
        case S_IFLNK: mx_printstr("l");
        break;
        case S_IFCHR: mx_printstr("c");
        break;
        case S_IFBLK: mx_printstr("b");
        break;
        case S_IFSOCK: mx_printstr("s");
        break;
        case S_IFIFO: mx_printstr("f");
        break;
    }
}

