#include "../inc/header.h"

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
