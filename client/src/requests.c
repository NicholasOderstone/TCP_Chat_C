#include "../inc/header.h"

void get_msg_request(GtkWidget *widget, gpointer data) {
    UNUSED(widget);
    get_messages_request_s *get_messages_request = (get_messages_request_s *)data;
    if (get_messages_request->client->active_chat_id != get_messages_request->chat->chat_id) {
    	get_messages_request->client->active_chat_id = get_messages_request->chat->chat_id;
        gtk_button_set_label(chat_lbl, get_messages_request->chat->chat_name);
        gtk_label_set_text (chat_label, get_messages_request->chat->chat_name);
    	command cmd;
    	char buffer[BUFFER_SZ];
    	snprintf(buffer, BUFFER_SZ, "<%d>", get_messages_request->chat->chat_id);
    	cmd.command = "<CHAT_MSG>";
    	cmd.params = strdup(buffer);
    	send_cmd(cmd, get_messages_request->client);
    	bzero(buffer, BUFFER_SZ);
        while (clean_listbox((gpointer)get_messages_request->client->m->box_message) == TRUE) {}
        clear_msg_id_q(&get_messages_request->client->msg_id_q_head);
        get_messages_request->client->m->row_num_list_gtk = -1;
    }
}

void new_chat_request(GtkWidget *widget, gpointer data) {
    UNUSED(widget);
    gtk_widget_hide (chat_name_d);
    new_chat_request_s *new_chat_request = (new_chat_request_s *)data;
    static int counter = 0;
    printf("index new_chat_request: %d\n", counter);
    counter++;
	command cmd;
	char buffer[BUFFER_SZ];
    new_chat_request->new_chat_name = mx_strnew(strlen(chatname_str));
    strcpy(new_chat_request->new_chat_name, chatname_str);
    snprintf(buffer, BUFFER_SZ, "<%s>", new_chat_request->new_chat_name);
	cmd.command = "<NEW_CHAT>";
	cmd.params = strdup(buffer);
	send_cmd(cmd, new_chat_request->client);
	bzero(buffer, BUFFER_SZ);
}

void delete_msg_request(del_msg_request_s *delete_msg_request) {
	command cmd;
	char buffer[BUFFER_SZ];
	snprintf(buffer, BUFFER_SZ, "<%d>", delete_msg_request->msg_id);
	cmd.command = "<DELETE_MSG>";
	cmd.params = strdup(buffer);
	send_cmd(cmd, delete_msg_request->client);
	bzero(buffer, BUFFER_SZ);
}

void delete_chat_request(del_chat_request_s *delete_chat_request) {
    command cmd;
    char buffer[BUFFER_SZ];
    snprintf(buffer, BUFFER_SZ, "<%d>", delete_chat_request->chat_id);
    cmd.command = "<DELETE_CHAT>";
    cmd.params = strdup(buffer);
    send_cmd(cmd, delete_chat_request->client);
    bzero(buffer, BUFFER_SZ);
}

void edit_msg_request(edit_msg_request_s *edit_msg_request) {
	command cmd;
	char buffer[BUFFER_SZ];
	snprintf(buffer, BUFFER_SZ, "<%d> <%s>", edit_msg_request->msg_id, edit_msg_request->new_text);
	cmd.command = "<EDIT_MSG>";
	cmd.params = strdup(buffer);
	send_cmd(cmd, edit_msg_request->client);
	bzero(buffer, BUFFER_SZ);
}

void delete_chat_request(del_chat_request_s *delete_chat_request) {
	command cmd;
	char buffer[BUFFER_SZ];
	snprintf(buffer, BUFFER_SZ, "<%d>", delete_chat_request->chat_id);
	cmd.command = "<DELETE_CHAT>";
	cmd.params = strdup(buffer);
	send_cmd(cmd, delete_chat_request->client);
	bzero(buffer, BUFFER_SZ);
}
