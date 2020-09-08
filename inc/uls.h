#ifndef ULS_H
#define ULS_H

#include <libmx.h>

// Macros
#define USAGE "usage: uls [-l] [file ...]\n"
#define ULS "uls: "
#define NO_FILE_DIR ": No such file or directory"
#define ILLEGAL_OPTION "uls: illegal option -- "
#define FLAGS "al"

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
    ERROR_WRONG_PARAM_NUMBER,
    ERROR_FILE_NOT_FOUND,
    ERROR_FILE_IS_EMPTY,
    ERROR_LINE_NOT_VALID,
    ERROR_INVALID_NUMBER_OF_ISLANDS,
    ERROR_DUPLICATE_BRIDGES,
    ERROR_SUM_OF_BRIDGES_TOO_BIG,
    ERROR_NOT_ENOUGH_MEMORY
};

typedef struct s_flags {
    bool flag_l;
    bool flag_a;
    bool flag_R;
}              t_flags;

typedef struct s_info {
    char *short_name; //example main.c
    char *full_name;//example ./src/main.c
    char file_type; //dir, regular file, link etc.
    //char *acl_info;
}              t_info;

typedef struct s_input {
    int win_width;
    char **files;
    char *flags;
    t_info **info;
    int string_size;
    int files_num;
}              t_input;


void mx_print_error_exit(enum e_error error, char *message);
void mx_printerr(const char *s);

void mx_basic(const char *dir_name);

// Utils
void mx_delete_dirent_arr(struct dirent ***arr);

// Fetchers
#define FETCHER(name) t_list *(*name)(const char *)
t_list *mx_fetch_one_dir(const char *dir_name); // list of `t_dir`
t_list * mx_fetch_recursive(const char *dir_name);

// Printers
#define PRINTER(name) void (*name)(t_list *, const char *) // list of t_dirs
void mx_print_single_dir(t_list *entities, const char *delim);
void mx_print_dirs_recursive(t_list *dirs, const char *delim);

void mx_print_dir_content(t_list *entities, const char *delim);
void mx_print_dir_content_single_column(t_list *entities, const char *delim);
void mx_print_single_column(t_list *entities, const char *delim);

int get_window_size(void);

// Algorithm
typedef struct s_algorithm {
    FETCHER(fetcher);
    PRINTER(printer);
    t_list *paths;
    char *delim;
}              t_algorithm;

t_algorithm *mx_parse_arguments(int argc, char *argv[]);
void mx_run_algorithm(t_algorithm *algorithm);
t_algorithm *mx_algorithm_new();
void mx_algorithm_del(t_algorithm **algorithm);

#endif
