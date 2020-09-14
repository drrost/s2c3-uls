#include <uls.h>

void check_leaks();

int main(int argc, char *argv[]) {
    t_algorithm *algorithm = mx_parse_arguments(argc, argv);
    mx_run_algorithm(algorithm);
    mx_algorithm_del(&algorithm);

    check_leaks();
    return 0;
}
