#include "../inc/header.h"

char *itoa(int val, int base) {
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
    char *p_login = strdup(mx_strtrim(username_str));
    char *p_pass = strdup(passoword_str);
    snprintf(buffer, BUFFER_SZ, "<LOGIN> <%s> <%s>", p_login, p_pass);
    send(client->sockfd, buffer, strlen(buffer), 0);
    bzero(buffer, BUFFER_SZ);
    while (sw_login == -1) { }
    switch(sw_login) {
        case 0:
	        client->login = strdup(p_login);
	        client->pass = strdup(p_pass);
			gtk_widget_hide(GTK_WIDGET(incorrect_l));
			gtk_widget_hide(GTK_WIDGET(incorrect_p));
            open_main_page(NULL, data);
            sw_login = -1;
            break;
        case 1:
            // printf("## INCORRECT_LOGIN\n");
			gtk_widget_show(GTK_WIDGET(incorrect_l));
			gtk_widget_hide(GTK_WIDGET(incorrect_p));
            sw_login = -1;
            break;
        case 2:
            // printf("## INCORRECT_PASS\n");
			gtk_widget_show(GTK_WIDGET(incorrect_p));
			gtk_widget_hide(GTK_WIDGET(incorrect_l));
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
    char *p_login = strdup(mx_strtrim(username_str_s));
    char *p_nick = strdup(mx_strtrim(nick_str_s));
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
			gtk_widget_hide(GTK_WIDGET(diff_p));
			gtk_widget_hide(GTK_WIDGET(username_e));
            open_main_page(NULL, data);
            sw_register = -1;
            break;
        case 1:
            // printf("## USERNAME_EXIST\n");
			gtk_widget_show(GTK_WIDGET(username_e));
			gtk_widget_hide(GTK_WIDGET(diff_p));
            sw_register = -1;
            break;
        case 2:
            // printf("## PASS_NOT_MATCH\n");
			gtk_widget_show(GTK_WIDGET(diff_p));
			gtk_widget_hide(GTK_WIDGET(username_e));
            sw_register = -1;
            break;
        default:
            break;
    }
}
