#ifndef ULS_H
#define ULS_H

#include <libmx.h>
#include <sys/stat.h>

// Macros
#define USAGE "usage: uls [-ACFGRSacgilmortu1@] [file ...]\n"
#define ILLEGAL_OPTION "uls: illegal option -- "
#define FLAGS "ACFGRSacgilmoprtu1@"

//File types

#define MX_IFMT 0170000 // Mask of file type
#define MX_IFIFO 0010000 // Named pipe(fifo)
#define MX_IFCHR 0020000 //character device
#define MX_IFDIR 0040000 //directory file
#define MX_IFBLK 0060000 //Block device
#define MX_IFREG 0100000 //regular file
#define MX_IFLNK 0120000 //symbolic link
#define MX_IFSOCK 0140000 //UNIX domain socket

//Permissions

#define MX_IRWXU 0000700 //RWX for owner
#define MX_IRUSR 0000400 // R for owner
#define MX_IWUSR 0000200 // W for owner
#define MX_IXUSR 0000100 // X for owner

#define MX_IRWXG 0000070 // RWX for group
#define MX_IRGRP 0000040 //R for group
#define MX_IWGRP 0000020 //W for group
#define MX_IXGRP 0000010 //X for group

#define MX_IRWXO 0000007 //RWX mask for other
#define MX_IROTH 0000004 // R for other
#define MX_IWOTH 0000002 //W for other
#define MX_IXOTH 0000001 //X for other

#define MX_ISUID 0004000 //set user id on execution 
#define MX_ISGID 0002000 //set group id on execution
#define MX_ISVTX 0001000 //sticky bit 

#define MX_ISBLK(m) (((m) & MX_IFMT) == MX_IFBLK)
#define MX_ISCHR(m) (((m) & MX_IFMT) == MX_IFCHR)
#define MX_ISDIR(m) (((m) & MX_IFMT) == MX_IFDIR)
#define MX_ISFIFO(m) (((m) & MX_IFMT) == MX_IFIFO)
#define MX_ISREG(m) (((m) & MX_IFMT) == MX_IFREG)
#define MX_ISLNK(m) (((m) & MX_IFMT) == MX_IFLNK)
#define MX_ISXEC(m) ((m) & MX_IXUSR)
#define MX_ISSOCK(m) (((m) & MX_IFMT) == MX_IFSOCK)

#define MX_GETMAJOR(x) ((int32_t)(((u_int32_t)(x) >> 24) & 0xff)) \
//major number identifies the driver associated with the device
#define MX_GETMINOR(x) ((int32_t)((x) & 0xffffff)) \
//minor number refers to an instance


//color output
#define MX_COLOR_RESET "\x1B[0m"
#define MX_BLACK 0
#define MX_RED 1
#define MX_GREEN 2
#define MX_YELLOW 3
#define MX_BLUE 4
#define MX_MAGENTA 5
#define MX_CYAN 6
#define MX_WHITE 7
#define MX_DEFAULT 9

// README.md
//
// `_e' suffix in functions name means that function may exit in a case
// of error.
//
// `_w' suffix in structs' *fields* mean that the field is "weak", so
// the struct does not own data obtained in this field. In all other
// cases means that the struct owns a field and *MUST* call free()
// function for this field in an appropriate place (mx_delete_xxx).
//

// Errors

enum e_error {
    ERROR_ILLEGAL_OPTION,
    ERROR_FILE_NOT_FOUND,
    ERROR_FILE_IS_EMPTY,
    ERROR_LINE_NOT_VALID,
    ERROR_INVALID_NUMBER_OF_ISLANDS,
    ERROR_DUPLICATE_BRIDGES,
    ERROR_SUM_OF_BRIDGES_TOO_BIG,
    ERROR_NOT_ENOUGH_MEMORY
};

typedef struct s_flags {
    bool A;
    bool C;
    bool G;
    bool F;
    bool R;
    bool S;
    bool a;
    bool c;
    bool f;
    bool g;
    bool i;
    bool l;
    bool m;
    bool o;
    bool p;
    bool r;
    bool t;
    bool u;
    bool _1;
    bool at;
}              t_flags;


void mx_print_error_exit(enum e_error error, char *message);
void mx_printerr(const char *s);
void mx_print_error_no_such_file(char *name);

// Utils
char *mx_get_time_u(struct stat buf);
char *mx_get_time_c(struct stat buf);
void mx_delete_dirent_arr(struct dirent ***arr);
char *mx_find_index(t_list *entities, int index);
void mx_count_spaces(t_list *entities, int max, int j, const char *delim);
int mx_get_maxlen(t_list *entities);
int mx_get_max_spaces(int longest);
int mx_lines_count(int files_count, int longest);
char *mx_get_size(struct stat buf);
char *mx_get_time(struct stat buf);
char *mx_get_owner(uid_t st_uid);
char *mx_get_group(gid_t st_gid);
int mx_find_blocks(t_list *entities, int files_count);
char *mx_get_permissions(mode_t mode, const char *path, char *name);
char *get_path(const char *dir, char *file);
char mx_get_attr(const char *path, char *name);
void mx_print_space(int n);
int mx_get_maxinode(t_list *entities);
void mx_print_link(t_list *entities);
int mx_get_maxsize(t_list *entities);
int mx_get_maxlinks(t_list *entities);
void mx_print_space_owner(int max, const char *owner);
int mx_get_maxowner(t_list *entities);
int mx_get_maxgroup(t_list *entities);
void mx_print_space_size(int max, const char *size);
void mx_print_total(t_list *entities, int files_count);

int mx_get_maxlen_all(t_list *entities);
int mx_get_num_files_all(t_list *entities);
void mx_count_spaces_all(t_list *entities, int max, int j, const char *delim);
char *mx_find_index_all(t_list *entities, int index);

int mx_color_set(unsigned char a, unsigned char b);
int mx_color_reset();
unsigned char mx_acl_bkcol(char *acl);
unsigned char mx_acl_strcol(char *acl);

bool check_valid_flags(const char *flags);

// Fetchers
#define FETCH_PARAMS const char *dir_name, t_filter filter, t_comparator cmp
#define FETCHER(name) t_list *(*name)(FETCH_PARAMS)

typedef struct s_fetcher {
    FETCHER(fetch);
    t_filter filter;
    t_comparator comparator;
}              t_fetcher;

// list of `t_dir`
t_list *mx_fetch_one_dir(FETCH_PARAMS);
t_list *mx_fetch_recursive(FETCH_PARAMS);

// Sort comparators
int mx_alphasort(t_dirent *d1, t_dirent *d2);
int mx_time_modify_sort(t_dirent *d1, t_dirent *d2);
int mx_time_access_sort(t_dirent *d1, t_dirent *d2);
int mx_time_ctime_sort(t_dirent *d1, t_dirent *d2);
int mx_no_sort(t_dirent *d1, t_dirent *d2);
int mx_size_sort(t_dirent *d1, t_dirent *d2);

// Filters
int mx_filter_none(const struct dirent *dirent);
int mx_filter_dot_dotdot(const struct dirent *dirent);
int mx_filter_dots(const struct dirent *dirent);

// Printers
#define PRINTER_PARAMS t_list *, const char *
#define PRINTER(name) void (*name)(PRINTER_PARAMS) // t_dir

typedef struct s_printer {
    PRINTER(printer);
    PRINTER(printer_link);
    bool is_recursive;
    char delim[10];
}              t_printer;

void
mx_print_dirs_recursive(t_list *dirs, const char *delim, PRINTER(printer));
void mx_print_dirs_long(t_list *dirs, const char *delim, PRINTER(printer));
void mx_print_single_column(t_list *entities, const char *delim);
void mx_print_dirs_m(t_list *dirs, const char *delim);
void mx_print_multicolumn(t_list *dirs, const char *delim);
void mx_print_multicolumn_p(t_list *entities, const char *delim);
void mx_print_long(t_list *dirs, const char *delim);
void mx_print_multicolumn_C(t_list *entities, const char *delim);
void mx_print_long_i(t_list *entities, const char *delim);
void mx_print_long_o(t_list *dirs, const char *delim);
void mx_print_long_at(t_list *entities, const char *delim);
void mx_print_long_g(t_list *entities, const char *delim);
void mx_print_multicolumn_F(t_list *dirs, const char *delim);
void mx_print_multicolumn_color(t_list *dirs, const char *delim);
void mx_print_long_c(t_list *entities, const char *delim);
void mx_print_long_u(t_list *entities, const char *delim);
void mx_print_long_link(t_list *entities, const char *delim);

int get_window_size(void);

// Algorithm

typedef struct s_algorithm {
    t_fetcher fetcher;
    t_printer printer;
    t_list *paths;
}              t_algorithm;

t_algorithm *mx_parse_arguments(int argc, char *argv[]);
bool mx_has_flag(const char *flags, char ch);
t_flags mx_parse_flags(const char *line);
void mx_check_options_e(const char *line);
t_list *mx_fetch_paths(int start_idx, int argc, char *argv[]);
void mx_run_algorithm(t_algorithm *algorithm);
t_algorithm *mx_algorithm_new();
void mx_algorithm_del(t_algorithm **algorithm);

// Assigners
void mx_assign_fetchers(t_algorithm *algorithm, t_flags *flags);
void mx_assign_sorters(t_algorithm *algorithm, t_flags *flags);
void mx_assign_filters(t_algorithm *algorithm, t_flags *flags);
void mx_assign_printers(t_algorithm *algorithm, t_flags *flags);

#endif
