#include "../inc/module_one.h"

void to_msg_q(char *data) {
    struct msg_q_elem *temp;
    temp = (struct msg_q_elem*)malloc(sizeof(struct msg_q_elem));
    temp->data = strdup(data);
    temp->link = NULL;

    if (message_q.rear == NULL)
        message_q.front = message_q.rear = temp;
    else {
        message_q.rear->link = temp;
        message_q.rear = temp;
    }
    printf("Element inserted in msg_q: %s\n", data);
}

void display()
{
    struct msg_q_elem *temp;
    temp = message_q.front;
    int cnt = 0;

    if (message_q.front == NULL)
        printf("Queue underflow\n");
    else {
        printf("The elements of the stack are:\n");
        while (temp) {
            printf("%s\n", temp->data);
            temp = temp->link;
            cnt++;
        }
    }
}

char *take_fst_msg_in_q() {
    return message_q.front->data;
}
