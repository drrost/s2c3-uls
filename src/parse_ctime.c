#include <uls.h>

static void parse_year(time_t time,t_time *parsed_time, char *date) {
    parsed_time->year = mx_strnew(4);
    for (int i = 0; i < 4; i++)
        parsed_time->year[i] = date[i + 20];
    parsed_time->r_time = time;
}

t_time *mx_parse_ctime(time_t time, t_flags *flags) {
    t_time *parsed_time = (t_time *)malloc(sizeof(t_time));
    char *date = ctime(&time);
    int i = 0;

    parsed_time->mmdd = mx_strnew(6);
    for (i = 0; i < 6; i++)
        parsed_time->mmdd[i] = date[i + 4];
    if (flags->f_T) {
        parsed_time->time = mx_strnew(8);
        for (i = 0; i < 8; i++)
            parsed_time->time[i] = date[i + 11];
    }
    else {
        parsed_time->time = mx_strnew(5);
        for (i = 0; i < 5; i++)
            parsed_time->time[i] = date[i + 11];
    }
    parse_year(time, parsed_time, date);
    return parsed_time;
}
