#include "../inc/header.h"

char* itoa(int val, int base){
	static char buf[32] = {0};
	int i = 30;
	for(; val && i ; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];
	return &buf[i+1];
}

void func_login(GtkWidget *widget, gpointer data) {
    UNUSED(widget);
	client_t *client = (client_t *)data;

	command cmd;
    char buffer[BUFFER_SZ];
    snprintf(buffer, BUFFER_SZ, "<%s> <%s>", username_str, passoword_str);
    cmd.command = "<LOGIN>";
    cmd.params = strdup(buffer);
    send_cmd(cmd, client);
    bzero(buffer, BUFFER_SZ);

    while (sw_login == -1) { }
    switch(sw_login) {
        case 0:
        client->login = strdup(username_str);
        client->pass = strdup(passoword_str);
            open_main_page(NULL, data);
            sw_login = -1;
            break;
        case 1:
            printf("## INCORRECT_LOGIN\n");
            sw_login = -1;
            break;
        case 2:
            printf("## INCORRECT_PASS\n");
            sw_login = -1;
            break;
        default:
            break;
    }
}

void func_register(GtkWidget *widget, gpointer data) {
    UNUSED(widget);
	client_t *client = (client_t *)data;

	command cmd;
	char buffer[BUFFER_SZ];
	snprintf(buffer, BUFFER_SZ, "<%s> <%s> <%s> <%s>", username_str_s, nick_str_s, pass_str_s, r_pass_str_s);
	cmd.command = "<REGISTER>";
	cmd.params = strdup(buffer);
	send_cmd(cmd, client);
	bzero(buffer, BUFFER_SZ);

    while (sw_register == -1) { }
    switch(sw_register) {
        case 0:
            client->login = strdup(username_str_s);
            client->pass = strdup(pass_str_s);
            open_main_page(NULL, data);
            sw_register = -1;
            break;
        case 1:
            printf("## USERNAME_EXIST\n");
            sw_register = -1;
            break;
        case 2:
            printf("## PASS_NOT_MATCH\n");
            sw_register = -1;
            break;
        default:
            break;
    }
}

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
}
