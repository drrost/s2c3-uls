#include <uls.h>

static char *strjoin_path_free(char *s, const char c) {
    char *join = NULL;
    int i = 0;

    join = mx_strnew(1 + mx_unicode_strlen(s));
        join[i] = c;
        i++;
    for (int j = 0; j < mx_unicode_strlen(s); j++, i++)
        join[i] = s[j];
    join[i] = '\0';
    // mx_strdel(&s);
    return join;
}

char *mx_strjoin_path(char *s1, char *s2, const char c) {
    char *join = NULL;
    int i = 0;

    if (s2 == NULL)
        return NULL;
    else if (s1 == NULL)
        join = strjoin_path_free(s2, c);
    else {
        join = mx_strnew(1 + mx_unicode_strlen(s1) + mx_unicode_strlen(s2));
        for (i = 0; i < mx_unicode_strlen(s1); i++)
            join[i] = s1[i];
        join[i] = c;
            i++;
        for (int j = 0; j < mx_unicode_strlen(s2); j++, i++)
            join[i] = s2[j];
        join[i] = '\0';
    }
    return join;
}
