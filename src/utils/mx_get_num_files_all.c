// Created by Karina Barinova on 09.09.2020.
//

#include <uls.h>

int mx_get_num_files_all(t_list *entities) {
    int sum = 0;

    while (entities != 0) {
        //t_dirent *entity = (t_dirent *)entities->data;

        // if (entity->name[0] != '.') {
        //     sum++;
        // }
        sum++;
        entities = entities->next;
    }
    //printf("sum of files is %d", sum);
    return sum;
} 
