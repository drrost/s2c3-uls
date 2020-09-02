#include <uls.h>

static void push_dir(t_uls *uls, t_d_lst **head, char *arg, t_out *out) {
    t_dir *dir = mx_read_dir(uls->flags, arg, out);
    mx_push_data_back(head, NULL, dir);
}

static void push_file_fd(t_uls *uls, t_d_lst **head, char *arg) {
    t_file *file = mx_read_file("/", arg, uls->flags);
    mx_push_data_back(head, file, NULL);
}

static void push_file_pd(t_uls *uls, t_d_lst **head, char *arg) {
    t_file *file = mx_read_file("./", arg, uls->flags);
    mx_push_data_back(head, file, NULL);
}

void mx_prepare_data(t_uls *uls, t_d_lst **head, char *arg, t_out *out) {
    int res = 0;

    uls->flags->r_fd_only = true;
    res = mx_check_is_folder(arg);
    if (res == 1)
        push_dir(uls, head, arg, out);
    else if (res == 0) {
        if (arg[0] == '/')
            push_file_fd(uls, head, arg);
        else
            push_file_pd(uls, head, arg);
    }
    else {
        mx_print_warning(MX_ERR_ULS, arg, MX_ERR_NSFOD);
        uls->flags->print_pathes = 1;
        uls->flags->errtrig = 1;
    }
}
