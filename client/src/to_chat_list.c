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

void display(chat_info_t **chat_list_head) {
    chat_info_t *current = *chat_list_head;
    while (current != NULL)
    {
        printf("## chat_name: %s\n", current->chat_name);
        current = current->next;
    }
    printf("\n");
}
