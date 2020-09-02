#include <uls.h>

static bool m_cond(char *name, int screen, t_out *out) {
    if ((mx_unicode_strlen(name) + 3) <= screen
        || (out->j == out->file_amount - 1
        && mx_unicode_strlen(name) + 1 <= screen)
        || out->j == 0) {
        return true;
    }
    return false;
}

static void m_cycle_cond(char *name, char *acl, int *screen, t_out *out) {
    if (out->flags->f_G) {
        mx_print_G(name, acl);
        (*screen) = (*screen) - (mx_unicode_strlen(name) + 2);
    }
    else{
        mx_printstr(name);
        (*screen) = (*screen) - (mx_unicode_strlen(name) + 2);
    }
}

void mx_print_m_cycle(t_file **file, t_out *out) {
    int screen = out->screen_size;

    for (; file[out->j]; out->j++) {
            if (m_cond(file[out->j]->name, screen, out))
                m_cycle_cond(file[out->j]->name, file[out->j]->acl, &screen, out);
            else if (out->j != 0) {
                mx_printstr("\n");
                screen = out->screen_size;
                m_cycle_cond(file[out->j]->name, file[out->j]->acl, &screen, out);
            }
        if (out->j < out->file_amount - 1)
            mx_printstr(", ");
    }
    if (out->flags->f_r && !out->flags->def_dots && !out->flags->def_file_dots)
        mx_printstr(",");
    mx_printstr("\n");
}
