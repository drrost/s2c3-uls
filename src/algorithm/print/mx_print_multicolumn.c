//
// Created by Karina Barinova on 10.09.2020.
//

#include <uls.h>

// static void reorder(t_list **list) {
//     t_list *head = 0;
//     t_list *tail = 0;
//     t_list *work = *list;

//     int i = 0;
//     while (work) {
//         if (i % 2 == 0)
//             mx_push_back(&head, work->data);
//         else
//             mx_push_back(&tail, work->data);
//         i++;
//         work = work->next;
//     }

//     mx_list_attach_back(&head, tail);
//     *list = head;
// }

void mx_print_multicolumn(t_list *entities, const char *delim) {
    int longest = mx_get_maxlen(entities);
    int files_count = mx_list_size(entities);
    int lines = mx_lines_count(files_count, longest);

    //reorder(&entities);

    for (int i = 0; i < lines; i++)
        for (int j = 0; j < files_count; j++)
            if (j == i || (j - i) % lines == 0) {
                mx_printstr(mx_find_index(entities, j));
                if (j + lines >= files_count)
                    mx_printstr("\n");
                else
                    mx_count_spaces(entities, longest, j, delim);
            }
}
