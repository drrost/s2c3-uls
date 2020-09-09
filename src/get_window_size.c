#include <uls.h>
#include <sys/ioctl.h>
#include <unistd.h>

int get_window_size(void) {
	struct winsize win;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
	return win.ws_col;
}
