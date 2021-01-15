#include "../inc/header.h"

void to_msg_q(char *data) {
    struct msg_q *temp;
    temp = (struct msg_q*)malloc(sizeof(struct msg_q));
    temp->data = strdup(data);
    temp->link = NULL;

    struct msg_q *current = msg_front;

    pthread_mutex_lock(&lock);
    if (msg_front == NULL) {
        current = msg_front = temp;
    }
    else {
        while (current->link != NULL) {
        current = current->link;
        }
        current->link = temp;
        current = current->link;
    }
    
    printf("now in msg_q: %s", current->data);
    str_overwrite_stdout();
    pthread_mutex_unlock(&lock);
}

char *take_fst_msg_in_q() {
    if (msg_front == NULL)
        return NULL;
    return msg_front->data;
}
