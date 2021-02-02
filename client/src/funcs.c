#include "../inc/header.h"

void func_login(GtkWidget *widget, gpointer data) {
    UNUSED(widget);
	client_t *client = (client_t *)data;
    char buffer[LENGTH];
    char *p_login = strdup(username_str);
    char *p_pass = strdup(passoword_str);
    snprintf(buffer, BUFFER_SZ, "<LOGIN> <%s> <%s>", p_login, p_pass);
    send(client->sockfd, buffer, strlen(buffer), 0);
    bzero(buffer, LENGTH);
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
    char buffer[LENGTH];
    char *p_login = strdup(username_str_s);
    char *p_nick = strdup(nick_str_s);
    char *p_pass = strdup(pass_str_s);
    char *p_r_pass = strdup(r_pass_str_s);
    snprintf(buffer, BUFFER_SZ, "<REGISTER> <%s> <%s> <%s> <%s>", p_login, p_nick, p_pass, p_r_pass);
    send(client->sockfd, buffer, strlen(buffer), 0);
    bzero(buffer, LENGTH);
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