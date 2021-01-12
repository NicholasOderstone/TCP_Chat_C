#include "../inc/module_one.h"

void to_cmd_q(struct command data) {
    struct cmd_q_elem *temp;
    temp = (struct cmd_q_elem *)malloc(sizeof(struct cmd_q_elem));
    temp->data.command = strdup(data.command);
    temp->data.params = strdup(data.params);
    temp->link = NULL;

    if (command_q.rear == NULL)
        command_q.front = command_q.rear = temp;
    else {
        command_q.rear->link = temp;
        command_q.rear = temp;
    }
    printf("Element inserted in cmd_q: %s\n", data.command);
}
