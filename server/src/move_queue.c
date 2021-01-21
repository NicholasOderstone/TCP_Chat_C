#include "../inc/header.h"

void move_cmd_q(struct cmd_q **cmd_q_front) {
    struct cmd_q *temp;
    temp = *cmd_q_front;
    pthread_mutex_lock(&cmd_lock);
    if (*cmd_q_front != NULL) {
        *cmd_q_front = temp->link;
    }
    free(temp);
    pthread_mutex_unlock(&cmd_lock);
}
