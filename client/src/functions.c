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
    printf("LOGIN: success.\n\tLogin: %s\n\tPassword: %s\n", p_login, p_pass);
}

void func_register(GtkWidget *widget, gpointer data) {
    UNUSED(widget);
	client_t *client = (client_t *)data;
    char buffer[LENGTH];
    char *p_username = strdup(username_str_s);
    char *p_nick = strdup(nick_str_s);
    char *p_pass = strdup(pass_str_s);
    char *p_r_pass = strdup(r_pass_str_s);
    snprintf(buffer, BUFFER_SZ, "<REGISTER> <%s> <%s> <%s> <%s>", p_username, p_nick, p_pass, p_r_pass);
    send(client->sockfd, buffer, strlen(buffer), 0);
    bzero(buffer, LENGTH);
    printf("REGISTER: success.\n\tUsername: %s\n\tNickname: %s\n", p_username, p_nick);
    printf("\tPassword: %s\n\tRepeated password: %s\n", p_pass, p_r_pass);
}

void f_change_name(char *params) {
    char *p_new_nick = param_1(params);
    printf("CHANGE NAME: success.\n\tNew nickname: %s\n", p_new_nick);
}

void f_change_pass(char *params) {
    char *p_new_pass = param_1(params);
    printf("CHANGE PASSWORD: success.\n\tNew password: %s\n", p_new_pass);
}

void f_search_user(char *params) {
    char *p_username = param_1(params);
    printf("SEARCH USER: success.\n\tSearch user with username: %s\n", p_username);
}

void f_add_contact(char *params) {
    char *p_username = param_1(params);
    printf("ADD CONTACT: success.\n\tContact added: %s\n", p_username);
}

void f_del_contact(char *params) {
    char *p_username = param_1(params);
    printf("DELETE CONTACT: success.\n\tContact deleted: %s\n", p_username);
}

void f_block_user(char *params) {
    char *p_username = param_1(params);
    printf("BLOCK USER: success.\n\tUser blocked: %s\n", p_username);
}

void f_unblock_user(char *params) {
    char *p_username = param_1(params);
    printf("UNBLOCK USER: success.\n\tUser unblocked: %s\n", p_username);
}

void f_new_chnl(char *params) {
    char *p_chnlname = param_1(params);
    printf("NEW CHANNEL: success.\n\tChannel created: %s\n", p_chnlname);
}

void init_funcs(cmd_func arr_cmd_func[]) {
    char *arr_func_names[AMOUNT_OF_CMD] = { "<LOGIN>", "<REGISTER>", "<CHANGE_NAME>",
                                "<CHANGE_PASS>", "<SEARCH_USER>", "<ADD_CONTACT>",
                                "<DEL_CONTACT>", "<BLOCK_USER>", "<UNBLOCK_USER>",
                                "<NEW_CHNL>", "<SEND>"};

    arr_cmd_func[0].func = &func_login;
    arr_cmd_func[1].func = &func_register;
    /*arr_cmd_func[2].func = &f_change_name;
    arr_cmd_func[3].func = &f_change_pass;
    arr_cmd_func[4].func = &f_search_user;
    arr_cmd_func[5].func = &f_add_contact;
    arr_cmd_func[6].func = &f_del_contact;
    arr_cmd_func[7].func = &f_block_user;
    arr_cmd_func[8].func = &f_unblock_user;
    arr_cmd_func[9].func = &f_new_chnl;*/

    for (int i = 0; i < AMOUNT_OF_CMD; i++)
        arr_cmd_func[i].name = strdup(arr_func_names[i]);
}
