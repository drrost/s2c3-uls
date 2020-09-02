#include <uls.h>

void mx_left_s_aligment(char *str, int count) {
  int len = mx_unicode_strlen(str);

  if (len == count) {
    mx_printstr(str);
  }
  else {
    for (int i = count - len; i > 0; i--)
      mx_printchar(' ');
    mx_printstr(str);
  }
}
