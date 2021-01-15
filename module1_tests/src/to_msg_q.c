#include "../inc/module_one.h"

void to_msg_q(char *data) {
    struct msg_q *temp;
    static int counter = 0;
    temp = (struct msg_q*)malloc(sizeof(struct msg_q));
    temp->data = strdup(data);
    temp->link = NULL;

    struct msg_q *current = msg_front;

    pthread_mutex_lock(&lock);
    if (msg_front == NULL) {
        current = msg_front = temp;
    }
    else {
        while (current->link != NULL) {
        current = current->link;
        }
        current->link = temp;
        current = current->link;
    }
    //pthread_mutex_lock(&print_lock);
    printf("%d: msg_q: %s\n", counter, current->data);
    //pthread_mutex_unlock(&print_lock);
    pthread_mutex_unlock(&lock);
    
    
    counter++;
}

char *take_fst_msg_in_q() {
    if (msg_front == NULL)
        return NULL;
    return msg_front->data;
}
