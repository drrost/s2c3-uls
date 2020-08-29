#include <uls.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


// void print_columns(t_output *list, int width) {
// 	int full_len = 0;
// 	int shorter_len = 0;
// 	//int tab_size = 8;
// 	int double_space = 2;

// 	for (; list != NULL; list = list->next) {
// 		mx_printstr(list->name);
// 		len += mx_strlen(list->name) + double_space;
// 		if (list->next != NULL) {
// 			mx_printstr(", ");
// 			if (list->next->next != NULL)
// 				shorter_len = 3;
// 			else
// 				shorter_len = 1;
// 			if (full_len + shorter_len + mx_strlen(list->next->name) > width) {
// 				mx_printstr("\n");
// 				full_len = 0;
// 			}
// 		}
// 	}
// 	mx_printstr("\n");
// }

int get_window_size(void) {
	struct winsize win;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
	return win.ws_col;
}

// void check_width(t_output *list) {
// 	if (isatty(1))
// 		print_columns(list, get_window_size());
// 	else
// 		print_columns(list, 80);
// }
