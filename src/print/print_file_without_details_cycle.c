#include <uls.h>

static void tab_print(int tab, t_out *out) {
    for (out->k = 0; out->k < tab; out->k++)
        mx_printstr("\t");
}

static void space_print(int space, t_out *out) {
    for (out->k = 0; out->k < space; out->k++)
        mx_printstr(" ");
}

void mx_print_file_cond(char *name, char *acl, t_out *out, int newct) {
    int tab = 0;
    int space = 0;

    if (out->flags->f_G && isatty(1) != 0) {
        space = mx_space_amount(name, out->count);
        mx_print_G(name, acl);
        if (out->j + out->i + out->rows < out->file_amount && out->flags->f_1 != 1)
            space_print(space, out);
    }
    else {
        tab = mx_tab_amount(name, out->count);
        mx_printstr(name);
        if (out->j + out->i + out->rows < out->file_amount
            && newct != out->columns && out->flags->f_1 != 1) {
            tab_print(tab, out);
        }
    }
}

void mx_print_file_without_details_cycle(t_file **file, t_out *out) {
    int newct = 0;

    if (out->flags->f_m) {
        mx_print_m_cycle(file, out);
    }
    else {
        for (out->i = 0; out->i < out->rows; out->i++) {
            for (out->j = 0; file[out->j + out->i]; out->j++) {
                if (out->j % out->rows == 0 && file[out->j + out->i]) {
                    newct++;
                    mx_print_file_cond(file[out->j + out->i]->name, 
                                        file[out->j + out->i]->acl, out, newct);
                }
            }
        newct = 0;
        mx_printstr("\n");
        }
    }
}
