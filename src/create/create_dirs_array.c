#include <uls.h>

t_dir **mx_create_dirs_array(unsigned int size) {
    t_dir **array = NULL;

    if (size <= 0)
        return NULL;
    array = (t_dir **)malloc(sizeof(t_dir *) * (size + 1));
    for (unsigned int i = 0; i <= size; i++) {
        array[i] = NULL;
    }
    return array;
}
