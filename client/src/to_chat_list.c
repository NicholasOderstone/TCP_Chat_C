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
        printf("## chat_name: %s\tchat_id: %d\n", current->chat_name, current->chat_id);
        current = current->next;
    }
    printf("\n");
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
