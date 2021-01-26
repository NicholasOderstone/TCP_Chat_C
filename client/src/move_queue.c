#include "../inc/header.h"

void move_msg_q(struct msg_q **msg_q_front, pthread_mutex_t msg_lock) {
    struct msg_q *temp;
    temp = *msg_q_front;
    pthread_mutex_lock(&msg_lock);
    if (*msg_q_front != NULL) {
        *msg_q_front = temp->link;
    }
    pthread_mutex_unlock(&msg_lock);
    free(temp);
}

void move_cmd_q(struct cmd_q **cmd_q_front) {
    struct cmd_q *temp;
    temp = *cmd_q_front;

    if (*cmd_q_front != NULL) {
        *cmd_q_front = temp->link;
    }
    free(temp);
}
