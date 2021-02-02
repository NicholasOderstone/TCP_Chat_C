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
    char buffer[BUFFER_SZ];
    char *p_login = strdup(username_str);
    char *p_pass = strdup(passoword_str);
    snprintf(buffer, BUFFER_SZ, "<LOGIN> <%s> <%s>", p_login, p_pass);
    send(client->sockfd, buffer, strlen(buffer), 0);
    bzero(buffer, BUFFER_SZ);
    while (sw_login == -1) { }
    switch(sw_login) {
        case 0:
        client->login = strdup(p_login);
        client->pass = strdup(p_pass);
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
    char buffer[BUFFER_SZ];
    char *p_login = strdup(username_str_s);
    char *p_nick = strdup(nick_str_s);
    char *p_pass = strdup(pass_str_s);
    char *p_r_pass = strdup(r_pass_str_s);
    snprintf(buffer, BUFFER_SZ, "<REGISTER> <%s> <%s> <%s> <%s>", p_login, p_nick, p_pass, p_r_pass);
    send(client->sockfd, buffer, strlen(buffer), 0);
    bzero(buffer, BUFFER_SZ);
    while (sw_register == -1) { }
    switch(sw_register) {
        case 0:
            client->login = strdup(p_login);
            client->pass = strdup(p_pass);
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
    char buffer[BUFFER_SZ + 32];
    snprintf(buffer, BUFFER_SZ, "<CHAT_MSG> <%s>", itoa(get_messages_request->chat->chat_id, 10));
    send(get_messages_request->client->sockfd, buffer, strlen(buffer), 0);
    bzero(buffer, BUFFER_SZ + 32);
}
