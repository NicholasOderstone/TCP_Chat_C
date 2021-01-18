#include "../inc/header.h"

void move_msg_q() {
    struct msg_q *temp;
    temp = msg_front;
    pthread_mutex_lock(&lock);
    if (msg_front != NULL) {
        msg_front = msg_front->link;
    }  
    pthread_mutex_unlock(&lock);
    free(temp);
}

void move_cmd_q() {
    struct cmd_q *temp;
    temp = cmd_front;
    pthread_mutex_lock(&lock);
    if (cmd_front != NULL) {
        cmd_front = cmd_front->link;
    }  
    pthread_mutex_unlock(&lock);
    free(temp);
}
