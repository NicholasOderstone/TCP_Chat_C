#include "../inc/header.h"

// ---- CHAT_MSG ----
void get_msg_request(GtkWidget *widget, gpointer data) {
    UNUSED(widget);
    gtk_widget_set_sensitive (GTK_WIDGET(chat_lbl), TRUE);
    get_messages_request_s *get_messages_r = (get_messages_request_s *)data;
    if (get_messages_r->client->active_chat_id != get_messages_r->chat->chat_id) {
        get_messages_r->chat->f_unread_msg_id = -1;
        time_t time = (time_t)get_messages_r->chat->last_msg_time;
        struct tm *ptm = localtime(&time);
        if (ptm == NULL) {
            puts("The localtime() function failed");
            return;
        }

        char last_msg_time_buf[BUFFER_SZ];
        snprintf(last_msg_time_buf, BUFFER_SZ, "%s  %02d:%02d unread_msg_id: %d", get_messages_r->chat->chat_name, ptm->tm_hour, ptm->tm_min, get_messages_r->chat->f_unread_msg_id);

        int chat_index = get_index_by_chat_id(&get_messages_r->client->chat_list_head, get_messages_r->chat->chat_id);
        gtk_button_set_label(GTK_BUTTON(get_messages_r->client->m->chat[chat_index]), last_msg_time_buf);

    	get_messages_r->client->active_chat_id = get_messages_r->chat->chat_id;
        gtk_button_set_label(chat_lbl, get_messages_r->chat->chat_name);
        gtk_label_set_text (chat_label, get_messages_r->chat->chat_name);
    	command cmd;
    	char buffer[BUFFER_SZ];
    	snprintf(buffer, BUFFER_SZ, "<%d>", get_messages_r->chat->chat_id);
    	cmd.command = "<CHAT_MSG>";
    	cmd.params = strdup(buffer);
    	send_cmd(cmd, get_messages_r->client);
    	bzero(buffer, BUFFER_SZ);
        while (clean_listbox((gpointer)get_messages_r->client->m->box_message) == TRUE) {}
        clear_msg_id_q(&get_messages_r->client->msg_id_q_head);
        get_messages_r->client->m->row_num_list_gtk = -1;
    }
}

// ---- NEW_CHAT ----
void new_chat_request(GtkWidget *widget, gpointer data) {
    UNUSED(widget);
    gtk_widget_hide (chat_name_d);
    new_chat_request_s *new_chat_r = (new_chat_request_s *)data;
    static int counter = 0;
    printf("index new_chat_request: %d\n", counter);
    counter++;
	command cmd;
	char buffer[BUFFER_SZ];
    new_chat_r->new_chat_name = mx_strnew(strlen(chatname_str));
    strcpy(new_chat_r->new_chat_name, chatname_str);
    snprintf(buffer, BUFFER_SZ, "<%s>", new_chat_r->new_chat_name);
	cmd.command = "<NEW_CHAT>";
	cmd.params = strdup(buffer);
	send_cmd(cmd, new_chat_r->client);
	bzero(buffer, BUFFER_SZ);
}

// ---- DELETE_MSG ----
void delete_msg_request(del_msg_request_s *delete_msg_r) {
	command cmd;
	char buffer[BUFFER_SZ];
	snprintf(buffer, BUFFER_SZ, "<%d> <%d>", delete_msg_r->msg_id, delete_msg_r->chat_id);
	cmd.command = "<DELETE_MSG>";
	cmd.params = strdup(buffer);
	send_cmd(cmd, delete_msg_r->client);
	bzero(buffer, BUFFER_SZ);
}

// ---- LEAVE_CHAT ----
void leave_chat_request(GtkWidget *widget, gpointer data) {
    UNUSED(widget);
    gtk_widget_hide(chat_menu_wind);
	command cmd;
	char buffer[BUFFER_SZ];
    del_chat_request_s *leave_chat_r = (del_chat_request_s *)data;
    printf("leave_chat_r->chat_id %d\n", leave_chat_r->client->active_chat_id);
    snprintf(buffer, BUFFER_SZ, "<%d>", leave_chat_r->client->active_chat_id);
    cmd.command = "<LEAVE_CHAT>";
    cmd.params = strdup(buffer);
    send_cmd(cmd, leave_chat_r->client);
    bzero(buffer, BUFFER_SZ);
}

// ---- EDIT_MSG ----
void edit_msg_request(GtkWidget *widget, gpointer data) {
    UNUSED(widget);
	command cmd;
	char buffer[BUFFER_SZ];

    gint index;
    client_t *client = (client_t *)data;
    GTK_WIDGET(gtk_list_box_get_selected_row (client->m->box_message));

    index = gtk_list_box_row_get_index(gtk_list_box_get_selected_row (client->m->box_message));

    msg_id_q *current = client->msg_id_q_head;

    while (index) {
        current = current->next;
        index--;
    }
    printf("edited: msd_id -- %d\n", current->msg_id);

    edit_msg_request_s *edit_msg = (edit_msg_request_s *)malloc(sizeof(edit_msg_request_s));
    edit_msg->msg_id = current->msg_id;
    edit_msg->client = client;
    //edit_msg_request(edit_msg);

    gtk_list_box_unselect_all(client->m->box_message);

    edit_msg->new_text = strdup(message_str);
    printf("edit_msg->new_text %s", edit_msg->new_text);

	snprintf(buffer, BUFFER_SZ, "<%d> <%d> <%s>", edit_msg->msg_id, edit_msg->client->active_chat_id, edit_msg->new_text);
	cmd.command = "<EDIT_MSG>";
	cmd.params = strdup(buffer);
	send_cmd(cmd, edit_msg->client);
	bzero(buffer, BUFFER_SZ);
    gtk_entry_set_placeholder_text(GTK_ENTRY(message_entry), "");
    gtk_widget_hide(GTK_WIDGET(edit_b));
    gtk_widget_set_sensitive (GTK_WIDGET(chat_lbl), TRUE);
    message_clear();
}

// ---- ADD_USER_TO_CHAT ----
void add_user_to_chat_request(GtkWidget *widget, gpointer data) {
    UNUSED(widget);
    gtk_widget_hide(add_memwind);
    command cmd;
    char buffer[BUFFER_SZ];
    client_t *client = (client_t *)data;

    snprintf(buffer, BUFFER_SZ, "<%d> <%s>", client->active_chat_id, user_searh_str);
    cmd.command = "<ADD_USER_TO_CHAT>";
    cmd.params = strdup(buffer);
    send_cmd(cmd, client);
    bzero(buffer, BUFFER_SZ);
}
