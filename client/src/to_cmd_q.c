#include "../inc/header.h"

void to_cmd_q(command data, struct cmd_q **cmd_q_front) {
    struct cmd_q *temp;
    temp = (struct cmd_q *)malloc(sizeof(struct cmd_q));
    temp->data.command = strdup(data.command);
    temp->data.params = strdup(data.params);
    temp->link = NULL;

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

    //printf("\tnow in cmd_q: command = %s", data.command);
    //printf("; params = %s\n", data.params);
    printf("to_cmd_q cmd_q_front addr: %p\n", (void *)*cmd_q_front);
    printf("cmd: %s; params: %s", data.command, data.params);

    //printf("\nCMD_Q_FRONT cmd: %s; params: %s", *cmd_q_front->data.command, *cmd_q_front->data.params);

    str_overwrite_stdout();
}

command take_fst_cmd_in_q(struct cmd_q **cmd_q_front) {
    struct cmd_q *temp = *cmd_q_front;
    return temp->data;
}
