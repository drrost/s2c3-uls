#include <uls.h>

t_driver *mx_create_driver() {
    t_driver *driver = (t_driver *)malloc(sizeof(t_driver));

    driver->driver = NULL;
    driver->size = 0;
    return driver;
}
