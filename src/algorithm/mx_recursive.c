//
// Created by Rostyslav Druzhchenko on 27.08.2020.
//

#include <uls.h>
#include <unistd.h>

// -R /Users/rdruzhchenko/Dropbox/SharedProjects/ucode/stage2/03_uls/test/tests/tr00_pdf/ts01_recursive/dir00

static void print_dir_content(t_list *entities, const char *delim) {
    while (entities) {
        t_dirent *entity = (t_dirent *)entities->data;
        mx_printstr(entity->name);
        if (entities->next != 0)
            mx_printstr(delim);
        entities = entities->next;
    }
}

static char *mx_strformat(const char *f, ...) {
    va_list arg;

    int len = 10;
    int locations[len];
    mx_memset(locations, 0, len * sizeof(int));

    int count = 0;
    int i = 0;
    char *s = f;
    while (*s) {
        if (*s == '%' && *s + 1 != '%') {
            locations[count] = i;
            count++;
        }
        s++;
        i++;
    }

    int f_len = mx_strlen(f);
    int new_len = f_len - 2 * count;

    va_start(arg, f);
    for (int i = 0; i < count; i++) {
        char *s = va_arg(arg, char *);
        new_len += mx_strlen(s);
    }
    va_end(arg);

    char *new_s = mx_strnew(new_len);

    va_start(arg, f);
    mx_strncpy(new_s, f, locations[0]);
    int pos = locations[0];
    for (int i = 0; i < count; i++) {
        char *s = va_arg(arg, char *);
        int len = mx_strlen(s);
        mx_strcpy(new_s + pos, s);
        pos += len;
        int aaa = 0;
        if (i + 1 != count) {
            aaa = locations[i + 1] - locations[i] - 2;
        } else {
            aaa = f_len - locations[i] + 2;
        }
        mx_strncpy(new_s + pos, f + locations[i] + 2, aaa);
        pos += aaa;
    }
    va_end(arg);

    return new_s;
}

static void do_scan(const char *dir_name, t_list **dirs) {
    mx_scandir(dir_name, dirs, mx_select_exclude_dot_dirs, mx_alphasort);

    t_list *last_dir_node = mx_list_get_last(*dirs);
    t_dir *dir = (t_dir *)last_dir_node->data;
    t_list *entities = dir->entities;

    while (entities) {
        t_dirent *dir_ent = (t_dirent *)entities->data;

        if (dir_ent->type == DT_DIR) {
            int parent_len = mx_strlen(dir_name);
            int len = parent_len + 1 + mx_strlen(dir_ent->name);
            char *subdir_name = mx_strnew(len);
            char *old = subdir_name;
            mx_strcpy(subdir_name, dir_name);
            subdir_name += parent_len;
            subdir_name[0] = '/';
            subdir_name += 1;
            mx_strcpy(subdir_name, dir_ent->name);

            subdir_name = old;

            do_scan(subdir_name, dirs);
            mx_strdel(&subdir_name);
        }
        entities = entities->next;
    }
}


static void print_dirs_recursive(t_list *dirs, char *delim) {
    int count = 0;

    while (dirs) {
        t_dir *dir = (t_dir*)dirs->data;
        if (count != 0) {
            mx_printline(dir->name);
        }

        t_list *entities = (t_list *)dir->entities;
        print_dir_content(entities, delim);
        mx_printstr("\n\n");

        dirs = dirs->next;
        count++;
    }
    mx_printline("");
}

void mx_recursive(const char *dir_name) {
    t_list *dirs = 0;

    do_scan(dir_name, &dirs);

    char *delim = isatty(STDOUT_FILENO) ? "\t\t" : "\n";
    mx_printline("----------------------------------------------------------");
    print_dirs_recursive(dirs, delim);
}
