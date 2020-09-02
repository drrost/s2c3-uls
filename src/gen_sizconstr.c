#include <uls.h>

static void push_num(int num, int pos, char *res) {
    char *arr = mx_itoa(num);
    int len = mx_strlen(arr);

    for (int i = 0; i < len; i++)
        res[i + pos] = arr[i];
    mx_strdel(&arr);
}

static int get_mod_part(double full) {
    int a = (full - (int)full) * 10;
    int b = (full - (int)full) * 100 - (a * 10);

    if (b != 0)
        if (b >= 5)
            a++;
    return a;
}

static void get_big_part(double full, int *state, int len, char *res) {
    if (get_mod_part(full) >= 5)
            full++;
    if (full >= 1000) {
        push_num(1, 1, res);
        res[2] = '.';
        push_num(0, 3, res);
        (*state) += 1;
    }
    else
        push_num(full, 3 - len + 1, res);
}

static void more_div(unsigned long long size, char *res, char *types) {
    unsigned long long del = 1024;
    int state = 1;
    double full = 0;

    while (size / del >= 1000) {
        del *= 1024;
        state++;
    }
    if (state > 5)
        return ;
    full = (double)size / (double)del;
    if (full < 10) {
        push_num(full, 1, res);
        res[2] = '.';
        push_num(get_mod_part(full), 3, res);
    }
    else
        get_big_part(full, &state, mx_nbrlen(full), res);
    res[4] = types[state];
}

char *mx_gen_sizconstr(unsigned long long size) {
    char types[7] = {'B', 'K', 'M', 'G', 'T', 'P', '\0'};
    char *res = mx_strdup("   0B\0");
    unsigned int len = 0;

    if (size < 1000) {
        len = mx_nbrlen((int)size);
        push_num(size, 3 - len + 1, res);
    }
    else
        more_div(size, res, types);
    return res;
}
