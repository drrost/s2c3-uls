#include <uls.h>
#include <stdlib.h>

t_file **mx_create_files_array(unsigned int size) {
    t_file **array = NULL;

    if (size <= 0)
        return NULL;
    array = (t_file **)malloc(sizeof(t_file *) * (size + 1));
    for (unsigned int i = 0; i <= size; i++) {
        array[i] = NULL;
    }
    return array;
}
