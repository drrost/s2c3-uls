//
// Created by Karina Barinova on 10.09.2020.
//

#include <uls.h>
#include <time.h>

static char *date_less(char *buf) {
    char *res = mx_strnew(12);

    res[0] = buf[4];
    res[1] = buf[5];
    res[2] = buf[6];
    res[3] = ' ';
    res[4] = buf[8];
    res[5] = buf[9];
    res[6] = ' ';
    res[7] = buf[11];
    res[8] = buf[12];
    res[9] = buf[13];
    res[10] = buf[14];
    res[11] = buf[15];
    return res;
}

static char *date_more(char *buf) {
    char *res = mx_strnew(12);

    res[0] = buf[4];
    res[1] = buf[5];
    res[2] = buf[6];
    res[3] = ' ';
    res[4] = buf[8];
    res[5] = buf[9];
    res[6] = ' ';
    res[7] = ' ';
    res[8] = buf[20];
    res[9] = buf[21];
    res[10] = buf[22];
    res[11] = buf[23];
    return res;
}

char *mx_get_time(struct stat buf) {
    time_t time_f;
    char *buff = NULL;
    char *res = NULL;
    time_t current = time(NULL);
    time_t sec_in_six_month = 15778368;

    time_f = buf.st_mtimespec.tv_sec;
    buff = mx_strdup(ctime(&time_f));

    if ((current - sec_in_six_month) > time_f ||
        (current + sec_in_six_month) < time_f)
        res = date_more(buff);
    else
        res = date_less(buff);
    mx_strdel(&buff);
    return res;
}

char *mx_get_time_c(struct stat buf) {
    time_t time_f;
    char *buff = NULL;
    char *res = NULL;
    time_t current = time(NULL);
    time_t sec_in_six_month = 15778368;

    time_f = buf.st_ctimespec.tv_sec;
    buff = mx_strdup(ctime(&time_f));

    if ((current - sec_in_six_month) > time_f ||
        (current + sec_in_six_month) < time_f)
        res = date_more(buff);
    else
        res = date_less(buff);
    mx_strdel(&buff);
    return res;
}

char *mx_get_time_u(struct stat buf) {
    time_t time_f;
    char *buff = NULL;
    char *res = NULL;
    time_t current = time(NULL);
    time_t sec_in_six_month = 15778368;

    time_f = buf.st_atimespec.tv_sec;
    buff = mx_strdup(ctime(&time_f));

    if ((current - sec_in_six_month) > time_f ||
        (current + sec_in_six_month) < time_f)
        res = date_more(buff);
    else
        res = date_less(buff);
    mx_strdel(&buff);
    return res;
}

