#include "../inc/module_one.h"

void move_msg_q() {
    struct msg_q_elem *temp;
    temp = message_q.front;

    if (message_q.front == NULL) {
        printf("Queue underflow\n");
        message_q.front = message_q.rear = NULL;
    }
    else {
        printf("The deleted element from the queue is: %s\n", message_q.front->data);
        message_q.front = message_q.front->link;
        free(temp);
    }
}
