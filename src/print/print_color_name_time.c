#include <uls.h>

static void print_uname_gr_size(t_file *file, t_flags *flags, t_out *out) {
  if (flags->f_g == 0)
    mx_right_alt(file->username, out->count_uname);
  if (flags->f_o == 0)
    mx_right_alt(file->gr ? file->gr : out->gid, out->count_group);
  if (file->driver)
    mx_left_aligment(file->driver->driver, out->count_size);
  else
    mx_left_aligment(out->size, out->count_size);
}

static void print_time(t_file *file, time_t this_time, t_flags *flags) {
  mx_printchar(' ');
  mx_printstr(file->time->mmdd);
  mx_printchar(' ');
  if (flags->f_T) {
    mx_printstr(file->time->time);
    mx_printchar(' ');
    mx_printstr(file->time->year);
  }
  else if (file->time->r_time <= (this_time - 15724800)
	   || file->time->r_time >= this_time) {
    mx_printchar(' ');
    mx_printstr(file->time->year);
  }
  else 
    mx_printstr(file->time->time);
  mx_printchar(' ');
}

void mx_print_time_name_color(t_file *file, time_t this_time,
                              t_flags *flags, t_out *out) {
  print_uname_gr_size(file, flags, out);
  print_time(file, this_time, flags);
  for (int i = 0; file->name[i]; i++) {
    if (file->name[i] >= 0 && file->name[i] <= 31
	&& (isatty(1) != 0 || flags->f_q == 1)) {
      file->name[i] = '?';
    }
  }
  if (flags->f_G && isatty(1) != 0) {
    mx_change_color(mx_acl_strcol(file->acl), mx_acl_bkcol(file->acl));
    mx_printstr(file->name);
    mx_color_reset();
  }
  else
    mx_printstr(file->name);
  if (file->link != NULL) {
    mx_printstr(" -> ");
    mx_printstr(file->link);
  }
  mx_printstr("\n");
}
