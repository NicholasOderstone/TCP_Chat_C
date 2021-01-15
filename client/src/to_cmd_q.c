#include "../inc/header.h"

void to_cmd_q(struct command data) {
    struct cmd_q *temp;
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

    printf("\tnow in cmd_q: command = %s", data.command);
    printf("; params = %s\n", data.params);
    str_overwrite_stdout();
}
