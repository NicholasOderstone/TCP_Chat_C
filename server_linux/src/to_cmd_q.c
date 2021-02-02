#include "../inc/header.h"

void to_cmd_q(struct command data, struct cmd_q **cmd_q_front) {
    struct cmd_q *temp;
    static int counter = 0;
    temp = (struct cmd_q *)malloc(sizeof(struct cmd_q));
    temp->data.command = strdup(data.command);
    temp->data.params = strdup(data.params);
    temp->link = NULL;

    struct cmd_q *current = *cmd_q_front;
    pthread_mutex_lock(&cmd_lock);
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
    printf("\t%d: cmd_q: command = %s", counter, data.command);
    printf("; params = %s\n", data.params);
    counter++;
    pthread_mutex_unlock(&cmd_lock);
}

struct command take_fst_cmd_in_q(struct cmd_q **cmd_q_front) {
    struct cmd_q *temp = *cmd_q_front;
    return temp->data;
}
