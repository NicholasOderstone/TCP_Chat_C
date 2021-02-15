#include "../inc/header.h"

void to_chat_list(int chat_id, char *chat_name, chat_info_t **chat_list_head) {
    chat_info_t *temp;

    temp = (chat_info_t *)malloc(sizeof(chat_info_t));
    temp->chat_id = chat_id;
    temp->chat_name = strdup(chat_name);
    temp->next = NULL;

    pthread_mutex_lock(&chat_lock);
    chat_info_t *current = *chat_list_head;
    if (*chat_list_head == NULL) {
        *chat_list_head = temp;
        current = *chat_list_head;
    }
    else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = temp;
    }
    //printf("now in chat_list: %s", current->chat_name);
    //printf("\tid: %d\n", current->chat_id);
    pthread_mutex_unlock(&chat_lock);
}

void display_chat_list(chat_info_t **chat_list_head) {
    chat_info_t *current = *chat_list_head;
    while (current != NULL)
    {
        printf("  ## n: %s\tc_id: %d\t m_id: %d\tt: %d\n", current->chat_name, current->chat_id, current->f_unread_msg_id, (int)current->last_msg_time);
        current = current->next;
    }
    printf("\n");
}

void del_elem_chat_list(chat_info_t **chat_list_head, int chat_id) {
    chat_info_t *temp = *chat_list_head;
    chat_info_t *prev_elem = NULL;
    if (temp != NULL && temp->chat_id == chat_id) {
        *chat_list_head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->chat_id != chat_id) {
        prev_elem = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        return;
    }
    prev_elem->next = temp->next;
    free(temp);
    //printf(" !! chat with chat_id %d deleted\n", chat_id);
    return;
}

int chat_list_size(chat_info_t **chat_list_head) {
    chat_info_t *current = *chat_list_head;
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

int is_chat_exists(chat_info_t **chat_list_head, int chat_id) {
    chat_info_t *current = *chat_list_head;
    while (current != NULL)
    {
        if (current->chat_id == chat_id) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int get_index_by_chat_id(chat_info_t **chat_list_head, int chat_id) {
    chat_info_t *current = *chat_list_head;
    int index = 0;
    while (current != NULL)
    {
        if (current->chat_id == chat_id) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

chat_info_t *get_chat_p_by_chat_id(chat_info_t **chat_list_head, int chat_id) {
    chat_info_t *current = (chat_info_t *)malloc(sizeof(chat_info_t));
    current = *chat_list_head;
    while (current != NULL)
    {
        if (current->chat_id == chat_id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

chat_info_t *get_chat_p_by_index(chat_info_t **chat_list_head, int index) {
    chat_info_t *current = (chat_info_t *)malloc(sizeof(chat_info_t));
    current = *chat_list_head;
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
