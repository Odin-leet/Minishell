#include <stdio.h>
struct dt{
    char *str;

};

t_liked_list {
    void *data;
    t_linked-list *next;
}

void free_head(t_linked_list *head) {
    if (head == NULL)
        return;
    free_head(head->next);
    free((dt *)(head->data)->str);
    free(head->data);
    free(head);
}