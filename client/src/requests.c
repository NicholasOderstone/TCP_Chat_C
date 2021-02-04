#include "../inc/header.h"

void get_msg_request(GtkWidget *widget, gpointer data) {
    UNUSED(widget);
    get_messages_request_s *get_messages_request = (get_messages_request_s *)data;
	get_messages_request->client->active_chat_id = get_messages_request->chat->chat_id;

	command cmd;
	char buffer[BUFFER_SZ];
	snprintf(buffer, BUFFER_SZ, "<%d>", get_messages_request->chat->chat_id);
	cmd.command = "<CHAT_MSG>";
	cmd.params = strdup(buffer);
	send_cmd(cmd, get_messages_request->client);
	bzero(buffer, BUFFER_SZ);
	while (clean_listbox((gpointer)get_messages_request->client->m->box_message) == TRUE){
	}
	get_messages_request->client->m->row_num_list_gtk = -1;
}

void new_chat_request(GtkWidget *widget, gpointer data) {
    UNUSED(widget);
    new_chat_request_s *new_chat_request = (new_chat_request_s *)data;

	command cmd;
	char buffer[BUFFER_SZ];
	snprintf(buffer, BUFFER_SZ, "<%s>", new_chat_request->new_chat_name);
	cmd.command = "<NEW_CHAT>";
	cmd.params = strdup(buffer);
	send_cmd(cmd, new_chat_request->client);
	bzero(buffer, BUFFER_SZ);
}
