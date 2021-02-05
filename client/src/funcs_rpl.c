#include "../inc/header.h"

void func_rpl_login(char *params, void *p) {
    UNUSED(p);
    char *p_rpl = take_param(params, 1);
    if (strcmp(p_rpl, "ERROR") == 0) {
        if (strcmp(take_param(params, 2), "INCORRECT_LOGIN") == 0) {
            sw_login = 1;
        }
        else if (strcmp(take_param(params, 2), "INCORRECT_PASS") == 0) {
            sw_login = 2;
        }
    }
    else if (strcmp(p_rpl, "SUCCESS") == 0) {
        sw_login = 0;
    }
}

void func_rpl_register(char *params, void *p) {
    UNUSED(p);
    char *p_rpl = take_param(params, 1);
    if (strcmp(p_rpl, "ERROR") == 0) {
        if (strcmp(take_param(params, 2), "USERNAME_EXIST") == 0) {
            sw_register = 1;
        }
        else if (strcmp(take_param(params, 2), "PASS_NOT_MATCH") == 0) {
            sw_register = 2;
        }
    }
    else if (strcmp(p_rpl, "SUCCESS") == 0) {
        sw_register = 0;
    }
}

void func_rpl_send(char *params, void *p) {
    received_messages *received_mess = (received_messages *)malloc(sizeof(received_messages));
    client_t *client = (client_t *)p;
    received_mess->client = client;
    strcpy(received_mess->message, take_param(params, 5));
    strcpy(received_mess->time, take_param(params, 4));
    strcpy(received_mess->sender_name, take_param(params, 3));
    received_mess->msg_id = atoi(take_param(params, 2));
    received_mess->chat_id = atoi(take_param(params, 1));
    if (received_mess->chat_id == received_mess->client->active_chat_id)
        gdk_threads_add_idle(message_show, (gpointer)received_mess);
}

void func_rpl_delete(char *params, void *p) {
    client_t *client = (client_t *)p;
    GtkListBox *box = client->m->box_message;
    int msg_id = atoi(take_param(params, 1));
    int index = get_index_by_msg_id(&client->msg_id_q_head, msg_id);

    gtk_list_box_select_row(box, gtk_list_box_get_row_at_index(box, (gint)index));
    gtk_container_remove(GTK_CONTAINER(box), GTK_WIDGET(gtk_list_box_get_selected_row (box)));
    del_elem_msg_id_q(&client->msg_id_q_head, msg_id);
    printf("## index in rpl_delete: %d\n", index);
}

void func_rpl_edit(char *params, void *p) {
    UNUSED(p);

    printf("## edit params: %s\n", params);
}

void func_rpl_add_chat(char *params, void *p) {
    client_t *client = (client_t *)p;
    int p_id = atoi(take_param(params, 1));
    char *p_name = take_param(params, 2);
    if (p_id == -1) {
        return;
    }
    if (!is_chat_exists(&client->chat_list_head, p_id)) {
        to_chat_list(p_id, p_name, &client->chat_list_head);
    }
    /*int chat_list_sz = chat_list_size(&client->chat_list_head);
    printf("## chat_list_size: %d\n", chat_list_sz);
    int i = 0;


    GtkWidget **chat = malloc(chat_list_sz * sizeof(GtkWidget *));
    chat_info_t *current = client->chat_list_head;


    while (gtk_list_box_get_row_at_index(box1, (gint)0) != NULL)
    {
        gtk_container_remove(GTK_CONTAINER(box1), GTK_WIDGET(gtk_list_box_get_row_at_index(box1, (gint)0)));
    }



    i = 0;
    current = client->chat_list_head;

    while (current != NULL)
    {
        get_messages_request_s *get_messages_request = (get_messages_request_s *)malloc(sizeof(get_messages_request_s));
        chat[i] = gtk_button_new_with_label(current->chat_name);
        gtk_widget_show(GTK_WIDGET(chat[i]));
        gtk_list_box_insert(box1, GTK_WIDGET(chat[i]), -1);
        get_messages_request->chat = current;
        get_messages_request->client = client;
        get_messages_request_s *get_msg_buf = get_messages_request;
        g_signal_connect(chat[i], "clicked", G_CALLBACK(get_msg_request), (gpointer)get_msg_buf);

        current = current->next;
        i++;
    }*/
    display_chat_list(&client->chat_list_head);
}


void init_funcs(cmd_func arr_cmd_func[]) {
    char *arr_func_names[AMOUNT_OF_CMD] = { "<LOGIN>", "<REGISTER>", "<SEND>",
                                            "<ADD_CHAT>", "<DELETE_MSG>", "EDIT_MSG"};

    arr_cmd_func[0].func = &func_rpl_login;
    arr_cmd_func[1].func = &func_rpl_register;
    arr_cmd_func[2].func = &func_rpl_send;
    arr_cmd_func[3].func = &func_rpl_add_chat;
    arr_cmd_func[4].func = &func_rpl_delete;
    arr_cmd_func[5].func = &func_rpl_edit;

    for (int i = 0; i < AMOUNT_OF_CMD; i++)
        arr_cmd_func[i].name = strdup(arr_func_names[i]);
}

void init_switches(void) {
    sw_login = -1;
    sw_register = -1;
}
