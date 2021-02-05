#include "../inc/header.h"

void to_msg_id_q(int msg_id, msg_id_q **msg_id_q_head) {
    msg_id_q *temp;

    pthread_mutex_lock(&msg_id_lock);
    temp = (msg_id_q *)malloc(sizeof(msg_id_q));
    temp->msg_id = msg_id;
    temp->next = NULL;

    msg_id_q *current = *msg_id_q_head;
    if (*msg_id_q_head == NULL) {
        *msg_id_q_head = temp;
        current = *msg_id_q_head;
    }
    else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = temp;
    }
    //printf("now in msg_id_q: %d\n", current->msg_id);
    pthread_mutex_unlock(&msg_id_lock);
}

void clear_msg_id_q(msg_id_q **msg_id_q_head) {
    while (*msg_id_q_head != NULL) {
        msg_id_q *temp;
        temp = *msg_id_q_head;
        *msg_id_q_head = temp->next;
        free(temp);
    }
}

void del_elem_msg_id_q(msg_id_q **msg_id_q_head, int msg_id){
    msg_id_q *temp = *msg_id_q_head;
    msg_id_q *prev_elem = NULL;
    if (temp != NULL && temp->msg_id == msg_id) {
        *msg_id_q_head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->msg_id != msg_id) {
        prev_elem = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        return;
    }
    prev_elem->next = temp->next;
    free(temp);
    return;
}

void display_msg_id_q(msg_id_q **msg_id_q_head) {
    msg_id_q *current = *msg_id_q_head;
    while (current != NULL)
    {
        printf("## msg_id: %d\n", current->msg_id);
        current = current->next;
    }
    printf("\n");
}

/*int chat_list_size(msg_id_q **msg_id_q_head) {
    msg_id_q *current = *msg_id_q_head;
    int size = 0;
    if (current == NULL) {
        return 0;
    }
    while (current != NULL)
    {
        current = current->next;
        size++;
    }
    return size;
}
*/
