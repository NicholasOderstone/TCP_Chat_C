#include "../inc/module_one.h"

void move_msg_q() {
    struct msg_q *temp;
    temp = msg_front;

    if (msg_front == NULL) {
        printf("Queue underflow\n");
        msg_front = msg_rear = NULL;
    }
    else {
        printf("The deleted element from the queue is: %s\n", msg_front->data);
        msg_front = msg_front->link;
        free(temp);
    }
}
