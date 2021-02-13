#include "../inc/header.h"

void swap_chats(chat_info_t *chat1,chat_info_t *chat2) {
    int temp_id = chat1->chat_id;
    chat1->chat_id = chat2->chat_id;
    chat2->chat_id = temp_id;

    char *temp = chat1->chat_name;
    chat1->chat_name = chat2->chat_name;
    chat2->chat_name = temp;

    int temp_l = chat1->last_msg_time;
    chat1->last_msg_time = chat2->last_msg_time;
    chat2->last_msg_time = temp_l;

    int temp_f = chat1->f_unread_msg_id;
    chat1->f_unread_msg_id = chat2->f_unread_msg_id;
    chat2->f_unread_msg_id = temp_f;
}

void sort_listbox(chat_info_t **chat_list_head, client_t *client) {
    int i, j;
    for (i = 0; i < chat_list_size(chat_list_head) - 1; i++) {
        for (j = 0; j < chat_list_size(chat_list_head) - i - 1; j++) {
            chat_info_t *chat1 = get_chat_p_by_index(chat_list_head, j);
            chat_info_t *chat2 = get_chat_p_by_index(chat_list_head, j + 1);
            if (chat1->last_msg_time < chat2->last_msg_time)
              swap_chats(chat1, chat2);
        }
    }
    display_chat_list(chat_list_head);
    int size = chat_list_size(chat_list_head);
    for (int index = 0; index < size; index++) {
        gtk_list_box_select_row(client->m->box_chat_list, gtk_list_box_get_row_at_index(client->m->box_chat_list, (gint)0));
        gtk_container_remove(GTK_CONTAINER(client->m->box_chat_list), GTK_WIDGET(gtk_list_box_get_selected_row (client->m->box_chat_list)));
    }
    for (int index = 0; index < size; index++) {
        chat_info_t *chat = get_chat_p_by_index(chat_list_head, index);
        client->m->chat[index] = gtk_button_new_with_label(chat->chat_name);
        gtk_container_add(GTK_CONTAINER(client->m->box_chat_list), GTK_WIDGET(client->m->chat[index]));
        gtk_widget_show(GTK_WIDGET(client->m->chat[index]));

        client->m->unread_b_images[index] = gtk_image_new_from_file("client/resources/new_msg.png");

        gtk_button_set_image(GTK_BUTTON(client->m->chat[index]), client->m->unread_b_images[index]);
        gtk_button_set_image_position(GTK_BUTTON(client->m->chat[index]), GTK_POS_RIGHT);

        if (chat->last_msg_time != -1 && chat->f_unread_msg_id != -1) {
            gtk_widget_show(client->m->unread_b_images[index]);
        }
        else {
            gtk_widget_hide(client->m->unread_b_images[index]);
        }

        get_messages_request_s *get_messages_request = (get_messages_request_s *)malloc(sizeof(get_messages_request_s));
        get_messages_request->chat = chat;
        get_messages_request->client = client;
        // get_messages_request_s *get_msg_buf = (get_messages_request_s *)malloc(sizeof(get_messages_request_s));
        get_messages_request_s *get_msg_buf = get_messages_request;

        gtk_widget_set_name(GTK_WIDGET(client->m->chat[index]), "chat_b");
        g_signal_connect(client->m->chat[index], "clicked", G_CALLBACK(get_msg_request), (gpointer)get_msg_buf);
    }
}
