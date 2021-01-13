#include "../inc/module_one.h"

void to_msg_q(char *data) {
    struct msg_q *temp;
    static int counter = 0;
    temp = (struct msg_q*)malloc(sizeof(struct msg_q));
    temp->data = strdup(data);
    temp->link = NULL;

    pthread_mutex_lock(&lock);
    if (msg_rear == NULL) {
        msg_front = msg_rear = temp;
    }
    else {
        msg_rear->link = temp;
        msg_rear = temp;
    }
    pthread_mutex_unlock(&lock);

    printf("%d: msg_q: %s\n", counter, data);
    counter++;
}

char *take_fst_msg_in_q() {
    if (msg_front == NULL)
        return NULL;
    return msg_front->data;
}
