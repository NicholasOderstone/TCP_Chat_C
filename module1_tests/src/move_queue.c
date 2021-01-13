#include "../inc/module_one.h"

void move_msg_q() {
    struct msg_q *temp;
    temp = msg_front;
    pthread_mutex_lock(&lock);
    if (msg_front == NULL)
        msg_front = msg_rear = NULL;
    else
        msg_front = msg_front->link;
    pthread_mutex_unlock(&lock);
    free(temp);
}
