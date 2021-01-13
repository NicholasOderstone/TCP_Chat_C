#include "../inc/module_one.h"

void to_cmd_q(struct command data) {
    struct cmd_q *temp;
    static int counter = 0;
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
    printf("\t%d: cmd_q: command = %s", counter, data.command);
    printf("; params = %s\n", data.params);
    counter++;
}
