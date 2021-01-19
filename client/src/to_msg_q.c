#include "../inc/header.h"

void to_msg_q(char *data, struct msg_q **msg_q_front) {
    struct msg_q *temp;
    temp = (struct msg_q*)malloc(sizeof(struct msg_q));
    temp->data = strdup(data);
    temp->link = NULL;

    struct msg_q *current = *msg_q_front;

    pthread_mutex_lock(&lock);
    if (*msg_q_front == NULL) {
        *msg_q_front = temp;
        current = *msg_q_front;
    }
    else {
        while (current->link != NULL) {
        current = current->link;
        }
        current->link = temp;
    }
    printf("to_msg_q msg_q_front addr: %p\n", (void *)*msg_q_front);
    printf("now in msg_q: %s", current->data);
    //printf("\tmsg_q_front: %s\n", *(&msg_q_front->data));
    //str_overwrite_stdout();
    pthread_mutex_unlock(&lock);
}

char *take_fst_msg_in_q(struct msg_q **msg_q_front) {
    if (*msg_q_front == NULL)
        return NULL;
    struct msg_q *temp = *msg_q_front;
    return temp->data;
}
