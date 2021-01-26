#include "../inc/header.h"

void to_cmd_q(command data, struct cmd_q **cmd_q_front, pthread_mutex_t cmd_lock) {
    struct cmd_q *temp;
    temp = (struct cmd_q *)malloc(sizeof(struct cmd_q));
    temp->data.command = strdup(data.command);
    temp->data.params = strdup(data.params);
    temp->link = NULL;

    pthread_mutex_lock(&cmd_lock);
    struct cmd_q *current = *cmd_q_front;
    if (*cmd_q_front == NULL) {
        *cmd_q_front = temp;
        current = *cmd_q_front;
    }
    else {
        while (current->link != NULL) {
        current = current->link;
        }
        current->link = temp;
    }
    printf("cmd: %s; params: %s", data.command, data.params);
    pthread_mutex_unlock(&cmd_lock);
}

command take_fst_cmd_in_q(struct cmd_q **cmd_q_front) {
    struct cmd_q *temp = *cmd_q_front;
    return temp->data;
}
