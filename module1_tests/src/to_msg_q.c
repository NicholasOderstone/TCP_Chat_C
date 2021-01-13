#include "../inc/module_one.h"

void to_msg_q(char *data) {
    struct msg_q *temp;
    temp = (struct msg_q*)malloc(sizeof(struct msg_q));
    temp->data = strdup(data);
    temp->link = NULL;

    if (msg_rear == NULL)
        msg_front = msg_rear = temp;
    else {
        msg_rear->link = temp;
        msg_rear = temp;
    }
    printf("Element inserted in msg_q: %s\n", data);
}

char *take_fst_msg_in_q() {
    return msg_front->data;
}
