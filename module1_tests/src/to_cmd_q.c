#include "../inc/module_one.h"

void to_cmd_q(struct command data) {
    struct cmd_q *temp;
    temp = (struct cmd_q *)malloc(sizeof(struct cmd_q));
    temp->data.command = strdup(data.command);
    temp->data.params = strdup(data.params);
    temp->link = NULL;

    if (cmd_rear == NULL)
        cmd_front = cmd_rear = temp;
    else {
        cmd_rear->link = temp;
        cmd_rear = temp;
    }
    printf("Element inserted in cmd_q: %s\n", data.command);
}
