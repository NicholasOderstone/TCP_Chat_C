#include "../inc/header.h"

void to_msg_q(char *data, struct msg_q **msg_q_front, pthread_mutex_t msg_lock) {
    struct msg_q *temp;
    temp = (struct msg_q*)malloc(sizeof(struct msg_q));
    temp->data = strdup(data);
    temp->link = NULL;

    pthread_mutex_lock(&msg_lock);
    struct msg_q *current = *msg_q_front;
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
    //// printf("now in msg_q: %s", current->data);
    pthread_mutex_unlock(&msg_lock);
}

char *take_fst_msg_in_q(struct msg_q **msg_q_front) {
    if (*msg_q_front == NULL)
        return NULL;
    struct msg_q *temp = *msg_q_front;
    return temp->data;
}
