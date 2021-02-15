#include "../inc/header.h"

void to_msg_id_q(received_messages *new_msg, msg_id_q **msg_id_q_head) {
    msg_id_q *temp;

    pthread_mutex_lock(&msg_id_lock);
    temp = (msg_id_q *)malloc(sizeof(msg_id_q));

    temp->msg_id = new_msg->msg_id;
    temp->chat_id = new_msg->chat_id;

    strcpy(temp->message, new_msg->message);
    strcpy(temp->sender_login, new_msg->sender_login);
    strcpy(temp->sender_name, new_msg->sender_name);
    strcpy(temp->time, new_msg->time);
    strcpy(temp->is_special, new_msg->is_special);
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
    //// printf("now in msg_id_q: %d\n", current->msg_id);
    pthread_mutex_unlock(&msg_id_lock);
    return;
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
        // printf("## msg_id: %d\n", current->msg_id);
        current = current->next;
    }
    // printf("\n");
}

int msg_id_q_size(msg_id_q **msg_id_q_head) {
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

int get_index_by_msg_id(msg_id_q **msg_id_q_head, int msg_id) {
    msg_id_q *current = *msg_id_q_head;
    int index = 0;
    while (current != NULL)
    {
        if (current->msg_id == msg_id) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

msg_id_q *get_msg_p_by_msg_id(msg_id_q **msg_id_q_head, int msg_id) {
    msg_id_q *current = *msg_id_q_head;
    while (current != NULL)
    {
        if (current->msg_id == msg_id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

msg_id_q *get_msg_p_by_msg_index(msg_id_q **msg_id_q_head, int index) {
    msg_id_q *current = *msg_id_q_head;
    int i = 0;
    while (current != NULL)
    {
        if (i == index) {
            return current;
        }
        current = current->next;
        i++;
    }
    return NULL;
}
