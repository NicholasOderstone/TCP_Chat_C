#include "../inc/header.h"

void to_cmd_q(struct command data) {
    struct cmd_q *temp;
    static int counter = 0;
    temp = (struct cmd_q *)malloc(sizeof(struct cmd_q));
    temp->data.command = strdup(data.command);
    temp->data.params = strdup(data.params);
    temp->link = NULL;

    struct cmd_q *current = cmd_front;
    if (current == NULL) {
        current = temp;
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
}
